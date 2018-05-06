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

#include "framework/base/typedef.h"

namespace gamer {

enum class PlayerTypes;
enum class Sex;

class PlayerProtocol {
  public:
	virtual ~PlayerProtocol() {};

	virtual inline void set_player_id(id_t player_id) = 0;

	virtual inline id_t player_id() const = 0;

	virtual inline void set_is_online(bool online) = 0;

	virtual inline bool is_online() const = 0;

	virtual inline void set_player_type(PlayerTypes player_type) = 0;

	virtual inline PlayerTypes player_type() const = 0;

	virtual inline void set_sex(Sex sex) = 0;

	virtual inline Sex sex() const = 0;
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_PLAYER_PROTOCOL_H_