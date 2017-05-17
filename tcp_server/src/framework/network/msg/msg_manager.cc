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

#include "msg/msg_type.h"
#include "msg/msg_id.h"
#include "msg/protocol/my_login_msg_protocol.pb.h"
#include "event/event_manager.h"
#include "network/network_manager.h"

namespace gamer {

MsgManager::MsgManager() {

}

MsgManager* MsgManager::instance() {
	static MsgManager s_msg_mgr; 
	return &s_msg_mgr;
}

bool MsgManager::SendMsg(const Msg& msg) {

    return true;
}

bool MsgManager::SendMsg(const Msg& msg, struct bufferevent* bev) {
	char buf[MsgManager::MAX_MSG_LEN] = { 0 };
	msg_header_t len = 0;
	this->PackMsg(msg, buf, len);
	return NetworkManager::instance()->Send(bev, buf, len);
}

void MsgManager::PackMsg(const Msg& msg, char* buf, msg_header_t& len) {
	auto len_total = gamer::msg_header_len();
	auto len_data = 0;  
	if (msg.context) {
		len_data = strlen((char*)msg.context);
		len_total += len_data;
	}

	len = len_total;

	memcpy(buf, &len_total, sizeof(msg_header_t));
	memcpy(buf + sizeof(msg_header_t), &msg.type, sizeof(msg_header_t));
	memcpy(buf + sizeof(msg_header_t) * 2, &msg.id, sizeof(msg_header_t));
	if (len_data > 0) {
		memcpy(buf + gamer::msg_header_len(), msg.context, len_data);
	}
}

void MsgManager::DealWithLoginMsg(const Msg& msg, struct bufferevent* bev) {
    printf("[MsgManager::DealWithLoginMsg] msg_type : %d, msg_id : %d", msg.type, msg.id);
	switch ((MsgIDs)msg.id) {
	case MsgIDs::MSG_ID_LOGIN_MY: {
            // TODO : verify password
            char buf[MsgManager::MAX_MSG_LEN] = { 0 };
            protocol::MyLoginMsgProtocol proto;
            proto.set_account("2017");
            proto.set_password(2018);
            proto.set_code(2020);
            proto.SerializeToArray(buf, proto.ByteSize());

            auto len_total = gamer::msg_header_len() + proto.ByteSize();
            gamer::Msg msg = { len_total, 
                (msg_header_t)MsgTypes::C2S_MSG_TYPE_LOGIN,
                (msg_header_t)MsgIDs::MSG_ID_LOGIN_MY, buf }; 
            this->SendMsg(msg, bev);
		}
		break;
	default:
		break;
	}
}

void MsgManager::OnMsgReceived(const Msg& msg, struct bufferevent* bev) {
    switch ((MsgTypes)msg.type) {
    case MsgTypes::C2S_MSG_TYPE_LOGIN: {
            this->DealWithLoginMsg(msg, bev);
        }
        break;
    default:
        break;
    }
}

} // namespace gamer