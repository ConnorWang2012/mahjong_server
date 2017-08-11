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

#include <unordered_map>

namespace gamer {

template<typename Player>
class RoomProtocol {
  public:
    virtual ~RoomProtocol() {};

    virtual void DissolveRoom(int room_id) = 0;

    virtual void AddPlayer(Player* player) = 0;

    virtual void RomovePlayer(int player_id) = 0;    

	virtual inline void set_room_id(int room_id) = 0;

	virtual inline int room_id() const = 0;

	virtual inline Player* player(int player_id) = 0;

    virtual inline std::vector<Player*>* players() = 0;

    virtual inline bool is_player_in_room(int player_id) const = 0;

    virtual inline int cur_players_num() const = 0;
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_ROOM_PROTOCOL_H_