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

bool PlayerManager::IsPlayerOnline(int player_id) const {
	return bufferevents_.find(player_id) != bufferevents_.end();
}

void PlayerManager::AddOnlinePlayerBufferevent(int player_id, bufferevent* bev) {
	if (bufferevents_.find(player_id) == bufferevents_.end()) {
		bufferevents_.insert(std::make_pair(player_id, bev));
	}
}

bufferevent* PlayerManager::GetOnlinePlayerBufferevent(int player_id) {
	auto itr = bufferevents_.find(player_id);
	if (itr != bufferevents_.end()) {
		return itr->second;
	}
	return nullptr;
}

void PlayerManager::AddOnlinePlayer(int player_id, Player* player) {
	if (players_.find(player_id) == players_.end()) {
		players_.insert(std::make_pair(player_id, player));
	}
}

Player* PlayerManager::GetOnlinePlayer(int player_id) {
	auto itr = players_.find(player_id);
	if (itr != players_.end()) {
		return itr->second;
	}
	return nullptr;
}

void PlayerManager::RemoveOnlinePlayer(int player_id) {
	auto it = bufferevents_.find(player_id);
	if (it != bufferevents_.end()) {
		bufferevents_.erase(it);
	}
}

void PlayerManager::RemoveOnlinePlayer(bufferevent* bev) {
    if (nullptr == bev)
        return;
    for (auto itr = bufferevents_.begin(); itr != bufferevents_.end(); ++itr) {
        if (itr->second == bev) {
            bufferevents_.erase(itr);
            break;
        }
    }
}

} // namespace gamer