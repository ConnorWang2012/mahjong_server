/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    player_protocol.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-14
@ description:  player protocol(interface).
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_PLAYER_PROTOCOL_H_
#define CONNOR_GAME_SRC_PLAYER_PROTOCOL_H_

#include <vector>

namespace gamer {

class PlayerProtocol {
  public:
	virtual ~PlayerProtocol() {};

	virtual void set_player_id(int player_id) = 0;

	virtual int player_id() const = 0;

	virtual void set_is_online(bool online) = 0;

	virtual bool is_online() const = 0;
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_PLAYER_PROTOCOL_H_