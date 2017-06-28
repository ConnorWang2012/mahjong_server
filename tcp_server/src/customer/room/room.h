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

#include <unordered_map>
#include <vector>

#include "msg/protocol/room_msg_protocol.pb.h"
#include "room/room_protocol.h"

namespace gamer {

template<typename Player>
class Room : public RoomProtocol<Player> {
  public:
    Room& operator=(const Room&) = delete;

    Room(const Room&) = delete;

    static Room* Create(int room_id);

    virtual void DissolveRoom(int room_id) override; // TODO :

    virtual void AddPlayer(int player_id, Player* player) override; // not keep the ownership

    virtual void RomovePlayer(int player_id) override;

	virtual inline void set_room_id(int room_id) override;

	virtual inline int room_id() const override;

	virtual inline Player* player(int player_id) override;

    virtual inline std::unordered_map<int, Player*>* players() override;

    virtual inline bool is_player_in_room(int player_id) const override;
    
    virtual inline int cur_players_num() const override;

	inline void set_room_msg_protocol(const std::string& serialized_data);

    inline protocol::RoomMsgProtocol* get_room_msg_protocol();
	
  private:    
    Room();

    bool Init(int room_id);

    protocol::RoomMsgProtocol room_msg_proto_;

	int room_id_;

    std::unordered_map<int, Player*> players_;

    std::vector<int> all_cards_;
};

template<typename Player>
gamer::Room<Player>::Room()
	:room_id_(0) {

}

template<typename Player>
gamer::Room<Player>* Room<Player>::Create(int room_id) {
    auto room = new Room<Player>();
    if (nullptr != room) {
        if ( !room->Init(room_id) ) {
            SAFE_DELETE(room);
            return nullptr;
        }
    }
    return room;
}

template<typename Player>
void gamer::Room<Player>::DissolveRoom(int room_id) {

}

template<typename Player>
void gamer::Room<Player>::AddPlayer(int player_id, Player* player) {
    if (players_.find(player_id) == players_.end()) {
        players_.insert(std::make_pair(player_id, player));
    }
}

template<typename Player>
void gamer::Room<Player>::RomovePlayer(int player_id) {
	auto itr = players_.find(player_id);
	if (itr != players_.end()) {
		players_.erase(itr);
	}
}

template<typename Player>
inline void Room<Player>::set_room_id(int room_id) {
	room_id_ = room_id;
}

template<typename Player>
inline int Room<Player>::room_id() const {
	return room_id_;
}

template<typename Player>
inline Player* Room<Player>::player(int player_id) {
	auto itr = players_.find(player_id);
	if (itr != players_.end()) {
		return itr->second;
	}
	return nullptr;
}

template<typename Player>
std::unordered_map<int, Player*>* gamer::Room<Player>::players() {
    return &players_;
}

template<typename Player>
bool gamer::Room<Player>::is_player_in_room(int player_id) const {
    return players_.find(player_id) != players_.end();
}

template<typename Player>
int gamer::Room<Player>::cur_players_num() const {
    return (int)players_.size();
}

template<typename Player>
void Room<Player>::set_room_msg_protocol(const std::string& serialized_data) {
	room_msg_proto_.ParseFromString(serialized_data);
}

template<typename Player>
protocol::RoomMsgProtocol* gamer::Room<Player>::get_room_msg_protocol() {
    return &room_msg_proto_;
}

template<typename Player>
bool gamer::Room<Player>::Init(int room_id) {
	room_id_ = room_id;
    return true;
}

} // namespace gamer

#endif // CONNOR_GAME_SRC_ROOM_H_