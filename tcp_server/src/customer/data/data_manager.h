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

namespace cpp_redis {
	class redis_client;
}

namespace gamer {

class DataManager : public BasicManager<DataManager> {
  public:
	DataManager();

	void SetPlayerPersonalData(const std::string& player_account, const std::string& serialized_data);

	void GetPlayerPersonalData(const std::string& player_account, std::string& serialized_data);

	void SetCreateRoomData(int room_id, const std::string& serialized_data);

	void GetCreateRoomData(int room_id, std::string& serialized_data);

	void SetGameStartData(int room_id, int round, const std::string& serialized_data);

	void GetGameStartData(int room_id, int round, std::string& serialized_data);

	int GeneratePlayerID();

	void UpdateAvailablePlayerID();

  private:
	int available_player_id_ = 10000000;

	cpp_redis::redis_client* redis_client_;
};

}

#endif // CONNOR_GAME_SRC_DATA_MANAGER_H_