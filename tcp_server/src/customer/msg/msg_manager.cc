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

#include "event2/bufferevent.h"		  // libevent

#include "event/event_manager.h"
#include "data/data_manager.h"
#include "framework/util/algorithm.h"
#include "framework/base/log_headers.h"
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

//MsgManager* MsgManager::instance() {
//	static MsgManager s_msg_mgr; 
//	return &s_msg_mgr;
//}

bool MsgManager::SendMsg(const ServerMsg& msg, bufferevent* bev) {
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
                         bufferevent* bev) {
    char buf[MsgManager::MAX_MSG_LEN] = { 0 };
    msg_header_t len = 0;
    auto ok = this->PackMsg(msg_type, msg_id, msg_code, msg, buf, len);
    if (ok) {
        return NetworkManager::instance()->Send(bev, buf, len);
    }
    return false;
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

void MsgManager::OnMsgReceived(const ClientMsg& msg, bufferevent* bev) {
	auto itr = msg_dispatchers_.find((int)msg.type);
	if (itr != msg_dispatchers_.end()) {
		itr->second(msg, bev);
	}
}

void MsgManager::DealWithLoginMsg(const ClientMsg& msg, bufferevent* bev) {
	auto itr = msg_handlers_.find((int)msg.id);
	if (itr != msg_handlers_.end()) {
		itr->second(msg, bev);
	}
}

void MsgManager::DealWithRoomMsg(const ClientMsg& msg, bufferevent* bev) {
	auto itr = msg_handlers_.find((int)msg.id);
	if (itr != msg_handlers_.end()) {
		itr->second(msg, bev);
	}
}

void MsgManager::DealWithMgLoginMsg(const ClientMsg& msg, bufferevent* bev) {
	protocol::MyLoginMsgProtocol login_proto_client;
	if (!this->ParseMsg(msg, &login_proto_client)) {
		// TODO : log
		// TODO : specify error code
		auto error_code = (msg_header_t)MsgCodes::MSG_RESPONSE_CODE_FAILED1;
		this->SendMsgForError(error_code, msg, bev);
		return;
	}

	// check account and password
	if ("" == login_proto_client.account() || 0 == login_proto_client.password()) {
		// TODO : log
		// TODO : specify error code
		auto error_code = (msg_header_t)MsgCodes::MSG_RESPONSE_CODE_FAILED1;
		this->SendMsgForError(error_code, msg, bev);
		return;
	}

	std::string player_msg = "";
	DataManager::instance()->GetPlayerPersonalData(login_proto_client.account(), player_msg);
	protocol::MyLoginMsgProtocol login_proto_server;
	auto player_id = 0;
	if ("" == player_msg) { // first login
		login_proto_server.set_account(login_proto_client.account());
		login_proto_server.set_password(login_proto_client.password());

		auto player_proto = new protocol::PlayerMsgProtocol;
		login_proto_server.set_allocated_player(player_proto);
		player_id = DataManager::instance()->GeneratePlayerID();
		player_proto->set_player_id(player_id);
		player_proto->set_game_currency(5000); // TODO : cfg
		player_proto->set_nick_name(login_proto_client.account());
		player_proto->set_level(1);
		player_proto->set_level_name("junior");

		auto login_info = login_proto_server.SerializeAsString();
		if ("" == login_info) {
			// TODO : log
			// TODO : specify error code
			auto error_code = (msg_header_t)MsgCodes::MSG_RESPONSE_CODE_FAILED1;
			this->SendMsgForError(error_code, msg, bev);
			return;
		}
		else {
			DataManager::instance()->SetPlayerPersonalData(login_proto_client.account(), login_info);
		}

	}
	else { // not first login
		if (!login_proto_server.ParseFromString(player_msg)) {
			// TODO : log
			// TODO : specify error code
			auto error_code = (msg_header_t)MsgCodes::MSG_RESPONSE_CODE_FAILED1;
			this->SendMsgForError(error_code, msg, bev);
			return;
		}
		else {
			// verify server password
			if (login_proto_server.password() != login_proto_client.password()) {
				// TODO : specify error code
				auto error_code = (msg_header_t)MsgCodes::MSG_RESPONSE_CODE_FAILED1;
				this->SendMsgForError(error_code, msg, bev);
				return;
			}
		}
	}

	// login succeed, keep the bev for sending msg
    player_id = (0 == player_id) ? login_proto_server.player().player_id() : player_id;
	if (bufferevents_.find(player_id) == bufferevents_.end()) {
		bufferevents_.insert(std::make_pair(player_id, bev));
	}

	// send login succeed msg
	this->SendMsg((msg_header_t)MsgTypes::S2C_MSG_TYPE_LOGIN,
				  (msg_header_t)MsgIDs::MSG_ID_LOGIN_MY,
				  (msg_header_t)MsgCodes::MSG_RESPONSE_CODE_SUCCESS,
				  login_proto_client,
				  bev);
}

void MsgManager::DealWithCreateRoomMsg(const ClientMsg& msg, bufferevent* bev) {
	protocol::CreateRoomMsgProtocol proto;
	if ( !this->ParseMsg(msg, &proto) ) {
		// TODO : log
		this->SendMsgForError((int)MsgCodes::MSG_RESPONSE_CODE_FAILED1, msg, bev);
		return;
	}

	auto room_mgr = RoomManager<Player>::instance();
	auto room_id = room_mgr->GenerateRoomID();
	if (-1 == room_id) {
		// TODO : log 
		return;
	} else {
		proto.set_room_id(room_id);
		auto msg_code = (msg_header_t)MsgCodes::MSG_RESPONSE_CODE_SUCCESS;
		auto ret = this->SendMsg(msg.type, msg.id, msg_code, proto, bev);

		// save data
		if ( !ret) { 
			// TODO : log
			return;
		} else {
			auto room = Room<Player>::Create(room_id);
			auto player = Player::Create(proto.room_owner_id());
			room->AddPlayer(proto.room_owner_id(), player);
			room_mgr->AddRoom(room);

			auto serialized_str = proto.SerializeAsString();
			if ("" != serialized_str) {
				DataManager::instance()->SetCreateRoomData(room_id, serialized_str);
			}
		}
	}	
}

void MsgManager::DealWithStartGameMsg(const ClientMsg& msg, bufferevent* bev) {
	// 1.verify client msg
	protocol::GameStartMsgProtocol proto_client;
	if (!this->ParseMsg(msg, &proto_client)) {
		// TODO : log
		this->SendMsgForError((msg_header_t)MsgCodes::MSG_RESPONSE_CODE_FAILED1, msg, bev); // TODO : specify error code
		return;
	}

	// 2.verify room id and room owner id
	auto room_id = proto_client.room_id();
	auto room = RoomManager<Player>::instance()->GetRoom(room_id);
	protocol::CreateRoomMsgProtocol create_room_msg_proto;
	if (nullptr == room) {
		// TODO : log
		this->SendMsgForError((msg_header_t)MsgCodes::MSG_RESPONSE_CODE_FAILED1, msg, bev); // TODO : specify error code
		return;
	}

	std::string serialized_str = "";
	DataManager::instance()->GetCreateRoomData(room_id, serialized_str);
	if ("" != serialized_str) {
		auto ret = create_room_msg_proto.ParseFromString(serialized_str);
		if ( !ret) {
			// TODO : log
			this->SendMsgForError((msg_header_t)MsgCodes::MSG_RESPONSE_CODE_FAILED1, msg, bev); // TODO : specify error code
			return;
		}
	}

	auto room_owner_id_client = proto_client.room_owner_id();
	auto room_owner_id_server = create_room_msg_proto.room_owner_id();
	if (room_owner_id_server != room_owner_id_client) {
		// TODO : log
		this->SendMsgForError((msg_header_t)MsgCodes::MSG_RESPONSE_CODE_FAILED1, msg, bev); // TODO : specify error code
		return;
	}

	// 3.verify room player num
	if (room->cur_players_num() != create_room_msg_proto.players_num()) {
		// TODO : log
		this->SendMsgForError((msg_header_t)MsgCodes::MSG_RESPONSE_CODE_FAILED1, msg, bev); // TODO : specify error code
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
	auto room_owner_id = create_room_msg_proto.room_owner_id();
	auto players_num = create_room_msg_proto.players_num();
	proto_server.set_room_id(room_id);
	proto_server.set_room_owner_id(room_owner_id);
	proto_server.set_players_num(players_num);
	proto_server.set_cur_round(1); // TODO : 1 is not right allways
	proto_server.set_total_round(create_room_msg_proto.rounds_num()); // TODO : rounds_num replace by total_round
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
		auto player_id = itr_player->first;
		player_cards->set_player_id(player_id);
		auto card_num = (player_id == room_owner_id) ? (CardConstants::ONE_PLAYER_CARD_NUM + 1) :
			CardConstants::ONE_PLAYER_CARD_NUM;
		for (auto j = 0; j <= card_num; j++) {
			auto card = vec.at(card_index);
			player_cards->add_invisible_hand_cards(card);

			if (card >= CardConstants::CARD_VALUE_SEASON_OR_FLOWER_1 &&
				card <= CardConstants::CARD_VALUE_SEASON_OR_FLOWER_4) {
				player_cards->add_flower_cards(card);
			}
			else if (card > CardConstants::CARD_VALUE_SEASON_OR_FLOWER_4) {
				player_cards->add_season_cards(card);
			}
			// TODO : visible cards and waiting cards
			++card_index;
		}

		++itr_player;
	}

	// cache game start data
	auto value = proto_server.SerializeAsString();
	if ("" != value) {
		DataManager::instance()->SetGameStartData(room_id, proto_server.cur_round(), value);
	}

	// send msg to all players in the room 
	// 1.prepare all player game start data
	std::unordered_map<int, protocol::GameStartMsgProtocol> game_start_protos;
	game_start_protos.insert(std::make_pair(proto_server.room_owner_id(),
		protocol::GameStartMsgProtocol(proto_server)));
	for (auto i = 0; i < proto_server.player_cards_size(); i++) {
		auto player_id = proto_server.player_cards(i).player_id();
		if (player_id != proto_server.room_owner_id()) {
			game_start_protos.insert(std::make_pair(player_id, 
				protocol::GameStartMsgProtocol(proto_server)));
		}
	}

	// 2.remove other player invisible hand cards except self
	for (auto it = game_start_protos.begin(); it != game_start_protos.end(); it++) {
		auto player_cards = it->second.mutable_player_cards();
		for (auto i = 0; i < it->second.player_cards_size(); i++) {
			if (it->first != it->second.player_cards(i).player_id()){
				it->second.mutable_player_cards(i)->clear_invisible_hand_cards();
			}
		}
	}

	// 3.send msg(not contain other player invisible cards) to all player
	for (auto itr = players->begin(); itr != players->end(); itr++) {
		auto player_id = itr->first;
		auto bev_itr = bufferevents_.find(player_id);
		if (bev_itr != bufferevents_.end()) {
			auto game_start_itr = game_start_protos.find(player_id);
			if (game_start_itr != game_start_protos.end()) {
				this->SendMsg((msg_header_t)MsgTypes::S2C_MSG_TYPE_ROOM,
							  (msg_header_t)MsgIDs::MSG_ID_ROOM_START_GAME,
							  (msg_header_t)MsgCodes::MSG_RESPONSE_CODE_SUCCESS,
							  game_start_itr->second,
							  bev_itr->second);
			}
		} else {
			// TODO : log
		}
	}

	// 4.release allocated
	for (auto itr = game_start_protos.begin(); itr != game_start_protos.end(); itr++) {
		auto player_cards = itr->second.mutable_player_cards();
		player_cards->DeleteSubrange(0, itr->second.player_cards_size());
	}
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

bool MsgManager::ParseMsg(const ClientMsg& msg, google::protobuf::Message* proto) {
    if (nullptr == proto || msg.total_len > MsgManager::MAX_MSG_LEN)
        return false;

    auto len = msg.total_len - gamer::client_msg_header_len();
    return proto->ParseFromArray(msg.context, len);
}

void MsgManager::SendMsgForError(msg_header_t error_code, const ClientMsg& msg, bufferevent* bev) {
	gamer::ServerMsg server_msg = { gamer::server_msg_header_len(),
									msg.type,
									msg.id,
									error_code,
									msg.context };
	this->SendMsg(server_msg, bev);
}

} // namespace gamer