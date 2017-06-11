/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    room_manager.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-10
@ description:  room manager, such as create room, destory room.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_ROOM_MANAGER_H_
#define CONNOR_GAME_SRC_ROOM_MANAGER_H_

#include <string>
#include <unordered_map>

#include "base/basic_manager.h"
#include "room/room.h"

namespace gamer {

class RoomManager : public BasicManager<RoomManager> {
  public:
    void AddRoom(Room* room);

    void RemoveRoom(Room* room);

    void RemoveRoom(int room_id);

    int GenerateRoomID();

  private:
    std::unordered_map<int, Room*> rooms_; // key is room id
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_ROOM_MANAGER_H_
