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

#include "framework/base/macros.h"

namespace gamer {

enum class RoomTypes;

template<typename Player>
class RoomProtocol {
  public:
    virtual ~RoomProtocol() {};

    virtual void DissolveRoom(id_t room_id) = 0;

    virtual void AddPlayer(Player* player) = 0;

    virtual void RomovePlayer(id_t player_id) = 0;    

	virtual inline Player* player(id_t player_id) = 0;

	virtual inline std::vector<Player*>* players() = 0;

	virtual inline void set_room_id(id_t room_id) = 0;

	virtual inline id_t room_id() const = 0;

	virtual inline void set_room_type(RoomTypes room_id) = 0;

	virtual inline RoomTypes room_type() const = 0;

    virtual inline bool is_player_in_room(id_t player_id) const = 0;

	virtual inline size_t cur_tables_num() const = 0;

	virtual inline size_t max_tables_num() const = 0;

	virtual inline void set_cur_table_id(id_t table_id) = 0;

	virtual inline id_t cur_table_id() const = 0;

    virtual inline size_t cur_players_num() const = 0;
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_ROOM_PROTOCOL_H_