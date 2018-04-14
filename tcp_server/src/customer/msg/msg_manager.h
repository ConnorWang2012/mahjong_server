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

#include "framework/base/basic_manager.h"
#include "framework/base/macros.h"
#include "framework/base/msg.h"

namespace google {

namespace protobuf {
	class Message;
}

}

struct bufferevent;

namespace gamer {

enum class MsgCodes;

class MsgManager : public BasicManager<MsgManager> {
  public:
	MsgManager() = default;

    void Init();

    bool SendMsg(const ServerMsg& msg, bufferevent* bev);

    bool SendMsg(msg_header_t msg_type,
                 msg_header_t msg_id,
                 msg_header_t msg_code,
                 const google::protobuf::Message& msg, 
                 bufferevent* bev);

  private:
    typedef std::function<void(const ClientMsg&, bufferevent* bev)> MsgHandler;

	void AddMsgDispatchers();

	void AddMsgHandlers();

	void OnMsgReceived(const ClientMsg& msg, bufferevent* bev);

	void DealWithLoginMsg(const ClientMsg& msg, bufferevent* bev);

	void DealWithPropertyMsg(const ClientMsg& msg, bufferevent* bev);

	void DealWithRoomMsg(const ClientMsg& msg, bufferevent* bev);

	void DealWithMgLoginMsg(const ClientMsg& msg, bufferevent* bev);

	void DealWithGetPlayerInfoMsg(const ClientMsg& msg, bufferevent* bev);

	void DealWithSetPropertyMsg(const ClientMsg& msg, bufferevent* bev);

	void DealWithSetNicknameMsg(const ClientMsg& msg, bufferevent* bev, 
		google::protobuf::Message* proto, id_t player_id, const std::string& nickname);

	void DealWithSetSexMsg(const ClientMsg& msg, bufferevent* bev,
		google::protobuf::Message* proto, id_t player_id, const std::string& sex);

	void DealWithSetLocalHeadPortraitMsg(const ClientMsg& msg, bufferevent* bev,
		google::protobuf::Message* proto, id_t player_id, const std::string& head_portrait_id);

	void DealWithCreateRoomMsg(const ClientMsg& msg, bufferevent* bev);

	void DealWithPlayerJoinRoomMsg(const ClientMsg& msg, bufferevent* bev);

	void DealWithPlayerLeaveRoomMsg(const ClientMsg& msg, bufferevent* bev);

	void DealWithGetRoomListMsg(const ClientMsg& msg, bufferevent* bev);

	void DealWithStartGameMsg(const ClientMsg& msg, bufferevent* bev);

	void DealWithPlayCardMsg(const ClientMsg& msg, bufferevent* bev);

	bool PackMsg(const ServerMsg& msg, char* buf, msg_header_t& len);

    bool PackMsg(msg_header_t msg_type,
                 msg_header_t msg_id,
                 msg_header_t msg_code,
                 const google::protobuf::Message& msg,
                 char* buf,
                 msg_header_t& len);

    bool ParseMsg(const ClientMsg& msg, google::protobuf::Message* proto);

	void SendMsgForError(gamer::MsgCodes error_code, const ClientMsg& msg, bufferevent* bev);

    friend class NetworkManager;

    std::unordered_map<id_t, MsgHandler> msg_handlers_;    // key is MsgIDs
    std::unordered_map<id_t, MsgHandler> msg_dispatchers_; // key is MsgTypes

    static const int MAX_MSG_LEN = 4096;
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_MSG_MANAGER_H_