/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    room.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-10
@ description:  room base.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_ROOM_H_
#define CONNOR_GAME_SRC_ROOM_H_

#include "msg/protocol/room_msg_protocol.pb.h"
#include "room/room_protocol.h"

namespace gamer {

    namespace protocol {
        class CreateRoomMsgProtocol;
    }

class Room : public RoomProtocol {
  public:
    Room& operator=(const Room&) = delete;

    Room(const Room&) = delete;

    static Room* Create(int room_id, const protocol::CreateRoomMsgProtocol& proto);

    virtual void DissolveRoom(int room_id) override;

    virtual void AddPlayer(int player_id) override;

    virtual void RomovePlayer(int player_id) override;

  private:    
    Room() = default;

    bool Init(int room_id, const protocol::CreateRoomMsgProtocol& proto);

    inline protocol::RoomMsgProtocol& get_room_msg_protocol() {
        return room_msg_proto_;
    }

    friend class RoomManager;

    protocol::RoomMsgProtocol room_msg_proto_;
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_ROOM_H_