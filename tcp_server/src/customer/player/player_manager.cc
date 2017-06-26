/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    player_manager.cc
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-26
@ description:  see the header.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#include "player_manager.h"

namespace gamer {

bool PlayerManager::IsPlayerOnline(int player_id) const {
	return online_players_.find(player_id) != online_players_.end();
}

void PlayerManager::AddOnlinePlayer(int player_id, Player* player, bufferevent* bev) {
	if (nullptr != player && online_players_.find(player_id) == online_players_.end()) {
		online_players_.insert(std::make_pair(player_id, player));
	}

	if (nullptr != player && bufferevents_.find(player_id) == bufferevents_.end()) {
		bufferevents_.insert(std::make_pair(player_id, bev));
	}
}

Player* PlayerManager::GetOnlinePlayer(int player_id) {
	auto itr = online_players_.find(player_id);
	if (itr != online_players_.end()) {
		return itr->second;
	}
	return nullptr;
}

bufferevent* PlayerManager::GetOnlinePlayerBufferevent(int player_id) {
	auto itr = bufferevents_.find(player_id);
	if (itr != bufferevents_.end()) {
		return itr->second;
	}
	return nullptr;
}

} // namespace gamer