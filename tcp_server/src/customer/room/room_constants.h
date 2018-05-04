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

enum class RoomConstans {
	TABLE_NUM_MAX = 10
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_ROOM_CONSTANTS_H_