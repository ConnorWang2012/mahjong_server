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

#include "framework/util/google/absl/strings/numbers.h"

#include "event2/bufferevent.h"

#include "event/event_manager.h"
#include "data/data_manager.h"
#include "data/config_manager.h"
#include "framework/algorithm/chess_card_algorithm.h"
#include "framework/log/mylog.h"
#include "msg/msg_type.h"
#include "msg/msg_id.h"
#include "msg/msg_code.h"
#include "msg/property_id.h"
#include "msg/protocol/my_login_msg_protocol.pb.h"
#include "msg/protocol/set_property_msg_protocol.pb.h"
#include "msg/protocol/room_list_msg_protocol.pb.h"
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
	msg_dispatchers_.insert(std::make_pair((id_t)MsgTypes::C2S_MSG_TYPE_LOGIN,
		CALLBACK_SELECTOR_2(MsgManager::DealWithLoginMsg, this)));

	// hall
	// property
	msg_dispatchers_.insert(std::make_pair((id_t)MsgTypes::C2S_MSG_TYPE_PROPERTY,
		CALLBACK_SELECTOR_2(MsgManager::DealWithPropertyMsg, this)));

	// room
	msg_dispatchers_.insert(std::make_pair((id_t)MsgTypes::C2S_MSG_TYPE_ROOM,
		CALLBACK_SELECTOR_2(MsgManager::DealWithRoomMsg, this)));
}

void MsgManager::AddMsgHandlers() {
	// login
	msg_handlers_.insert(std::make_pair((id_t)MsgIDs::MSG_ID_LOGIN_MY,
		CALLBACK_SELECTOR_2(MsgManager::DealWithMgLoginMsg, this)));

	// hall
	// property
	msg_handlers_.insert(std::make_pair((id_t)MsgIDs::MSG_ID_PROPERTY_GET_PLAYER_INFO,
		CALLBACK_SELECTOR_2(MsgManager::DealWithGetPlayerInfoMsg, this)));

	msg_handlers_.insert(std::make_pair((id_t)MsgIDs::MSG_ID_PROPERTY_SET,
		CALLBACK_SELECTOR_2(MsgManager::DealWithSetPropertyMsg, this)));

	// room
	// create room
	msg_handlers_.insert(std::make_pair((id_t)MsgIDs::MSG_ID_ROOM_CREATE,
		CALLBACK_SELECTOR_2(MsgManager::DealWithCreateRoomMsg, this)));

	// player join room
	msg_handlers_.insert(std::make_pair((id_t)MsgIDs::MSG_ID_ROOM_PLAYER_JOIN,
		CALLBACK_SELECTOR_2(MsgManager::DealWithPlayerJoinRoomMsg, this)));

	// player leave room
	msg_handlers_.insert(std::make_pair((id_t)MsgIDs::MSG_ID_ROOM_PLAYER_LEAVE,
		CALLBACK_SELECTOR_2(MsgManager::DealWithPlayerLeaveRoomMsg, this)));

	// get room list
	msg_handlers_.insert(std::make_pair((id_t)MsgIDs::MSG_ID_ROOM_GET_ROOM_LIST,
		CALLBACK_SELECTOR_2(MsgManager::DealWithGetRoomListMsg, this)));

	// start game
	msg_handlers_.insert(std::make_pair((id_t)MsgIDs::MSG_ID_ROOM_START_GAME,
		CALLBACK_SELECTOR_2(MsgManager::DealWithStartGameMsg, this)));

	// play card
	msg_handlers_.insert(std::make_pair((id_t)MsgIDs::MSG_ID_ROOM_PLAY_CARD,
		CALLBACK_SELECTOR_2(MsgManager::DealWithPlayCardMsg, this)));
}

void MsgManager::OnMsgReceived(const ClientMsg& msg, bufferevent* bev) {
	auto itr = msg_dispatchers_.find((id_t)msg.type);
	if (itr != msg_dispatchers_.end()) {
		itr->second(msg, bev);
	}
}

void MsgManager::DealWithLoginMsg(const ClientMsg& msg, bufferevent* bev) {
	auto itr = msg_handlers_.find((id_t)msg.id);
	if (itr != msg_handlers_.end()) {
		itr->second(msg, bev);
	}
}

void MsgManager::DealWithPropertyMsg(const ClientMsg& msg, bufferevent * bev) {
	auto itr = msg_handlers_.find((id_t)msg.id);
	if (itr != msg_handlers_.end()) {
		itr->second(msg, bev);
	}
}

void MsgManager::DealWithRoomMsg(const ClientMsg& msg, bufferevent* bev) {
	auto itr = msg_handlers_.find((id_t)msg.id);
	if (itr != msg_handlers_.end()) {
		itr->second(msg, bev);
	}
}

void MsgManager::DealWithMgLoginMsg(const ClientMsg& msg, bufferevent* bev) {
	gamer::protocol::MyLoginMsgProtocol login_proto_client;
	if ( !this->ParseMsg(msg, &login_proto_client ) ) {
		// TODO : log
		this->SendMsgForError(MsgCodes::MSG_CODE_LOGIN_MSG_PROTO_ERR, msg, bev);
		return;
	}

	// check account and password
	if (login_proto_client.account().empty() || login_proto_client.password().empty()) {
		// TODO : log
		this->SendMsgForError(MsgCodes::MSG_CODE_LOGIN_ACCOUNT_OR_PASSWORD_ERR, msg, bev);
		return;
	}
	
	auto player_id_new = 0;
	Player* player = nullptr;
	gamer::protocol::MyLoginMsgProtocol login_proto_server;
	auto player_proto = new (std::nothrow) gamer::protocol::PlayerMsgProtocol;

	// get cached account data
	std::string account_server  = "";
	std::string password_server = "";
	id_t player_id_server       = 0;

	if (login_proto_client.player_id() <= 0) { // first login
        player_id_new    = DataManager::instance()->GeneratePlayerID();
		player_id_server = player_id_new;
		account_server   = PlayerManager::instance()->GenerateAccountByPlayerID(player_id_new);
		password_server  = account_server; // password is account

		// TODO : init by cfg
        player_proto->set_player_id(player_id_new);
        player_proto->set_nick_name(account_server); 
		player_proto->set_sex((unsigned)Player::Sex::FEMALE);
		player_proto->set_head_portrait_type((unsigned)Player::PortraitTypes::LOCAL);
		player_proto->set_head_portrait_id(gamer::GenerateRandom<id_t>(1, 75));
        player_proto->set_level(1);
        player_proto->set_level_name("开启一切");
        player_proto->set_score_gold(10000);
		player_proto->set_score_diamond(5000);
		player_proto->set_num_room_cards(10);
		player_proto->set_num_played_games(0);
		player_proto->set_num_win_games(0);
		player_proto->set_num_loss_games(0);

		// cache player data
		// 1.account and password
		DataManager::instance()->CacheAccountData(account_server, player_id_new, password_server);

		// 2.other personal data
		std::string player_data = "";
		if ( !player_proto->SerializeToString(&player_data) ) {
			this->SendMsgForError(MsgCodes::MSG_CODE_LOGIN_MSG_PROTO_ERR, msg, bev);
			return;
		}
		DataManager::instance()->CachePlayerPersonalData(player_id_new, player_data);
	} else { // not first login
		DataManager::instance()->GetCacheAccountData(login_proto_client.account(),
			&player_id_server, &password_server);

		// check account and player id
		if (player_id_server != login_proto_client.player_id()) {
			this->SendMsgForError(MsgCodes::MSG_CODE_LOGIN_ACCOUNT_OR_PLAYERID_ERR, msg, bev);
			return;
		}

		// check password
		if (password_server != login_proto_client.password()) {
			this->SendMsgForError(MsgCodes::MSG_CODE_LOGIN_ACCOUNT_OR_PASSWORD_ERR, msg, bev);
			return;
		}

		// get cache player data
		std::string player_data = "";
		DataManager::instance()->GetCachedPlayerPersonalData(player_id_server, &player_data);

		if (player_data.empty()) {
			this->SendMsgForError(MsgCodes::MSG_CODE_LOGIN_PLAYER_ID_ERR, msg, bev);
			return;
		}

		if ( !player_proto->ParseFromString(player_data) ) {
			this->SendMsgForError(MsgCodes::MSG_CODE_LOGIN_MSG_PROTO_ERR, msg, bev);
			return;
		}

		account_server = login_proto_client.account();
	}

	// add on line player, keep the bev for sending msg
	player = Player::Create(player_id_server);
	player->set_account(account_server);
	PlayerManager::instance()->AddOnlinePlayer(player_id_server, player, bev);

	// prepare player data for client
	login_proto_server.set_account(account_server);
	login_proto_server.set_password(password_server);
	login_proto_server.set_player_id(player_id_server);
	login_proto_server.set_allocated_player(player_proto);

	// send login succeed msg
	this->SendMsg((msg_header_t)MsgTypes::S2C_MSG_TYPE_LOGIN,
				  (msg_header_t)MsgIDs::MSG_ID_LOGIN_MY,
				  (msg_header_t)MsgCodes::MSG_CODE_SUCCESS,
                  login_proto_server,
				  bev);
}

void MsgManager::DealWithGetPlayerInfoMsg(const ClientMsg& msg, bufferevent* bev) {
	gamer::protocol::PlayerMsgProtocol proto;
	if ( !this->ParseMsg(msg, &proto) ) {
		this->SendMsgForError(MsgCodes::MSG_CODE_MSG_PROTO_ERR, msg, bev);
		return;
	}

	std::string data = "";
	DataManager::instance()->GetCachedPlayerPersonalData(proto.player_id(), &data);
	if (data.empty()) {
		this->SendMsgForError(MsgCodes::MSG_CODE_GET_DATA_ERR, msg, bev);
		return;
	}

	if ( !proto.ParseFromString(data) ) {
		this->SendMsgForError(MsgCodes::MSG_CODE_PARSE_DATA_ERR, msg, bev);
		return;
	}

	this->SendMsg((msg_header_t)MsgTypes::S2C_MSG_TYPE_PROPERTY,
		(msg_header_t)MsgIDs::MSG_ID_PROPERTY_GET_PLAYER_INFO,
		(msg_header_t)MsgCodes::MSG_CODE_SUCCESS,
		proto,
		bev);
}

void MsgManager::DealWithSetPropertyMsg(const ClientMsg& msg, bufferevent* bev) {
	gamer::protocol::SetPropertyMsgProtocol proto;
	if (!this->ParseMsg(msg, &proto)) {
		this->SendMsgForError(MsgCodes::MSG_CODE_MSG_PROTO_ERR, msg, bev);
		return;
	}

	for (auto i = 0; i < proto.property_ids_size(); i++) {
		if (proto.property_ids(i) == (unsigned)gamer::PropertyIDs::PROP_ID_NICKNAME) {
			this->DealWithSetNicknameMsg(msg, bev, &proto, proto.player_id(), proto.new_properties(i));
		} else if (proto.property_ids(i) == (unsigned)gamer::PropertyIDs::PROP_ID_SEX) {
			this->DealWithSetSexMsg(msg, bev, &proto, proto.player_id(), proto.new_properties(i));
		} else if (proto.property_ids(i) == (unsigned)gamer::PropertyIDs::PROP_ID_HEAD_PORTRAIT_LOCAL) {
			this->DealWithSetLocalHeadPortraitMsg(msg, bev, &proto, proto.player_id(), proto.new_properties(i));
		}
	}
}

void MsgManager::DealWithSetNicknameMsg(const ClientMsg& msg, bufferevent* bev,
	google::protobuf::Message* proto, id_t player_id, const std::string& nickname) {
	// TODO : check limit
	
	// get cache player data
	std::string player_data = "";
	DataManager::instance()->GetCachedPlayerPersonalData(player_id, &player_data);

	if (player_data.empty()) {
		this->SendMsgForError(MsgCodes::MSG_CODE_GET_DATA_ERR, msg, bev);
		return;
	}

	gamer::protocol::PlayerMsgProtocol player_proto;
	if ( !player_proto.ParseFromString(player_data) ) {
		this->SendMsgForError(MsgCodes::MSG_CODE_PARSE_DATA_ERR, msg, bev);
		return;
	}

	player_proto.set_nick_name(nickname);

	if ( !player_proto.SerializePartialToString(&player_data) ) {
		this->SendMsgForError(MsgCodes::MSG_CODE_PARSE_DATA_ERR, msg, bev);
		return;
	}

	DataManager::instance()->CachePlayerPersonalData(player_id, player_data);

	this->SendMsg((msg_header_t)MsgTypes::S2C_MSG_TYPE_PROPERTY,
		(msg_header_t)MsgIDs::MSG_ID_PROPERTY_SET,
		(msg_header_t)MsgCodes::MSG_CODE_SUCCESS,
		*proto,
		bev);
}

void MsgManager::DealWithSetSexMsg(const ClientMsg& msg, bufferevent* bev, 
	google::protobuf::Message* proto, id_t player_id, const std::string& sex) {
	if (sex.empty()) {
		this->SendMsgForError(MsgCodes::MSG_CODE_MSG_PROTO_ERR, msg, bev);
		return;
	}

	// TODO : check limit

	// get cache player data
	std::string player_data = "";
	DataManager::instance()->GetCachedPlayerPersonalData(player_id, &player_data);

	if (player_data.empty()) {
		this->SendMsgForError(MsgCodes::MSG_CODE_GET_DATA_ERR, msg, bev);
		return;
	}

	gamer::protocol::PlayerMsgProtocol player_proto;
	if (!player_proto.ParseFromString(player_data)) {
		this->SendMsgForError(MsgCodes::MSG_CODE_PARSE_DATA_ERR, msg, bev);
		return;
	}

	if (sex == "1") {
		player_proto.set_sex((unsigned)Player::Sex::FEMALE);
	} else {
		player_proto.set_sex((unsigned)Player::Sex::MALE);
	}
	
	if (!player_proto.SerializePartialToString(&player_data)) {
		this->SendMsgForError(MsgCodes::MSG_CODE_PARSE_DATA_ERR, msg, bev);
		return;
	}

	DataManager::instance()->CachePlayerPersonalData(player_id, player_data);

	this->SendMsg((msg_header_t)MsgTypes::S2C_MSG_TYPE_PROPERTY,
		(msg_header_t)MsgIDs::MSG_ID_PROPERTY_SET,
		(msg_header_t)MsgCodes::MSG_CODE_SUCCESS,
		*proto,
		bev);
}

void MsgManager::DealWithSetLocalHeadPortraitMsg(const ClientMsg& msg, bufferevent* bev, 
	google::protobuf::Message* proto, id_t player_id, const std::string& head_portrait_id) {
	if (head_portrait_id.empty()) {
		this->SendMsgForError(MsgCodes::MSG_CODE_MSG_PROTO_ERR, msg, bev);
		return;
	}

	// TODO : check limit

	// get cache player data
	std::string player_data = "";
	DataManager::instance()->GetCachedPlayerPersonalData(player_id, &player_data);

	if (player_data.empty()) {
		this->SendMsgForError(MsgCodes::MSG_CODE_GET_DATA_ERR, msg, bev);
		return;
	}

	gamer::protocol::PlayerMsgProtocol player_proto;
	if ( !player_proto.ParseFromString(player_data) ) {
		this->SendMsgForError(MsgCodes::MSG_CODE_PARSE_DATA_ERR, msg, bev);
		return;
	}

	unsigned portrait_id = 1;
	absl::SimpleAtoi<unsigned>(head_portrait_id, &portrait_id);

	player_proto.set_head_portrait_type((unsigned)Player::PortraitTypes::LOCAL);
	player_proto.set_head_portrait_id(portrait_id);

	if ( !player_proto.SerializePartialToString(&player_data) ) {
		this->SendMsgForError(MsgCodes::MSG_CODE_PARSE_DATA_ERR, msg, bev);
		return;
	}

	DataManager::instance()->CachePlayerPersonalData(player_id, player_data);

	this->SendMsg((msg_header_t)MsgTypes::S2C_MSG_TYPE_PROPERTY,
		(msg_header_t)MsgIDs::MSG_ID_PROPERTY_SET,
		(msg_header_t)MsgCodes::MSG_CODE_SUCCESS,
		*proto,
		bev);
}

void MsgManager::DealWithCreateRoomMsg(const ClientMsg& msg, bufferevent* bev) {
	gamer::protocol::CreateRoomMsgProtocol proto;
	if ( !this->ParseMsg(msg, &proto) ) {
		this->SendMsgForError(MsgCodes::MSG_CODE_ROOM_CREATE_ROOM_MSG_PROTO_ERR, msg, bev);
		return;
	}

	// TODO:
	// check gold cost, room card cost

    // check whether player on line 
    auto player = PlayerManager::instance()->GetOnlinePlayer(proto.room_owner_id());
    if (nullptr == player) {
        // TODO : log
        this->SendMsgForError(MsgCodes::MSG_CODE_PLAYER_OFFLINE, msg, bev);
        return;
    }

	// generate room id
	auto room_mgr = RoomManager<Player>::instance();
	auto room_id = room_mgr->GenerateRoomID();
	if (room_id <= 0) {
		this->SendMsgForError(MsgCodes::MSG_CODE_ROOM_GENERATE_ROOM_ID_ERR, msg, bev);
		return;
	}

	// send create room success msg
	proto.set_room_id(room_id);
    this->SendMsg(msg.type, msg.id, (msg_header_t)MsgCodes::MSG_CODE_SUCCESS, proto, bev);

    // add player to room
    auto room = room_mgr->GetRoom(room_id);
    if (nullptr == room) {
        room = Room<Player>::Create(room_id);
        room_mgr->AddRoom(room);
    }
	room->AddPlayer(player);
	
    room->InitCreateRoomMsgProtocol(proto);
}

void MsgManager::DealWithPlayerJoinRoomMsg(const ClientMsg& msg, bufferevent* bev) {
	gamer::protocol::RoomOperationMsgProtocol proto_client;
	if ( !this->ParseMsg(msg, &proto_client) ) {
		// TODO : log
		this->SendMsgForError(MsgCodes::MSG_CODE_ROOM_JOIN_ROOM_MSG_PROTO_ERR, msg, bev);
		return;
	}

	// find room
	auto room = RoomManager<Player>::instance()->GetRoom(proto_client.room_id());
	if (nullptr == room) {
		// TODO : log
		this->SendMsgForError(MsgCodes::MSG_CODE_ROOM_NOT_EXIST, msg, bev);
		return;
	}

	// check whether player in the room
	auto player_id = proto_client.player_id();
	if (room->is_player_in_room(player_id)) {
		// TODO : log
		this->SendMsgForError(MsgCodes::MSG_CODE_ROOM_PLAYER_ALREADY_IN_THE_ROOM, msg, bev);
		return;
	}

	// check whether player in any other room
	if (RoomManager<Player>::instance()->IsPlayerInRoom(player_id)) {
		// TODO : log
		this->SendMsgForError(MsgCodes::MSG_CODE_ROOM_PLAYER_ALREADY_IN_OTHER_ROOM, msg, bev);
		return;
	}

	// check players num
	if (room->is_players_num_upper_limit()) {
		// TODO : log
		this->SendMsgForError(MsgCodes::MSG_CODE_ROOM_PLAYER_NUM_LIMIT, msg, bev);
		return;
	}

	// check whether player on line
	auto player = PlayerManager::instance()->GetOnlinePlayer(player_id);
	if (nullptr == player) {
		// TODO : log
		this->SendMsgForError(MsgCodes::MSG_CODE_PLAYER_OFFLINE, msg, bev);
		return;
    }

    room->AddPlayer(player);

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
	gamer::protocol::RoomOperationMsgProtocol proto_client;
	if ( !this->ParseMsg(msg, &proto_client) ) {
		// TODO : log
		this->SendMsgForError(MsgCodes::MSG_CODE_ROOM_LEAVE_ROOM_MSG_PROTO_ERR, msg, bev);
		return;
	}

	// find room
	auto room = RoomManager<Player>::instance()->GetRoom(proto_client.room_id());
	if (nullptr == room) {
		// TODO : log
		this->SendMsgForError(MsgCodes::MSG_CODE_ROOM_NOT_EXIST, msg, bev);
		return;
	}

	// check whether player in any other room
	auto player_id = proto_client.player_id();
	if ( !RoomManager<Player>::instance()->IsPlayerInRoom(player_id) ) {
		// TODO : log
		this->SendMsgForError(MsgCodes::MSG_CODE_ROOM_PLAYER_NOT_IN_ROOM, msg, bev);
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

void MsgManager::DealWithGetRoomListMsg(const ClientMsg& msg, bufferevent* bev) {
	gamer::protocol::RoomListMsgProtocol proto;
	if ( !this->ParseMsg(msg, &proto) ) {
		this->SendMsgForError(MsgCodes::MSG_CODE_MSG_PROTO_ERR, msg, bev);
		return;
	}

	auto room_list_proto = ConfigManager::instance()->room_list_msg_protocol();
	if (room_list_proto->IsInitialized()) {
		room_list_proto->set_player_id(proto.player_id());
		this->SendMsg((msg_header_t)MsgTypes::S2C_MSG_TYPE_ROOM,
			          (msg_header_t)MsgIDs::MSG_ID_ROOM_GET_ROOM_LIST,
			          (msg_header_t)MsgCodes::MSG_CODE_SUCCESS,
			          *room_list_proto,
			          bev);
	} else {
		this->SendMsgForError(MsgCodes::MSG_CODE_PARSE_DATA_ERR, msg, bev);
		return;
	}
}

void MsgManager::DealWithStartGameMsg(const ClientMsg& msg, bufferevent* bev) {
	// 1.verify client msg
	gamer::protocol::RoomMsgProtocol proto_client;
	if ( !this->ParseMsg(msg, &proto_client) ) {
		// TODO : log
		this->SendMsgForError(MsgCodes::MSG_CODE_ROOM_MSG_PROTO_ERR, msg, bev); 
		return;
	}

	// 2.verify room id and room owner id
	auto room_id = proto_client.room_id();
	auto room = RoomManager<Player>::instance()->GetRoom(room_id);
	if (nullptr == room) {
		// TODO : log
		this->SendMsgForError(MsgCodes::MSG_CODE_ROOM_NOT_EXIST, msg, bev);
		return;
	}

	// 3.verify room players num
	if ( !room->is_players_num_upper_limit() ) {
		// TODO : log
		this->SendMsgForError(MsgCodes::MSG_CODE_ROOM_PLAYER_NUM_LIMIT, msg, bev);
		return;
	}

    // 4.deal with game start
    auto code = room->DealWithGameStart(proto_client);
    if (code != MsgCodes::MSG_CODE_SUCCESS) {
        this->SendMsgForError(code, msg, bev);
    }
}

void MsgManager::DealWithPlayCardMsg(const ClientMsg& msg, bufferevent* bev) {
	gamer::protocol::PlayCardMsgProtocol proto_client;
	if ( !this->ParseMsg(msg, &proto_client) ) {
		// TODO : log
		this->SendMsgForError(MsgCodes::MSG_CODE_ROOM_PLAY_CARD_MSG_PROTO_ERR, 
			msg, bev);
		return;
	}

	// find room
	auto room = RoomManager<Player>::instance()->GetRoom(proto_client.room_id());
	if (nullptr == room) {
		// TODO : log
		this->SendMsgForError(MsgCodes::MSG_CODE_ROOM_NOT_EXIST, msg, bev);
		return;
	}

    // deal with play card
    auto code = room->DealWithPlayCard(proto_client);
    if (code != MsgCodes::MSG_CODE_SUCCESS) {
        this->SendMsgForError(code, msg, bev);
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

void MsgManager::SendMsgForError(gamer::MsgCodes error_code, 
	const ClientMsg& msg, bufferevent* bev) {
	gamer::ServerMsg server_msg = { gamer::server_msg_header_len(),
									msg.type,
									msg.id,
									(msg_header_t)error_code,
									msg.context };
	this->SendMsg(server_msg, bev);
}

} // namespace gamer