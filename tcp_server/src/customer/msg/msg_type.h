﻿/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    msg_type.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-05-01
@ description:  msg type.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_MSG_TYPE_H_
#define CONNOR_GAME_SRC_MSG_TYPE_H_

namespace gamer {

enum class MsgTypes {
    // client to server
    C2S_MSG_TYPE_LOGIN				= 1,
    C2S_MSG_TYPE_PROPERTY			= 2,
    C2S_MSG_TYPE_ROOM				= 3,

    // server to client
    S2C_MSG_TYPE_LOGIN				= 1,
    S2C_MSG_TYPE_PROPERTY			= 2,
    S2C_MSG_TYPE_ROOM				= 3
};

}

#endif // CONNOR_GAME_SRC_MSG_TYPE_H_