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

#include "msg/protocol/create_room_msg_protocol.pb.h"
#include "msg/protocol/game_start_msg_protocol.pb.h"
#include "room/room_protocol.h"

namespace gamer {

template<typename Player>
class Room : public RoomProtocol<Player> {
  public:
    Room& operator=(const Room&) = delete;

    Room(const Room&) = delete;

    static Room* Create(int room_id, const protocol::CreateRoomMsgProtocol& proto); // TODO : use google::protobuf::massage

    virtual void DissolveRoom(int room_id) override;

    virtual void AddPlayer(int player_id, Player* player) override;

    virtual void RomovePlayer(int player_id) override;

    virtual inline std::unordered_map<int, Player*>* players() override;

    virtual inline bool is_player_in_room(int player_id) const override;
    
    virtual inline int cur_players_num() const override;

    inline protocol::GameStartMsgProtocol& get_game_start_msg_protocol();

    inline protocol::CreateRoomMsgProtocol* get_create_room_msg_protocol();

  private:    
    Room() = default;

    bool Init(int room_id, const protocol::CreateRoomMsgProtocol& proto);

    protocol::GameStartMsgProtocol room_msg_proto_;
    protocol::CreateRoomMsgProtocol create_room_msg_proto_;

    std::unordered_map<int, typename Player*> players_;

    std::vector<int> all_cards_;
};

template<typename Player>
gamer::Room<Player>* Room<Player>::Create(int room_id, 
                                          const protocol::CreateRoomMsgProtocol& proto) {
    auto room = new Room<Player>();
    if (nullptr != room) {
        if (!room->Init(room_id, proto)) {
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
protocol::CreateRoomMsgProtocol* gamer::Room<Player>::get_create_room_msg_protocol() {
    return &create_room_msg_proto_;
}

template<typename Player>
protocol::GameStartMsgProtocol& gamer::Room<Player>::get_game_start_msg_protocol() {
    return room_msg_proto_;
}

template<typename Player>
bool gamer::Room<Player>::Init(int room_id, const protocol::CreateRoomMsgProtocol& proto) {
    create_room_msg_proto_.set_room_owner_id(proto.room_owner_id());
    create_room_msg_proto_.set_room_id(room_id);
    create_room_msg_proto_.set_players_num(proto.players_num());
    create_room_msg_proto_.set_rounds_num(proto.rounds_num());
    // TODO : init more info
    return true;
}

} // namespace gamer

#endif // CONNOR_GAME_SRC_ROOM_H_