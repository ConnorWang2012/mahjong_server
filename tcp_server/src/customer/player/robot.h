/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    robot.h
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

#ifndef CONNOR_GAME_SRC_ROBOT_H_
#define CONNOR_GAME_SRC_ROBOT_H_

#include "customer/player/player.h"


namespace gamer {

class Robot : public Player {
  public:
	Robot(id_t player_id);
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_ROBOT_H_