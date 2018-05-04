/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    table.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2018-04-21
@ description:  table base.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#include <vector>

#include "customer/room/table_protocol.h"
#include "customer/msg/protocol/table_msg_protocol.pb.h"

namespace gamer {
	
template<typename Player>
class Table : public TableProtocol<Player> {
  public:
	typedef gamer::protocol::TableMsgProtocol    TableMsgProtocol;

    Table& operator=(const Table&) = delete;

	Table(const Table&) = delete;

	static Table* Create(id_t table_id);

	virtual void AddPlayer(Player* player) override;

	virtual void RomovePlayer(id_t player_id) override;

	virtual inline std::vector<Player*>* players() override;

	virtual inline Player* player(id_t player_id) override;

	virtual inline void set_table_id(id_t table_id) override;

	virtual inline id_t table_id() const override;

	virtual inline bool is_player_in_table(id_t player_id) const override;

	virtual inline size_t cur_players_num() const override;

  private:
	Table();

	bool Init(id_t table_id);

	TableMsgProtocol table_msg_proto_;

	std::vector<Player*> players_;
};

template<typename Player>
gamer::Table<Player>::Table() {
	table_msg_proto_.set_table_id(0);
}

template<typename Player>
gamer::Table<Player>* Table<Player>::Create(id_t table_id) {
	auto table = new Table<Player>();
	if (nullptr != table) {
		if ( !table->Init(table_id) ) {
			SAFE_DELETE(table);
			return nullptr;
		}
	}
	return table;
}

template<typename Player>
void gamer::Table<Player>::AddPlayer(Player* player) {
	auto itr = std::find(players_.begin(), players_.end(), player);
	if (itr == players_.end()) {
		players_.push_back(player);
	}
}

template<typename Player>
void gamer::Table<Player>::RomovePlayer(id_t player_id) {
	auto itr = std::find_if(players_.begin(),
		                    players_.end(),
		                    [=](const Player* player) {
		                        return (player->player_id() == player_id);
	                        });
	if (itr != players_.end()) {
		players_.erase(itr);
	}
}

template<typename Player>
inline Player* Table<Player>::player(id_t player_id) {
	for (auto& p : players_) {
		if (p->player_id() == player_id) {
			return p;
		}
	}
	return nullptr;
}

template<typename Player>
inline std::vector<Player*>* gamer::Table<Player>::players() { return &players_; }

template<typename Player>
inline void Table<Player>::set_table_id(id_t table_id) { table_msg_proto_.set_table_id(table_id); }

template<typename Player>
inline id_t Table<Player>::table_id() const { return table_msg_proto_.table_id(); }

template<typename Player>
bool gamer::Table<Player>::is_player_in_table(id_t player_id) const {
	for (auto& p : players_) {
		if (p->player_id() == player_id) {
			return true;
		}
	}
	return false;
}

template<typename Player>
inline size_t gamer::Table<Player>::cur_players_num() const { return players_.size(); }

template<typename Player>
bool Table<Player>::Init(id_t table_id) {
	table_msg_proto_.set_table_id(table_id);
	return true;
}

}