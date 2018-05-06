/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    robot.cc
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2018-05-06
@ description:  robot.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#include "robot.h"

namespace gamer {
	
Robot::Robot(id_t  player_id)
	: Player(player_id, PlayerTypes::ROBOT, Sex::FEMALE){
}

} // namespace gamer