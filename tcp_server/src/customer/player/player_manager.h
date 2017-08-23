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

	void AddOnlinePlayerBufferevent(int player_id, bufferevent* bev); // not keep the ownership 

	bufferevent* GetOnlinePlayerBufferevent(int player_id);

	void AddOnlinePlayer(int player_id, Player* player); // keep the ownership

	Player* GetOnlinePlayer(int player_id); // still keep the ownership

	void RemoveOnlinePlayer(int player_id);

    void RemoveOnlinePlayer(bufferevent* bev);

  private:
	std::unordered_map<int, Player*> players_; // key is player id

	std::unordered_map<int, bufferevent*> bufferevents_; // key is player id
};

}

#endif // CONNOR_GAME_SRC_PLAYER_MANAGER_H_