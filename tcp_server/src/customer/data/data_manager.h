/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    data_manager.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-20
@ description:  data manager.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_DATA_MANAGER_H_
#define CONNOR_GAME_SRC_DATA_MANAGER_H_

#include <string>

#include "base/basic_manager.h"
#include "base/macros.h"

namespace cpp_redis {
	class redis_client;
}

namespace gamer {

class DataManager : public BasicManager<DataManager> {
  public:
	DataManager();

	void CacheAccountData(const std::string& account, id_t player_id, const std::string& password);

	void GetCacheAccountData(const std::string& account, id_t* player_id, std::string* password);

	void CachePlayerPersonalData(id_t player_id, const std::string& serialized_data);

	void GetCachedPlayerPersonalData(id_t player_id, std::string* serialized_data);

	void CacheCreateRoomData(id_t room_id, const std::string& serialized_data);

	void GetCachedCreateRoomData(id_t room_id, std::string& serialized_data);

	void CacheGameStartData(id_t room_id, const std::string& serialized_data);

	void GetCachedGameStartData(id_t room_id, std::string& serialized_data);

	void CacheRoomData(id_t room_id, int round, const std::string& serialized_data);

	void GetCachedRoomData(id_t room_id, int round, std::string& serialized_data);

	id_t GeneratePlayerID();

	void UpdateAvailablePlayerID();

	void CacheAccountByID(id_t player_id, const std::string& player_account);

	void GetCachedAccountByID(id_t player_id, std::string* player_account);

    // async
	void SetGold(id_t player_id, score_t gold);

	void GetGold(id_t player_id, score_t& gold) const;

	void SetDiamond(id_t player_id, score_t diamond);

	void GetDiamond(id_t player_id, score_t& diamond) const;

	void AddGold(id_t player_id, score_t gold);

	void AddDiamond(id_t player_id, score_t diamond);

  private:
	void Init();

	id_t available_player_id_ = 1000;

	cpp_redis::redis_client* redis_client_;
};

}

#endif // CONNOR_GAME_SRC_DATA_MANAGER_H_