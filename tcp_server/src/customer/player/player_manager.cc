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

#include <algorithm>

namespace gamer {

bool PlayerManager::IsPlayerOnline(id_t player_id) const {
	return bufferevents_.find(player_id) != bufferevents_.end();
}

bufferevent* PlayerManager::GetOnlinePlayerBufferevent(id_t player_id) {
	auto itr = bufferevents_.find(player_id);
	if (itr != bufferevents_.end()) {
		return itr->second;
	}
	return nullptr;
}

void PlayerManager::AddOnlinePlayer(id_t player_id, Player* player, bufferevent* bev) {
	if (players_.find(player_id) == players_.end()) {
		players_.insert(std::make_pair(player_id, player));
	}
	if (bufferevents_.find(player_id) == bufferevents_.end()) {
		bufferevents_.insert(std::make_pair(player_id, bev));
	}
}

Player* PlayerManager::GetOnlinePlayer(id_t player_id) {
	auto itr = players_.find(player_id);
	if (itr != players_.end()) {
		return itr->second;
	}
	return nullptr;
}

void PlayerManager::RemoveOnlinePlayer(id_t player_id) {
	auto it = players_.find(player_id);
	if (it != players_.end()) {
		players_.erase(it);
	}

	auto itr = bufferevents_.find(player_id);
	if (itr != bufferevents_.end()) {
		bufferevents_.erase(itr);
	}
}

void PlayerManager::RemoveOnlinePlayer(bufferevent* bev) {
	if (nullptr != bev) {
		// TODO : some kind of ugly
		for (auto itr = bufferevents_.begin(); itr != bufferevents_.end(); ++itr) {
			if (itr->second == bev) {
                auto it = players_.find(itr->first);
                if (it != players_.end()) {
                    players_.erase(it);
                }

				bufferevents_.erase(itr);

				break;
			}
		}
	}
}

} // namespace gamer