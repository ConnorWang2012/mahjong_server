﻿/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    room_constants.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2018-03-19
@ description:  room constants.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_ROOM_CONSTANTS_H_
#define CONNOR_GAME_SRC_ROOM_CONSTANTS_H_

namespace gamer {

enum class RoomTypes {
	UNKNOW_ROOM,
	COMMON_ROOM,
    PERSONAL_ROOM
};

enum class TableIDs {
	TABLE_ID_INVALID,
	TABLE_ID_1                      = 1,
	TABLE_ID_MAX                    = 5
};

enum class RoomConstants {
	ROOM_OWNER_ID_COMMON           = 8888,
	REQUIRED_PLAYERS_NUM_2         = 2,
	REQUIRED_PLAYERS_NUM_3         = 3,
	REQUIRED_PLAYERS_NUM_4         = 4,
	TABLE_NUM_MAX                  = 10
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_ROOM_CONSTANTS_H_