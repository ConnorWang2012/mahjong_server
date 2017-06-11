/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    room.cc
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

#include "room.h"

#include "base/macros.h"
#include "msg/protocol/create_room_msg_protocol.pb.h"

namespace gamer {

Room * gamer::Room::Create(int room_id, const protocol::CreateRoomMsgProtocol& proto) {
    auto room = new Room();
    if (nullptr != room) {
        if ( !room->Init(room_id, proto) ) {
            SAFE_DELETE(room);
            return nullptr;
        }
    }
    return room;
}

void Room::DissolveRoom(int room_id) {

}

void Room::AddPlayer(int player_id) {

}

void Room::RomovePlayer(int player_id) {

}

bool Room::Init(int room_id, const protocol::CreateRoomMsgProtocol& proto) {
    room_msg_proto_.set_room_id(room_id);
    room_msg_proto_.set_players_num(proto.players_num());
    room_msg_proto_.set_total_round(proto.rounds_num());
    // TODO : init more info
    return true;
}

}