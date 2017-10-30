/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    msg.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-05-01
@ description:  msg protocol.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_MSG_PROTOCOL_H_
#define CONNOR_GAME_SRC_MSG_PROTOCOL_H_

#include <functional>

namespace gamer
{

#ifdef _WIN64
	typedef __int64         intptr_t;
#else
	typedef int             intptr_t;
#endif

#ifdef _WIN32
#define socket_t			intptr_t
#else
#define socket_t			int
#endif

#define msg_header_t		unsigned int

// msg  for client to server
struct ClientMsg {
	msg_header_t total_len;
	msg_header_t type;
	msg_header_t id;
    void* context;
};

// msg for server to client
struct ServerMsg {
    msg_header_t total_len;
    msg_header_t type;
    msg_header_t id;
    msg_header_t code; // msg response code
    void* context;
};

constexpr msg_header_t client_msg_header_len() {  return sizeof(msg_header_t) * 3; }

constexpr msg_header_t server_msg_header_len() { return sizeof(msg_header_t) * 4; }

} // namespace gamer

#endif // CONNOR_GAME_SRC_MSG_PROTOCOL_H_