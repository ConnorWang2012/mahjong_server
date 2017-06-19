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

template<typename Player>
class RoomManager : public BasicManager<RoomManager<Player>> {
  public:
    void AddRoom(Room<Player>* room);

    void RemoveRoom(Room<Player>* room);

    void RemoveRoom(int room_id);

    Room<Player>* GetRoom(int room_id);

    int GenerateRoomID();

  private:
    std::unordered_map<int, Room<Player>*> rooms_; // key is room id
};

template<typename Player>
void gamer::RoomManager<Player>::AddRoom(Room<Player>* room) {
    if (nullptr == room)
        return;

    auto room_id = room->get_create_room_msg_protocol()->room_id();
    if (rooms_.find(room_id) == rooms_.end()) {
        rooms_.insert(std::make_pair(room_id, room));
    }
}

template<typename Player>
void gamer::RoomManager<Player>::RemoveRoom(int room_id) {
}

template<typename Player>
void gamer::RoomManager<Player>::RemoveRoom(Room<Player>* room) {

}

template<typename Player>
gamer::Room<Player>* gamer::RoomManager<Player>::GetRoom(int room_id) {
    auto itr = rooms_.find(room_id);
    if (itr != rooms_.end()) {
        return itr->second;
    }
    return nullptr;
}

template<typename Player>
int gamer::RoomManager<Player>::GenerateRoomID() {
    auto try_count = 5;
    auto count = 0;
    while (count < try_count) {
        auto r = gamer::GenerateRandom<int>(0, 999999);
        if (rooms_.find(r) == rooms_.end()) {
            return r;
        }
        ++count;
    }
    return -1;
}

} // namespace gamer

#endif // CONNOR_GAME_SRC_ROOM_MANAGER_H_