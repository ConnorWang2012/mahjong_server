/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    room_manager.cc
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-10
@ description:  see the header.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#include "room_manager.h"
#include "util/util.h"

namespace gamer {

void RoomManager::AddRoom(Room* room) {
    auto room_id = room->get_room_msg_protocol().room_id();
    if (nullptr != room && rooms_.find(room_id) != rooms_.end()) {
        rooms_.insert(std::make_pair(room_id, room));
    }
}

void RoomManager::RemoveRoom(int room_id) {
}

void RoomManager::RemoveRoom(Room* room) {

}

int RoomManager::GenerateRoomID() {
    auto try_count = 5;
    auto count = 0;
    while (count < try_count) {
        auto r = gamer::GenerateRandom(0, 999999);
        if (rooms_.find(r) == rooms_.end()) {
            return r;
        }
        ++count;
    }
    return -1;
}

} // namespace gamer