/*******************************************************************************
 @ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
 @ filename:	  special_typedef.h
 @ author:		  Connor
 @ version:	      1.0.0
 @ date:		  2018-04-23
 @ description:   define special type.
 @ others:
 @ history:
 1.date:
 author:
 modification:
 ********************************************************************************/

#ifndef CONNOR_GAME_SRC_SPECIAL_TYPEDEF_H_
#define CONNOR_GAME_SRC_SPECIAL_TYPEDEF_H_

#include "customer/player/player.h"
#include "customer/room/room.h"
#include "customer/room/room_manager.h"

namespace gamer {

class Player;

template class Room<Player>;
template class RoomManager<Player>;

} // namespace gamer

#endif // CONNOR_GAME_SRC_SPECIAL_TYPEDEF_H_
