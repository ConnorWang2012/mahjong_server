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

struct bufferevent;

namespace gamer {
	
class MsgManager {
  public:
	MsgManager& operator=(const MsgManager&) = delete;

	MsgManager(const MsgManager&) = delete;

	void *operator new(std::size_t) = delete;
	
	static MsgManager* instance();

    bool SendMsg(const Msg& msg);

  private:
    std::unordered_map<std::string, MsgResponseCallback> msg_response_callbacks_;

    MsgManager();

	bool SendMsg(const Msg& msg, struct bufferevent* bev);

	void PackMsg(const Msg& msg, char* buf, msg_header_t& len);

    void DealWithLoginMsg(const Msg& msg, struct bufferevent* bev);

    void OnMsgReceived(const Msg& msg, struct bufferevent* bev);

    friend class NetworkManager;

    static const int MAX_MSG_LEN = 4096;
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_MSG_MANAGER_H_