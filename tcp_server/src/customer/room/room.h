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

#include "customer/room/card_constants.h"
#include "framework/util/chess_card_algorithm.h"
#include "msg/msg_manager.h"
#include "msg/protocol/room_msg_protocol.pb.h"
#include "msg/protocol/play_card_msg_protocol.pb.h"
#include "room/room_protocol.h"

namespace gamer {

template<typename Player>
class Room : public RoomProtocol<Player> {
  public:
    Room& operator=(const Room&) = delete;

    Room(const Room&) = delete;

    static Room* Create(int room_id);

    virtual void DissolveRoom(int room_id) override; // TODO :

    virtual void AddPlayer(Player* player) override; // not keep the ownership

    virtual void RomovePlayer(int player_id) override;

	virtual inline void set_room_id(int room_id) override;

	virtual inline int room_id() const override;

	virtual inline Player* player(int player_id) override;
    
    virtual inline std::vector<Player*>* players() override;

    virtual inline bool is_player_in_room(int player_id) const override;
    
    virtual inline int cur_players_num() const override;

    inline void set_room_msg_protocol(const std::string& serialized_data);

    inline protocol::RoomMsgProtocol* get_room_msg_protocol();

    Player* GetTheRightPlayer(int player_id);

    MsgCodes DealWithPlayCard(gamer::protocol::PlayCardMsgProtocol& proto);
	
  private:   
    Room();

    bool Init(int room_id);

    inline int new_card();

    protocol::RoomMsgProtocol room_msg_proto_;

	int room_id_;
    int new_card_index_;
    std::vector<Player*> players_;
    std::vector<Player*> players_sended_msg_hu_;
    std::vector<int> all_cards_;
};

template<typename Player>
gamer::Room<Player>::Room()
	:room_id_(0)
    ,new_card_index_(-1) {

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
void gamer::Room<Player>::AddPlayer(Player* player) {
    auto itr = std::find(players_.begin(), players_.end(), player);
    if (itr == players_.end()) {
        players_.push_back(player);
    }
}

template<typename Player>
void gamer::Room<Player>::RomovePlayer(int player_id) {
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
inline void Room<Player>::set_room_id(int room_id) {
	room_id_ = room_id;
}

template<typename Player>
inline int Room<Player>::room_id() const {
	return room_id_;
}

template<typename Player>
inline Player* Room<Player>::player(int player_id) {
    for (auto& player : players_) {
        if (player->player_id() == player_id) {
            return player;
        }
    }
	return nullptr;
}

template<typename Player>
std::vector<Player*>* gamer::Room<Player>::players() {
    return &players_;
}

template<typename Player>
bool gamer::Room<Player>::is_player_in_room(int player_id) const {
    for (auto& player : players_) {
        if (player->player_id() == player_id) {
            return true;
        }
    }
    return false;
}

template<typename Player>
int gamer::Room<Player>::cur_players_num() const {
    return (int)players_.size();
}

template<typename Player>
MsgCodes Room<Player>::DealWithPlayCard(gamer::protocol::PlayCardMsgProtocol& proto) {
    // check whether player in the room
    auto player_id = proto.player_id();
    auto player = this->player(player_id);
    if (nullptr == player) {
        // TODO : log
        // TODO : specify error code
        return MsgCodes::MSG_RESPONSE_CODE_FAILED1;
    }

    players_sended_msg_hu_.clear();

    int operation_id = proto.operation_id();
    switch (operation_id) {
    case PlayCardOperationIDs::DISCARD: {
        // check hand cards
        if ( !player->InvisibleHandCardsContains(proto.discard()) ) {
            // TODO : log
            // TODO : specify error code
            return MsgCodes::MSG_RESPONSE_CODE_FAILED1;
        }

        // update hand card and discard
        player->UpdateCardForDiscard(proto.discard());

        // send discard succeed msg
        auto bev = PlayerManager::instance()->GetOnlinePlayerBufferevent(player->player_id());
        if (nullptr != bev) {
            MsgManager::instance()->SendMsg((msg_header_t)MsgTypes::S2C_MSG_TYPE_ROOM,
                (msg_header_t)MsgIDs::MSG_ID_ROOM_PLAY_CARD,
                (msg_header_t)MsgCodes::MSG_RESPONSE_CODE_SUCCESS,
                proto,
                bev);
        } else {
            // TODO : log
        }

        // check whether is hu for other players
        auto playertmp = player;
        for (unsigned i = 0; i < players_.size() - 1; i++) {
            auto right_player = this->GetTheRightPlayer(playertmp->player_id());
            auto playerid = right_player->player_id();
            playertmp = right_player;
            if (playerid == player_id) {
                continue;
                // TODO : log
            }

            if (right_player->IsHu(proto.discard())) {
                auto bev = PlayerManager::instance()->GetOnlinePlayerBufferevent(playerid);
                if (nullptr != bev) {
                    proto.set_operation_id(PlayCardOperationIDs::MELD_CARD_HU);
                    MsgManager::instance()->SendMsg((msg_header_t)MsgTypes::S2C_MSG_TYPE_ROOM,
                        (msg_header_t)MsgIDs::MSG_ID_ROOM_PLAY_CARD,
                        (msg_header_t)MsgCodes::MSG_RESPONSE_CODE_SUCCESS,
                        proto,
                        bev);

                    players_sended_msg_hu_.push_back(right_player);
                } else {
                    // TODO : log
                }
            }
        }

        // check whether is peng for other players

        // check whether is chi for other players

        // send discard msg to other players if no players can hu, peng, chi
        if (players_sended_msg_hu_.size() <= 0) {
            playertmp = player;
            for (unsigned i = 0; i < players_.size() - 1; i++) {
                auto right_player = this->GetTheRightPlayer(playertmp->player_id());
                auto playerid = right_player->player_id();
                playertmp = right_player;
                if (0 == i) { // get a new card for the first right player
                    auto new_card = this->new_card();
                    // whether is zimo or ming gang or an gang or bu hua with new card
                    auto ret = right_player->GetAvailableOperationID(new_card);
                    proto.set_operation_id(ret);

                    proto.set_new_card(new_card);
                    right_player->UpdateInvisibleHandCard(new_card);
                } else {
                    proto.set_operation_id(PlayCardOperationIDs::DISCARD);
                    proto.set_new_card(0);
                }

                auto bev = PlayerManager::instance()->GetOnlinePlayerBufferevent(playerid);
                if (nullptr != bev) {
                    MsgManager::instance()->SendMsg((msg_header_t)MsgTypes::S2C_MSG_TYPE_ROOM,
                        (msg_header_t)MsgIDs::MSG_ID_ROOM_PLAY_CARD,
                        (msg_header_t)MsgCodes::MSG_RESPONSE_CODE_SUCCESS,
                        proto,
                        bev);
                } else {
                    // TODO : log
                }
            }
        }

        break;
    }
    default:
        // TODO : log
        // TODO : specify error code
        return MsgCodes::MSG_RESPONSE_CODE_FAILED1;
        //break;
    }

    return MsgCodes::MSG_RESPONSE_CODE_SUCCESS;
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
Player* Room<Player>::GetTheRightPlayer(int player_id) {
    for (unsigned i = 0; i < players_.size(); i++) {
        if (players_.at(i)->player_id() == player_id) {
            auto j = (players_.size() - 1) == i ? 0 : i + 1;
            return players_.at(j);
        }
    }
    return nullptr;
}

template<typename Player>
bool gamer::Room<Player>::Init(int room_id) {
	room_id_ = room_id;
    return true;
}

template<typename Player>
inline int Room<Player>::new_card() {
    new_card_index_ += 1;
    if (new_card_index_ < room_msg_proto_.remain_cards().size()) {
        return room_msg_proto_.remain_cards(new_card_index_);
    }
    return 0;
}

} // namespace gamer

#endif // CONNOR_GAME_SRC_ROOM_H_