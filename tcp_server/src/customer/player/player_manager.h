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

#include "framework/base/basic_manager.h"
#include "framework/base/macros.h"

struct bufferevent;

namespace gamer {

class Event;
class Player;

class PlayerManager : public BasicManager<PlayerManager> {
  public:
	void Init();

	bool IsPlayerOnline(id_t player_id) const;

	bufferevent* GetOnlinePlayerBufferevent(id_t player_id);

	// keep the ownership of player, not keep the ownership of bev
	void AddOnlinePlayer(id_t player_id, Player* player, bufferevent* bev);

	Player* GetOnlinePlayer(id_t player_id); // still keep the ownership

	void RemoveOnlinePlayer(id_t player_id);

    void RemoveOnlinePlayer(bufferevent* bev);

	std::string GenerateAccountByPlayerID(id_t player_id) const;

  private:
	void OnSocketDisconnected(const gamer::Event& event);

	std::unordered_map<id_t, Player*> players_; // key is player id

	std::unordered_map<id_t, bufferevent*> bufferevents_; // key is player id
};

}

#endif // CONNOR_GAME_SRC_PLAYER_MANAGER_H_