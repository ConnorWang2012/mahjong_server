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

typedef std::function<void(unsigned int, unsigned int, void*)> MsgResponseCallback;

struct Msg
{
    unsigned int total_len;
    unsigned int type;
    unsigned int id;
    void* context;
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_MSG_PROTOCOL_H_