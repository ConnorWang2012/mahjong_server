/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    room_protocol.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-10
@ description:  room protocol(interface).
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_ROOM_PROTOCOL_H_
#define CONNOR_GAME_SRC_ROOM_PROTOCOL_H_

namespace gamer {

class RoomProtocol {
  public:
    virtual ~RoomProtocol() {};

    virtual void DissolveRoom(int room_id) = 0;

    virtual void AddPlayer(int player_id) = 0;

    virtual void RomovePlayer(int player_id) = 0;
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_ROOM_PROTOCOL_H_