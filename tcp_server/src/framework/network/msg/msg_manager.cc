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

#include "msg_type.h"
#include "network_manager.h"

namespace gamer
{

MsgManager::MsgManager()
{

}

MsgManager* MsgManager::getInstance()
{
	static MsgManager s_msg_mgr; 
	return &s_msg_mgr;
}

bool MsgManager::sendMsg(const Msg& msg, const MsgResponseCallback& response_cb)
{
    char buf[MsgManager::MAX_MSG_LEN] = { 0 };
    auto len_total = sizeof(unsigned int) * 3;
    auto len_data = 0;
    //snprintf(buf, sizeof(buf), "%d%d%d%s", msg.type, msg.id, msg.context);    
    if (msg.context)
    {
        len_data = strlen((char*)msg.context);
        len_total += len_data;
    }
    
    memcpy(buf, &len_total, sizeof(unsigned int));
    memcpy(buf + sizeof(unsigned int), &msg.type, sizeof(unsigned int));
    memcpy(buf + sizeof(unsigned int) * 2, &msg.id, sizeof(unsigned int));
    if (len_data > 0)
    {
        memcpy(buf + sizeof(unsigned int) * 3, msg.context, len_data);
    }

    //char tmp[8]; // ugly TODO : use c++11 constexpress
    //snprintf(tmp, sizeof(tmp), "%d%d", msg.type, msg.id);
    //msg_response_callbacks_.insert(std::make_pair(tmp, response_cb));

    //return NetworkManager::instance()->send(buf, len_total);
    return true;
}

void MsgManager::dealWithLoginMsg(const Msg& msg)
{
    printf("msg callback msg_type : %d, msg_id : %d", msg.type, msg.id);
}

void MsgManager::onMsgReceived(const Msg& msg)
{
    switch ((MsgTypes)msg.type)
    {
    case MsgTypes::C2S_MSG_TYPE_LOGIN:
        {
            this->dealWithLoginMsg(msg);
        }
        break;
    default:
        break;
    }
}

} // namespace gamer