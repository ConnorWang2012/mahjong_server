/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    msg_id.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-05-01
@ description:  msg id.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_MSG_ID_H_
#define CONNOR_GAME_SRC_MSG_ID_H_

namespace gamer {

enum class MsgIDs {
	MSG_ID_UNKNOW					= 0,

	// login
	// c2s, s2c
    MSG_ID_LOGIN_3RD_PARTY          = 1,
    MSG_ID_LOGIN_MY                 = 2,
    
	// room
	// c2s, s2c
	MSG_ID_ROOM_CREATE              = 3,
	MSG_ID_ROOM_PLAYER_JOIN			= 4,
	MSG_ID_ROOM_PLAYER_LEAVE		= 5,
	MSG_ID_ROOM_DISSOLVE			= 6,
    MSG_ID_ROOM_START_GAME          = 7,
	MSG_ID_ROOM_PLAY_CARD			= 8,
    MSG_ID_ROOM_GAME_END            = 9, // game end for one round
    MSG_ID_ROOM_FINAL_GAME_END      = 10,
	MSG_ID_ROOM_GET_ROOM_LIST       = 11,

	// property
	// c2s, s2c
	MSG_ID_PROPERTY_SET				= 12,

	// s2c
	MSG_ID_PROPERTY_CHANGED			= 13,

	// c2s, s2c
	MSG_ID_PROPERTY_GET_PLAYER_INFO = 14,
};

}

#endif // CONNOR_GAME_SRC_MSG_ID_H_