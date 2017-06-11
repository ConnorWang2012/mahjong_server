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

    return msg.SerializeToArray(buf + gamer::server_msg_header_len(), msg.ByteSize());
}

bool MsgManager::ParseMsg(const ClientMsg& msg, google::protobuf::Message& proto) {
    if (msg.total_len > MsgManager::MAX_MSG_LEN)
        return false;

    auto len = msg.total_len - gamer::client_msg_header_len();
    proto.ParseFromArray(msg.context, len);

    return true;
}

void MsgManager::DealWithLoginMsg(const ClientMsg& msg, struct bufferevent* bev) {
    auto itr = msg_handlers_.find((int)msg.id);
    if (itr != msg_handlers_.end()) {
        itr->second(msg, bev);
    }
}

void MsgManager::DealWithMgLoginMsg(const ClientMsg& msg, struct bufferevent* bev) {
    // TODO : verify password
    char buf[MsgManager::MAX_MSG_LEN] = { 0 };
    protocol::MyLoginMsgProtocol proto;
    proto.set_account("2017");
    proto.set_password(2018);
    proto.set_code(2020);
    proto.SerializeToArray(buf, proto.ByteSize());

    auto len_total = gamer::server_msg_header_len() + proto.ByteSize();
    gamer::ServerMsg msg2 = { len_total,
        (msg_header_t)MsgTypes::C2S_MSG_TYPE_LOGIN,
        (msg_header_t)MsgIDs::MSG_ID_LOGIN_MY,
        (msg_header_t)MsgCodes::MSG_RESPONSE_CODE_SUCCESS,
        buf };
    this->SendMsg(msg2, bev);
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
        auto room_mgr = RoomManager::instance();
        auto room_id = room_mgr->GenerateRoomID();
        if (-1 == room_id) {
            // TODO : log 
        }
        else {
            auto room = Room::Create(room_id, proto);
            room_mgr->AddRoom(room);
            
            auto msg_code = (msg_header_t)MsgCodes::MSG_RESPONSE_CODE_SUCCESS;
            this->SendMsg(msg.type, msg.id, msg_code, proto, bev);
        }        
    }
}

void MsgManager::DealWithStartGameMsg(const ClientMsg& msg, struct bufferevent* bev) {
    std::vector<int> vec = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 
                             21, 22, 23, 24, 25, 26, 27, 28, 29,
                             31, 32, 33, 34, 35, 36, 37, 38, 39,
                             41, 42, 43, 44, 45, 46, 47,
                             51, 52, 53, 54, 55, 56, 57, 58 };
    gamer::Shuffle(vec);

    char buf[MsgManager::MAX_MSG_LEN] = { 0 };
    protocol::GameStartMsgProtocol proto;

    proto.SerializeToArray(buf, proto.ByteSize());

    auto len_total = gamer::server_msg_header_len() + proto.ByteSize();
    gamer::ServerMsg msg2 = { len_total,
        (msg_header_t)MsgTypes::C2S_MSG_TYPE_LOGIN,
        (msg_header_t)MsgIDs::MSG_ID_LOGIN_MY,
        (msg_header_t)MsgCodes::MSG_RESPONSE_CODE_SUCCESS,
        buf };
    this->SendMsg(msg2, bev);
}

void MsgManager::OnMsgReceived(const ClientMsg& msg, struct bufferevent* bev) {
    auto itr = msg_dispatchers_.find((int)msg.type);
    if (itr != msg_dispatchers_.end()) {
        itr->second(msg, bev);
    }
}

} // namespace gamer