/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    msg_manager.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-05-01
@ description:  msg manager, such as msg send, msg receive.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_MSG_MANAGER_H_
#define CONNOR_GAME_SRC_MSG_MANAGER_H_

#include <string>
#include <unordered_map>

#include "msg.h"

namespace gamer
{

class MsgManager
{
public:
	MsgManager& operator=(const MsgManager&) = delete;

	MsgManager(const MsgManager&) = delete;

	void *operator new(std::size_t) = delete;
	
	static MsgManager* getInstance();

    bool sendMsg(const Msg& msg, const MsgResponseCallback& response_cb);

private:
    std::unordered_map<std::string, MsgResponseCallback> msg_response_callbacks_;

    MsgManager();

    void dealWithLoginMsg(const Msg& msg);

    void onMsgReceived(const Msg& msg);

    friend class NetworkManager;

    static const int MAX_MSG_LEN = 4096;
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_MSG_MANAGER_H_