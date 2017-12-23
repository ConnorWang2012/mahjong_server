/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    property_id.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-05-01
@ description:  player property(which can be modified by player) id.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_PROPERTY_ID_H_
#define CONNOR_GAME_SRC_PROPERTY_ID_H_

namespace gamer {

enum class PropertyIDs {
	PROP_ID_UNKNOW				= 0,
	PROP_ID_NICKNAME			= 1,
	PROP_ID_SEX					= 2
};

}

#endif // CONNOR_GAME_SRC_PROPERTY_ID_H_