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

#include "base/macros.h"
#include "msg/msg.h"

namespace google
{
    namespace protobuf
    {
        class Message;
    }
}

struct bufferevent;

namespace gamer {
	
class MsgManager {
  public:
	MsgManager& operator=(const MsgManager&) = delete;

	MsgManager(const MsgManager&) = delete;

	void *operator new(std::size_t) = delete;
	
	static MsgManager* instance();

    bool SendMsg(const ServerMsg& msg, bufferevent* bev);

    bool SendMsg(msg_header_t msg_type,
                 msg_header_t msg_id,
                 msg_header_t msg_code,
                 const google::protobuf::Message& msg, 
                 bufferevent* bev);

  private:
    typedef std::function<void(const ClientMsg&, bufferevent* bev)> MsgHandler;

    MsgManager();

    void Init();

    void AddMsgDispatchers();

    void AddMsgHandlers();

	bool PackMsg(const ServerMsg& msg, char* buf, msg_header_t& len);

    bool PackMsg(msg_header_t msg_type,
                 msg_header_t msg_id,
                 msg_header_t msg_code,
                 const google::protobuf::Message& msg,
                 char* buf,
                 msg_header_t& len);

    bool ParseMsg(const ClientMsg& msg, google::protobuf::Message& proto);

    void DealWithLoginMsg(const ClientMsg& msg, bufferevent* bev);

    void DealWithMgLoginMsg(const ClientMsg& msg, bufferevent* bev);
    
    void DealWithRoomMsg(const ClientMsg& msg, bufferevent* bev);

    void DealWithCreateRoomMsg(const ClientMsg& msg, bufferevent* bev);

    void DealWithStartGameMsg(const ClientMsg& msg, bufferevent* bev);

	void SendMsgForError(msg_header_t error_code, const ClientMsg& msg, bufferevent* bev);

    void OnMsgReceived(const ClientMsg& msg, bufferevent* bev);

    friend class NetworkManager;

    std::unordered_map<int, MsgHandler> msg_handlers_;    // key is MsgIDs
    std::unordered_map<int, MsgHandler> msg_dispatchers_; // key is MsgTypes

	std::unordered_map<std::string, bufferevent*> bufferevents_; // key is user account

    static const int MAX_MSG_LEN = 4096;
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_MSG_MANAGER_H_