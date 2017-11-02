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
#include "framework/util/chess_card_algorithm.h"
#include "framework/base/log_headers.h"
#include "msg/msg_type.h"
#include "msg/msg_id.h"
#include "msg/msg_code.h"
#include "msg/protocol/my_login_msg_protocol.pb.h"
#include "msg/protocol/create_room_msg_protocol.pb.h"
#include "msg/protocol/room_operation_msg_protocol.pb.h"
#include "network/network_manager.h"
#include "player/player.h"
#include "player/player_manager.h"
#include "room/card_constants.h"
#include "room/room_manager.h"

namespace gamer {

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
    msg_dispatchers_.clear();
    msg_handlers_.clear();

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

	// player join room
	msg_handlers_.insert(std::make_pair((int)MsgIDs::MSG_ID_ROOM_PLAYER_JOIN,
		CALLBACK_SELECTOR_2(MsgManager::DealWithPlayerJoinRoomMsg, this)));

	// player leave room
	msg_handlers_.insert(std::make_pair((int)MsgIDs::MSG_ID_ROOM_PLAYER_LEAVE,
		CALLBACK_SELECTOR_2(MsgManager::DealWithPlayerLeaveRoomMsg, this)));

	// start game
	msg_handlers_.insert(std::make_pair((int)MsgIDs::MSG_ID_ROOM_START_GAME,
		CALLBACK_SELECTOR_2(MsgManager::DealWithStartGameMsg, this)));

	// play card
	msg_handlers_.insert(std::make_pair((int)MsgIDs::MSG_ID_ROOM_PLAY_CARD,
		CALLBACK_SELECTOR_2(MsgManager::DealWithPlayCardMsg, this)));
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
	if ( !this->ParseMsg(msg, &login_proto_client )) {
		// TODO : log
		this->SendMsgForError((msg_header_t)MsgCodes::MSG_CODE_LOGIN_MSG_PROTO_ERR, 
			msg, bev);
		return;
	}

	// check account and password
	if ("" == login_proto_client.account() || "" == login_proto_client.password()) {
		// TODO : log
		this->SendMsgForError((msg_header_t)MsgCodes::MSG_CODE_LOGIN_ACCOUNT_OR_PASSWORD_ERR, 
			msg, bev);
		return;
	}

	std::string account_data = "";
	DataManager::instance()->GetCachedPlayerPersonalData(login_proto_client.account(), 
		&account_data);
	
	auto player_id = 0;
    auto player = Player::Create(player_id);
    protocol::MyLoginMsgProtocol login_proto_server;

	if ("" == account_data) { // first login
        player_id = DataManager::instance()->GeneratePlayerID();
        player->set_account(login_proto_client.account());
        player->set_player_id(player_id);
        
        auto player_proto  = new protocol::PlayerMsgProtocol;
        player_proto->set_player_id(player_id);
        player_proto->set_nick_name(login_proto_client.account());
        player_proto->set_level(1);
        player_proto->set_level_name("junior");
        player_proto->set_score_gold(10000); // TODO : cfg
		player_proto->set_score_diamond(5000);
		player_proto->set_num_room_cards(10);
		player_proto->set_num_played_games(0);
		player_proto->set_num_win_games(0);

        login_proto_server.set_account(login_proto_client.account());
        login_proto_server.set_password(login_proto_client.password());
		login_proto_server.set_allocated_player(player_proto);

		auto accout_info = login_proto_server.SerializeAsString();
		if ("" == accout_info) {
			// TODO : log
			this->SendMsgForError((msg_header_t)MsgCodes::MSG_CODE_LOGIN_MSG_PROTO_ERR, 
				msg, bev);
			return;
		} else {
			DataManager::instance()->CachePlayerPersonalData(login_proto_client.account(), 
                accout_info);

			DataManager::instance()->CacheAccountByID(player_id, login_proto_client.account());
		}
	} else { // not first login
		if ( !login_proto_server.ParseFromString(account_data) ) {
			// TODO : log
			this->SendMsgForError((msg_header_t)MsgCodes::MSG_CODE_LOGIN_MSG_PROTO_ERR, msg, bev);
			return;
		} else {
			// check account and password
			if (login_proto_server.password() != login_proto_client.password()) {
				// TODO : log
				this->SendMsgForError((msg_header_t)MsgCodes::MSG_CODE_LOGIN_ACCOUNT_OR_PASSWORD_ERR, 
					msg, bev);
				return;
			}

            player_id = login_proto_server.player().player_id();
            player->set_account(login_proto_server.account());
            player->set_player_id(player_id);
		}
	}

	// login succeed, add online player, keep the bev for sending msg	
	PlayerManager::instance()->AddOnlinePlayer(player_id, player, bev);

	// send login succeed msg
	this->SendMsg((msg_header_t)MsgTypes::S2C_MSG_TYPE_LOGIN,
				  (msg_header_t)MsgIDs::MSG_ID_LOGIN_MY,
				  (msg_header_t)MsgCodes::MSG_CODE_SUCCESS,
                  login_proto_server,
				  bev);
}

void MsgManager::DealWithCreateRoomMsg(const ClientMsg& msg, bufferevent* bev) {
	protocol::CreateRoomMsgProtocol proto;
	if ( !this->ParseMsg(msg, &proto) ) {
		this->SendMsgForError((msg_header_t)MsgCodes::MSG_CODE_ROOM_CREATE_ROOM_MSG_PROTO_ERR,
			msg, bev);
		return;
	}

	// check gold cost


	auto room_mgr = RoomManager<Player>::instance();
	auto room_id = room_mgr->GenerateRoomID();
	if (-1 == room_id) {
		this->SendMsgForError((msg_header_t)MsgCodes::MSG_CODE_ROOM_GENERATE_ROOM_ID_ERR,
			msg, bev);
		return;
	}

	proto.set_room_id(room_id);
	auto ret = this->SendMsg(msg.type, msg.id, (msg_header_t)MsgCodes::MSG_CODE_SUCCESS, 
		proto, bev);
	if ( !ret ) { 
		// TODO : log
		return;
	} 

	auto room = Room<Player>::Create(room_id);
	auto player = Player::Create(proto.room_owner_id());
	room->AddPlayer(player);
	room_mgr->AddRoom(room);

    room->InitCreateRoomMsgProtocol(proto);
}

void MsgManager::DealWithPlayerJoinRoomMsg(const ClientMsg& msg, bufferevent* bev) {
	gamer::protocol::RoomOperationMsgProtocol proto_client;
	if ( !this->ParseMsg(msg, &proto_client) ) {
		// TODO : log
		this->SendMsgForError((msg_header_t)MsgCodes::MSG_CODE_ROOM_JOIN_ROOM_MSG_PROTO_ERR, 
			msg, bev);
		return;
	}

	// find room
	auto room = RoomManager<Player>::instance()->GetRoom(proto_client.room_id());
	if (nullptr == room) {
		// TODO : log
		this->SendMsgForError((msg_header_t)MsgCodes::MSG_CODE_ROOM_NOT_EXIST, 
			msg, bev);
		return;
	}

	// check whether player in the room
	auto player_id = proto_client.player_id();
	if (room->is_player_in_room(player_id)) {
		// TODO : log
		this->SendMsgForError((msg_header_t)MsgCodes::MSG_CODE_ROOM_PLAYER_ALREADY_IN_THE_ROOM, 
			msg, bev);
		return;
	}

	// check whether player in any other room
	if (RoomManager<Player>::instance()->IsPlayerInRoom(player_id)) {
		// TODO : log
		this->SendMsgForError((msg_header_t)MsgCodes::MSG_CODE_ROOM_PLAYER_ALREADY_IN_OTHER_ROOM,
			msg, bev);
		return;
	}

	// check players num
	if (room->is_players_num_upper_limit()) {
		// TODO : log
		this->SendMsgForError((msg_header_t)MsgCodes::MSG_CODE_ROOM_PLAYER_NUM_LIMIT,
			msg, bev);
		return;
	}

	// check whether player online
	auto player = PlayerManager::instance()->GetOnlinePlayer(player_id);
	if (nullptr == player) {
		// TODO : log
		this->SendMsgForError((msg_header_t)MsgCodes::MSG_CODE_PLAYER_OFFLINE, msg, bev);
		return;
    } else {
        room->AddPlayer(player);
    }

	// send join succeed msg to all players in the room
	auto players = room->players();
	for (auto& player : *players) {
		auto bev = PlayerManager::instance()->GetOnlinePlayerBufferevent(player->player_id());
		if (nullptr != bev) {
			this->SendMsg((msg_header_t)MsgTypes::S2C_MSG_TYPE_ROOM,
				          (msg_header_t)MsgIDs::MSG_ID_ROOM_PLAYER_JOIN,
				          (msg_header_t)MsgCodes::MSG_CODE_SUCCESS,
				          proto_client,
						  bev);
		}
	}
}

void MsgManager::DealWithPlayerLeaveRoomMsg(const ClientMsg& msg, bufferevent* bev) {
	protocol::RoomOperationMsgProtocol proto_client;
	if ( !this->ParseMsg(msg, &proto_client) ) {
		// TODO : log
		this->SendMsgForError((msg_header_t)MsgCodes::MSG_CODE_ROOM_LEAVE_ROOM_MSG_PROTO_ERR, 
			msg, bev);
		return;
	}

	// find room
	auto room = RoomManager<Player>::instance()->GetRoom(proto_client.room_id());
	if (nullptr == room) {
		// TODO : log
		this->SendMsgForError((msg_header_t)MsgCodes::MSG_CODE_ROOM_NOT_EXIST, msg, bev);
		return;
	}

	// check whether player in any other room
	auto player_id = proto_client.player_id();
	if ( !RoomManager<Player>::instance()->IsPlayerInRoom(player_id) ) {
		// TODO : log
		this->SendMsgForError((msg_header_t)MsgCodes::MSG_CODE_ROOM_PLAYER_NOT_IN_ROOM,
			msg, bev);
		return;
	}

	// send leave succeed msg to all players in the room
	auto players = room->players();
	for (auto& player : *players) {
		auto bev = PlayerManager::instance()->GetOnlinePlayerBufferevent(player->player_id());
		if (nullptr != bev) {
			this->SendMsg((msg_header_t)MsgTypes::S2C_MSG_TYPE_ROOM,
				          (msg_header_t)MsgIDs::MSG_ID_ROOM_PLAYER_LEAVE,
				          (msg_header_t)MsgCodes::MSG_CODE_SUCCESS,
				          proto_client,
				          bev);
		}
	}

	room->RomovePlayer(player_id);
}

void MsgManager::DealWithStartGameMsg(const ClientMsg& msg, bufferevent* bev) {
	// 1.verify client msg
	gamer::protocol::RoomMsgProtocol proto_client;
	if ( !this->ParseMsg(msg, &proto_client) ) {
		// TODO : log
		this->SendMsgForError((msg_header_t)MsgCodes::MSG_CODE_ROOM_MSG_PROTO_ERR, msg, bev); 
		return;
	}

	// 2.verify room id and room owner id
	auto room_id = proto_client.room_id();
	auto room = RoomManager<Player>::instance()->GetRoom(room_id);
	if (nullptr == room) {
		// TODO : log
		this->SendMsgForError((msg_header_t)MsgCodes::MSG_CODE_ROOM_NOT_EXIST, msg, bev);
		return;
	}

	// 3.verify room players num
	if ( !room->is_players_num_upper_limit() ) {
		// TODO : log
		this->SendMsgForError((msg_header_t)MsgCodes::MSG_CODE_ROOM_PLAYER_NUM_LIMIT, msg, bev);
		return;
	}

    // 4.deal with game start
    auto code = room->DealWithGameStart(proto_client);
    if (code != MsgCodes::MSG_CODE_SUCCESS) {
        this->SendMsgForError((msg_header_t)code, msg, bev);
    }
}

void MsgManager::DealWithPlayCardMsg(const ClientMsg& msg, bufferevent* bev) {
	gamer::protocol::PlayCardMsgProtocol proto_client;
	if ( !this->ParseMsg(msg, &proto_client) ) {
		// TODO : log
		this->SendMsgForError((msg_header_t)MsgCodes::MSG_CODE_ROOM_PLAY_CARD_MSG_PROTO_ERR, 
			msg, bev);
		return;
	}

	// find room
	auto room = RoomManager<Player>::instance()->GetRoom(proto_client.room_id());
	if (nullptr == room) {
		// TODO : log
		this->SendMsgForError((msg_header_t)MsgCodes::MSG_CODE_ROOM_NOT_EXIST, msg, bev);
		return;
	}

    // deal with play card
    auto code = room->DealWithPlayCard(proto_client);
    if (code != MsgCodes::MSG_CODE_SUCCESS) {
        this->SendMsgForError((msg_header_t)code, msg, bev);
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