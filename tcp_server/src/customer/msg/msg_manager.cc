/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    msg_manager.cc
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-05-01
@ description:  see the header.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#include "msg_manager.h"

#include "event2/bufferevent.h"

#include "event/event_manager.h"
#include "framework/util/algorithm.h"
#include "msg/msg_type.h"
#include "msg/msg_id.h"
#include "msg/msg_code.h"
#include "msg/protocol/my_login_msg_protocol.pb.h"
#include "msg/protocol/create_room_msg_protocol.pb.h"
#include "msg/protocol/game_start_msg_protocol.pb.h"
#include "network/network_manager.h"
#include "player/player.h"
#include "room/card_constants.h"
#include "room/room_manager.h"

namespace gamer {

MsgManager::MsgManager() {
    this->Init();
}

MsgManager* MsgManager::instance() {
	static MsgManager s_msg_mgr; 
	return &s_msg_mgr;
}

void MsgManager::Init() {
    this->AddMsgDispatchers();
    this->AddMsgHandlers();
}

void MsgManager::AddMsgDispatchers() {
    // login
    msg_dispatchers_.insert(std::make_pair((int)MsgTypes::C2S_MSG_TYPE_LOGIN,
        CALLBACK_SELECTOR_2(MsgManager::DealWithLoginMsg, this)));

    // room
    msg_dispatchers_.insert(std::make_pair((int)MsgTypes::C2S_MSG_TYPE_ROOM,
        CALLBACK_SELECTOR_2(MsgManager::DealWithRoomMsg, this)));
}

void MsgManager::AddMsgHandlers() {
    // login
    msg_handlers_.insert(std::make_pair((int)MsgIDs::MSG_ID_LOGIN_MY,
        CALLBACK_SELECTOR_2(MsgManager::DealWithMgLoginMsg, this)));

    // room
    // create room
    msg_handlers_.insert(std::make_pair((int)MsgIDs::MSG_ID_ROOM_CREATE,
        CALLBACK_SELECTOR_2(MsgManager::DealWithCreateRoomMsg, this)));

    // start game
    msg_handlers_.insert(std::make_pair((int)MsgIDs::MSG_ID_ROOM_START_GAME,
        CALLBACK_SELECTOR_2(MsgManager::DealWithStartGameMsg, this)));
}

bool MsgManager::SendMsg(const ServerMsg& msg, struct bufferevent* bev) {
	char buf[MsgManager::MAX_MSG_LEN] = { 0 };
	msg_header_t len = 0;
    if (this->PackMsg(msg, buf, len)){
        return NetworkManager::instance()->Send(bev, buf, len);
    }
    return false;
}

bool MsgManager::SendMsg(msg_header_t msg_type, 
                         msg_header_t msg_id,
                         msg_header_t msg_code,
                         const google::protobuf::Message& msg,
                         struct bufferevent* bev) {
    char buf[MsgManager::MAX_MSG_LEN] = { 0 };
    msg_header_t len = 0;
    auto ok = this->PackMsg(msg_type, msg_id, msg_code, msg, buf, len);
    if (ok) {
        return NetworkManager::instance()->Send(bev, buf, len);
    }
    return false;
}

bool MsgManager::PackMsg(const ServerMsg& msg, char* buf, msg_header_t& len) {
	auto len_total = gamer::server_msg_header_len();
	auto len_data = 0;  
	if (msg.context) {
		len_data = strlen((char*)msg.context);
		len_total += len_data;
	}

    if (len_total > MsgManager::MAX_MSG_LEN)
        return false;

	len = len_total;

	memcpy(buf, &len_total, sizeof(msg_header_t));
	memcpy(buf + sizeof(msg_header_t), &msg.type, sizeof(msg_header_t));
	memcpy(buf + sizeof(msg_header_t) * 2, &msg.id, sizeof(msg_header_t));
    memcpy(buf + sizeof(msg_header_t) * 3, &msg.code, sizeof(msg_header_t));
	if (len_data > 0) {
		memcpy(buf + gamer::server_msg_header_len(), msg.context, len_data);
	}

    return true;
}

bool MsgManager::PackMsg(msg_header_t msg_type, 
                         msg_header_t msg_id, 
                         msg_header_t msg_code,
                         const google::protobuf::Message& msg, 
                         char* buf, 
                         msg_header_t& len) {
    auto len_total = gamer::server_msg_header_len() + msg.ByteSize();
    if (len_total > MsgManager::MAX_MSG_LEN) // TODO : log
        return false;

    len = len_total;

    memcpy(buf, &len_total, sizeof(msg_header_t));
    memcpy(buf + sizeof(msg_header_t), &msg_type, sizeof(msg_header_t));
    memcpy(buf + sizeof(msg_header_t) * 2, &msg_id, sizeof(msg_header_t));
    memcpy(buf + sizeof(msg_header_t) * 3, &msg_code, sizeof(msg_header_t));

    if (msg.ByteSize() > 0) {
        return msg.SerializeToArray(buf + gamer::server_msg_header_len(), msg.ByteSize());
    }
    return true;
}

bool MsgManager::ParseMsg(const ClientMsg& msg, google::protobuf::Message& proto) {
    if (msg.total_len > MsgManager::MAX_MSG_LEN)
        return false;

    auto len = msg.total_len - gamer::client_msg_header_len();
    return proto.ParseFromArray(msg.context, len);
}

void MsgManager::DealWithLoginMsg(const ClientMsg& msg, struct bufferevent* bev) {
    auto itr = msg_handlers_.find((int)msg.id);
    if (itr != msg_handlers_.end()) {
        itr->second(msg, bev);
    }
}

void MsgManager::DealWithMgLoginMsg(const ClientMsg& msg, struct bufferevent* bev) {
    // TODO : verify password
    protocol::MyLoginMsgProtocol proto;
    proto.set_account("2017");
    proto.set_password(2018);
    proto.set_code(2020);

    this->SendMsg((msg_header_t)MsgTypes::S2C_MSG_TYPE_LOGIN,
                  (msg_header_t)MsgIDs::MSG_ID_LOGIN_MY,
                  (msg_header_t)MsgCodes::MSG_RESPONSE_CODE_SUCCESS,
                  proto,
                  bev);
}

void MsgManager::DealWithRoomMsg(const ClientMsg& msg, struct bufferevent* bev) {
    auto itr = msg_handlers_.find((int)msg.id);
    if (itr != msg_handlers_.end()) {
        itr->second(msg, bev);
    }
}

void MsgManager::DealWithCreateRoomMsg(const ClientMsg& msg, struct bufferevent* bev) {
    protocol::CreateRoomMsgProtocol proto;
    if (this->ParseMsg(msg, proto)) {
        auto room_mgr = RoomManager<Player>::instance();
        auto room_id = room_mgr->GenerateRoomID();
        if (-1 == room_id) {
            // TODO : log 
        }
        else {
            auto room = Room<Player>::Create(room_id, proto);
            room_mgr->AddRoom(room);
            
            proto.set_room_id(room_id);
            auto msg_code = (msg_header_t)MsgCodes::MSG_RESPONSE_CODE_SUCCESS;
            this->SendMsg(msg.type, msg.id, msg_code, proto, bev);
        }        
    }
}

void MsgManager::DealWithStartGameMsg(const ClientMsg& msg, struct bufferevent* bev) {
    // 1.verify client msg
    protocol::GameStartMsgProtocol proto_client;
    auto ret = this->ParseMsg(msg, proto_client);
    if (!ret) {
        // TODO : log
        this->SendStartGameMsgForError((msg_header_t)MsgCodes::MSG_RESPONSE_CODE_FAILED1, bev); // TODO : specify error code
        return;
    }

    // 2.verify room id and room owner id
    auto room_id = proto_client.room_id();   
    auto room = RoomManager<Player>::instance()->GetRoom(room_id);
    protocol::CreateRoomMsgProtocol* create_room_msg_proto;
    if (nullptr == room) {
        // TODO : log
        this->SendStartGameMsgForError((msg_header_t)MsgCodes::MSG_RESPONSE_CODE_FAILED1, bev); // TODO : specify error code
        return;
    }
    else {
        create_room_msg_proto = room->get_create_room_msg_protocol();
        auto room_owner_id_client = proto_client.room_owner_id();
        auto room_owner_id_server = create_room_msg_proto->room_owner_id();
        if (room_owner_id_server != room_owner_id_client) {
            // TODO : log
            this->SendStartGameMsgForError((msg_header_t)MsgCodes::MSG_RESPONSE_CODE_FAILED1, bev); // TODO : specify error code
            return;
        }
    }

    // 3.verify room player num
    if (room->cur_players_num() < room->get_game_start_msg_protocol().players_num()) {
        // TODO : log
        this->SendStartGameMsgForError((msg_header_t)MsgCodes::MSG_RESPONSE_CODE_FAILED1, bev); // TODO : specify error code
        return;
    }

    int buf[CardConstants::TOTAL_CARDS_NUM] = { 
                     11, 12, 13, 14, 15, 16, 17, 18, 19,
                     11, 12, 13, 14, 15, 16, 17, 18, 19,
                     11, 12, 13, 14, 15, 16, 17, 18, 19,
                     11, 12, 13, 14, 15, 16, 17, 18, 19,
                
                     21, 22, 23, 24, 25, 26, 27, 28, 29,
                     21, 22, 23, 24, 25, 26, 27, 28, 29,
                     21, 22, 23, 24, 25, 26, 27, 28, 29,
                     21, 22, 23, 24, 25, 26, 27, 28, 29,

                     31, 32, 33, 34, 35, 36, 37, 38, 39,
                     31, 32, 33, 34, 35, 36, 37, 38, 39,
                     31, 32, 33, 34, 35, 36, 37, 38, 39,
                     31, 32, 33, 34, 35, 36, 37, 38, 39,

                     41, 42, 43, 44, 45, 46, 47,
                     41, 42, 43, 44, 45, 46, 47,
                     41, 42, 43, 44, 45, 46, 47,
                     41, 42, 43, 44, 45, 46, 47,
                     
                     51, 52, 53, 54, 55, 56, 57, 58 };
    auto vec = std::vector<int>(buf, buf + CardConstants::TOTAL_CARDS_NUM - 1);
    gamer::Shuffle(vec);

    protocol::GameStartMsgProtocol proto_server;
    // room common
    auto room_owner_id = create_room_msg_proto->room_owner_id();
    auto players_num = create_room_msg_proto->players_num();
    proto_server.set_room_id(room_id);
    proto_server.set_room_owner_id(room_owner_id);
    proto_server.set_players_num(players_num);
    proto_server.set_cur_round(1); // TODO : 1 is not right allways
    proto_server.set_total_round(create_room_msg_proto->rounds_num()); // TODO : rounds_num replace by total_round
    proto_server.set_remain_cards_num(CardConstants::TOTAL_CARDS_NUM - 
        players_num * CardConstants::ONE_PLAYER_CARD_NUM - 1);
    proto_server.set_cur_acting_player_id(room_owner_id);
    proto_server.set_cur_action_id(0); // TODO : 
    proto_server.set_banker_id(room_owner_id); // not right allways
    proto_server.set_banker_is_same_time(0); // not right allways

    // room player
    auto players = room->players();
    auto itr_player = players->begin();
    auto card_index = 0;
    for (auto i = 0; i < players_num; i++) {
        auto player_cards = proto_server.add_player_cards();
        //player_cards->set_player_id(itr_player->first);
        player_cards->set_player_id(i);
        for (auto j = 0; j <= CardConstants::ONE_PLAYER_CARD_NUM; j++) {
            auto card = vec.at(card_index);
            player_cards->add_invisible_hand_cards(card);

            if (card >= CardConstants::CARD_VALUE_SEASON_OR_FLOWER_1 &&
                card <= CardConstants::CARD_VALUE_SEASON_OR_FLOWER_4) {
                player_cards->add_flower_cards(card);
            } else if (card > CardConstants::CARD_VALUE_SEASON_OR_FLOWER_4) {
                player_cards->add_season_cards(card);
            }
            // TODO : visible cards and waiting cards
            ++card_index;
        }

        //++itr_player;
    }

    this->SendMsg((msg_header_t)MsgTypes::S2C_MSG_TYPE_ROOM,
                  (msg_header_t)MsgIDs::MSG_ID_ROOM_START_GAME,
                  (msg_header_t)MsgCodes::MSG_RESPONSE_CODE_SUCCESS,
                  proto_server,
                  bev);
}

void MsgManager::SendStartGameMsgForError(msg_header_t error_code, struct bufferevent* bev) {
    protocol::GameStartMsgProtocol proto_empty;
    this->SendMsg((msg_header_t)MsgTypes::S2C_MSG_TYPE_ROOM,
                  (msg_header_t)MsgIDs::MSG_ID_ROOM_START_GAME,
                  error_code, 
                  proto_empty,
                  bev);
}

void MsgManager::OnMsgReceived(const ClientMsg& msg, struct bufferevent* bev) {
    auto itr = msg_dispatchers_.find((int)msg.type);
    if (itr != msg_dispatchers_.end()) {
        itr->second(msg, bev);
    }
}

} // namespace gamer