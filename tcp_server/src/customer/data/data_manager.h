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

	void CachePlayerPersonalData(const std::string& player_account, const std::string& serialized_data);

	void GetCachedPlayerPersonalData(const std::string& player_account, std::string& serialized_data);

	void CacheCreateRoomData(int room_id, const std::string& serialized_data);

	void GetCachedCreateRoomData(int room_id, std::string& serialized_data);

	void CacheGameStartData(int room_id, const std::string& serialized_data);

	void GetCachedGameStartData(int room_id, std::string& serialized_data);

	void CacheRoomData(int room_id, int round, const std::string& serialized_data);

	void GetCachedRoomData(int room_id, int round, std::string& serialized_data);

	int GeneratePlayerID();

	void UpdateAvailablePlayerID();

    // async
	void SetGold(id_t player_id, score_t gold);

	void GetGold(id_t player_id, score_t& gold) const;

	void SetDiamond(id_t player_id, score_t diamond);

	void GetDiamond(id_t player_id, score_t& diamond) const;

	void AddGold(id_t player_id, score_t gold);

	void AddDiamond(id_t player_id, score_t diamond);

  private:
	void Init();

	int available_player_id_ = 10000000;

	cpp_redis::redis_client* redis_client_;
};

}

#endif // CONNOR_GAME_SRC_DATA_MANAGER_H_