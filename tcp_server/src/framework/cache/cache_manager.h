/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    cache_manager.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-20
@ description:  cache manager.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_CACHE_MANAGER_H_
#define CONNOR_GAME_SRC_CACHE_MANAGER_H_

#include "base/basic_manager.h"
#include "cpp_redis/redis_client.hpp" // redis client

namespace gamer {

class CacheManager : public BasicManager<CacheManager> {
  public:
	void Init();

	void GetCachedData(const std::string& key, std::string& value);

    void CacheData(const std::string& key, const std::string& value);

	int GeneratePlayerID();

	void UpdateAvailablePlayerID();

	inline cpp_redis::redis_client& redis_client();

  private:
	enum PlayerIDRanges {
		PLAYER_ID_RANGES_1			= 1000000,
		PLAYER_ID_RANGES_2			= 2000000,
		PLAYER_ID_RANGES_3			= 3000000,
		PLAYER_ID_RANGES_4			= 4000000,
		PLAYER_ID_RANGES_5			= 5000000,
		PLAYER_ID_RANGES_6			= 6000000,
		PLAYER_ID_RANGES_7			= 7000000,
		PLAYER_ID_RANGES_8			= 8000000,
		PLAYER_ID_RANGES_9			= 9000000
	};

	int available_player_id_ = 10000000;

	cpp_redis::redis_client redis_client_; // use sync_commit
};

}

#endif // CONNOR_GAME_SRC_CACHE_MANAGER_H_