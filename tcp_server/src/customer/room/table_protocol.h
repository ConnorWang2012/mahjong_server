/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    table_protocol.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2018-04-21
@ description:  table protocol(interface).
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_TABLE_PROTOCOL_H_
#define CONNOR_GAME_SRC_TABLE_PROTOCOL_H_

#include "framework/base/macros.h"

namespace gamer {

template<typename Player>
class TableProtocol {
  public:
    virtual ~TableProtocol() {};

    virtual void AddPlayer(Player* player) = 0;

    virtual void RomovePlayer(id_t player_id) = 0;    

	virtual inline Player* player(id_t player_id) = 0;

	virtual inline std::vector<Player*>* players() = 0;

	virtual inline void set_table_id(id_t room_id) = 0;

	virtual inline id_t table_id() const = 0;

    virtual inline bool is_player_in_table(id_t player_id) const = 0;

    virtual inline size_t cur_players_num() const = 0;

	virtual inline size_t required_players_num() const = 0;
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_TABLE_PROTOCOL_H_