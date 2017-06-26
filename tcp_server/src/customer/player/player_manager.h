/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    player_manager.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-26
@ description:  player manager.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_PLAYER_MANAGER_H_
#define CONNOR_GAME_SRC_PLAYER_MANAGER_H_

#include <unordered_map>

#include "base/basic_manager.h"

struct bufferevent;

namespace gamer {

class Player;

class PlayerManager : public BasicManager<PlayerManager> {
  public:
	bool IsPlayerOnline(int player_id) const;

	void AddOnlinePlayer(int player_id, Player* player, bufferevent* bev);

	void RemoveOnlinePlayer(int player_id);

	Player* GetOnlinePlayer(int player_id);

	bufferevent* GetOnlinePlayerBufferevent(int player_id);

  private:
	std::unordered_map<int, Player*> online_players_;
	std::unordered_map<int, bufferevent*> bufferevents_; // key is player id
};

}

#endif // CONNOR_GAME_SRC_PLAYER_MANAGER_H_