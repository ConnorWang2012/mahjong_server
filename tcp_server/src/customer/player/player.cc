/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    player.cc
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-14
@ description:  player.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#include "player.h"
#include "base/macros.h"

namespace gamer {

Player::Player()
	:is_online_(false) {
}

Player* Player::Create(int player_id) {
	auto player = new Player;
	if (nullptr != player) {
		if (!player->Init(player_id)) {
			SAFE_DELETE(player);
			return nullptr;
		}
	}
	return player;
}

void Player::set_player_id(int player_id) {
	player_id_ = player_id;
}

int Player::player_id() const {
	return player_id_;
}

void Player::set_is_online(bool online) {
	is_online_ = online;
}

bool Player::is_online() const {
	return is_online_;
}

bool Player::Init(int player_id) {
	player_id_ = player_id;
	return true;
}

}