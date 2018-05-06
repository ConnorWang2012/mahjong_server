/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    player_constants.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2018-05-06
@ description:  player constants.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_PLAYER_CONSTANTS_H_
#define CONNOR_GAME_SRC_PLAYER_CONSTANTS_H_

namespace gamer {

enum class PlayerTypes {
	REAL_PLAYER,
	ROBOT
};

enum class Sex {
	MALE,
	FEMALE
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_PLAYER_CONSTANTS_H_