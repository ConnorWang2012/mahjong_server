/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    config_manager.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-11-17
@ description:  cfg manager.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_CONFIG_MANAGER_H_
#define CONNOR_GAME_SRC_CONFIG_MANAGER_H_

#include <string>

#include "framework/base/basic_manager.h"

namespace gamer {

namespace protocol {

class RoomListMsgProtocol;

}

class ConfigManager : public BasicManager<ConfigManager> {
  public:
	typedef gamer::protocol::RoomListMsgProtocol RoomListMsgProtocol;

	ConfigManager();

	void Init();

	inline RoomListMsgProtocol* room_list_msg_protocol();

  private:
	RoomListMsgProtocol* room_list_proto_;
};

inline ConfigManager::RoomListMsgProtocol* ConfigManager::room_list_msg_protocol() {
	return room_list_proto_;
}

}

#endif // CONNOR_GAME_SRC_CONFIG_MANAGER_H_