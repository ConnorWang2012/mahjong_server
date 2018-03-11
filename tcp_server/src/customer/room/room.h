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

#include <algorithm>
#include <unordered_map>
#include <vector>

#include "framework/base/macros.h"
#include "framework/util/chess_card_algorithm.h"

#include "customer/room/room_protocol.h"
#include "customer/room/card_constants.h"
#include "customer/msg/msg_manager.h"
#include "customer/msg/protocol/my_login_msg_protocol.pb.h"
#include "customer/msg/protocol/player_cards_msg_protocol.pb.h"
#include "customer/msg/protocol/create_room_msg_protocol.pb.h"
#include "customer/msg/protocol/room_msg_protocol.pb.h"
#include "customer/msg/protocol/play_card_msg_protocol.pb.h"
#include "customer/msg/protocol/game_end_msg_protocol.pb.h"

namespace gamer {

template<typename Player>
class Room : public RoomProtocol<Player> {
  public:
    typedef gamer::protocol::CreateRoomMsgProtocol CreateRoomMsgProtocol;
    typedef gamer::protocol::RoomMsgProtocol       RoomMsgProtocol;
    typedef gamer::protocol::PlayCardMsgProtocol   PlayCardMsgProtocol;
    typedef gamer::protocol::GameEndMsgProtocol    GameEndMsgProtocol;

    Room& operator=(const Room&) = delete;

    Room(const Room&) = delete;

    static Room* Create(id_t room_id);

    virtual void DissolveRoom(id_t room_id) override; // TODO :

    virtual void AddPlayer(Player* player) override; // not keep the ownership

    virtual void RomovePlayer(id_t player_id) override;

	virtual inline void set_room_id(id_t room_id) override;

	virtual inline id_t room_id() const override;

	virtual inline Player* player(id_t player_id) override;
    
    virtual inline std::vector<Player*>* players() override;

    virtual inline bool is_player_in_room(id_t player_id) const override;
    
    virtual inline size_t cur_players_num() const override;

	inline bool is_players_num_upper_limit() const;

    void InitCreateRoomMsgProtocol(const CreateRoomMsgProtocol& proto);

    void InitRoomMsgProtocol(const std::string& serialized_data);

	MsgCodes DealWithGameStart(RoomMsgProtocol& proto);

    MsgCodes DealWithPlayCard(PlayCardMsgProtocol& proto);

  private:   
    Room();

    bool Init(id_t room_id);

    void DealWithFirstGameStart();

    void DealWithNonFirstGameStart();

	MsgCodes DealWithOperationDiscard(PlayCardMsgProtocol& proto, Player* player);

    void DealWithOperationGiveUp(PlayCardMsgProtocol& proto, Player* player);

    void DealWithOperationGiveUpPengOrPengGang(PlayCardMsgProtocol& proto);

    void DealWithGameEnd(Player* player_win);

    Player* GetTheRightPlayer(id_t player_id);

    bool IsLeftPlayer(id_t src_player_id, id_t target_player_id);

    bool SendPlayCardMsg(PlayCardMsgProtocol& proto, id_t player_id) const;

    void RemovePlayerOfSendedMsgHu(id_t player_id);

    void RemovePlayerOfSendedMsgPeng(id_t player_id);

    Player* GetPlayerOfHigherPriorityForHu();

    inline int next_one_new_card();

    CreateRoomMsgProtocol create_room_msg_proto_;
    RoomMsgProtocol room_msg_proto_;

	id_t room_id_;
    Player* last_discard_player_;
    Player* player_sended_msg_chi_;
    std::vector<Player*> players_;
    std::vector<Player*> players_sended_msg_hu_;
    std::vector<Player*> players_sended_msg_peng_;
    std::vector<Player*> players_selected_hu_;
    std::vector<Player*> players_selected_giveup_;
};

template<typename Player>
gamer::Room<Player>::Room()
	: room_id_(0),
      last_discard_player_(nullptr),
      player_sended_msg_chi_(nullptr) {

}

template<typename Player>
gamer::Room<Player>* Room<Player>::Create(id_t room_id) {
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
void gamer::Room<Player>::DissolveRoom(id_t room_id) {

}

template<typename Player>
void gamer::Room<Player>::AddPlayer(Player* player) {
    auto itr = std::find(players_.begin(), players_.end(), player);
    if (itr == players_.end()) {
        players_.push_back(player);
    }
}

template<typename Player>
void gamer::Room<Player>::RomovePlayer(id_t player_id) {
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
inline void Room<Player>::set_room_id(id_t room_id) {
	room_id_ = room_id;
}

template<typename Player>
inline id_t Room<Player>::room_id() const {
	return room_id_;
}

template<typename Player>
inline Player* Room<Player>::player(id_t player_id) {
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
bool gamer::Room<Player>::is_player_in_room(id_t player_id) const {
    for (auto& player : players_) {
        if (player->player_id() == player_id) {
            return true;
        }
    }
    return false;
}

template<typename Player>
size_t gamer::Room<Player>::cur_players_num() const {
    return players_.size();
}

template<typename Player>
inline bool Room<Player>::is_players_num_upper_limit() const {
	return this->cur_players_num() >= create_room_msg_proto_.players_num();
}

template<typename Player>
void Room<Player>::InitCreateRoomMsgProtocol(const CreateRoomMsgProtocol& proto) {
    create_room_msg_proto_.CopyFrom(proto);
}

template<typename Player>
MsgCodes Room<Player>::DealWithGameStart(RoomMsgProtocol& proto) {
    if ( !create_room_msg_proto_.IsInitialized() ) {
        // TODO : log
        return MsgCodes::MSG_CODE_ROOM_NOT_EXIST;
    }

    // verify room owner id and room players num
    auto room_owner_id_client = proto.room_owner_id();
    auto room_owner_id_server = create_room_msg_proto_.room_owner_id();
    if (room_owner_id_server != room_owner_id_client) {
        // TODO : log
        return MsgCodes::MSG_CODE_ROOM_NOT_ROOM_OWNER;
    }

    if ( !this->is_players_num_upper_limit() ) {
        // TODO : log
        return MsgCodes::MSG_CODE_ROOM_PLAYER_NUM_LIMIT;
    }

    this->DealWithNonFirstGameStart();
    this->DealWithFirstGameStart();
    
    // prepare room msg proto for each player
    std::unordered_map<int, RoomMsgProtocol*> room_msg_protos;
    for (auto& p : players_) {
        auto room_proto = new RoomMsgProtocol(room_msg_proto_);
        room_msg_protos.insert(std::make_pair(p->player_id(), room_proto));
    }

    int buf[CardConstants::TOTAL_CARDS_NUM] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8,
        0, 1, 2, 3, 4, 5, 6, 7, 8,
        0, 1, 2, 3, 4, 5, 6, 7, 8,
        0, 1, 2, 3, 4, 5, 6, 7, 8,

        9, 10, 11, 12, 13, 14, 15, 16, 17,
        9, 10, 11, 12, 13, 14, 15, 16, 17,
        9, 10, 11, 12, 13, 14, 15, 16, 17,
        9, 10, 11, 12, 13, 14, 15, 16, 17,

        18, 19, 20, 21, 22, 23, 24, 25, 26,
        18, 19, 20, 21, 22, 23, 24, 25, 26,
        18, 19, 20, 21, 22, 23, 24, 25, 26,
        18, 19, 20, 21, 22, 23, 24, 25, 26,

        27, 28, 29, 30, 31, 32, 33,
        27, 28, 29, 30, 31, 32, 33,
        27, 28, 29, 30, 31, 32, 33,
        27, 28, 29, 30, 31, 32, 33, // 41 -> 28

        34, 1, 2, 3, 4, 5, 6, 7
    };
        //34, 35, 36, 37, 38, 39, 40, 41};
    auto vec = std::vector<int>(buf, buf + CardConstants::TOTAL_CARDS_NUM);
    //gamer::ChessCard::Shuffle(vec);

    // room remain cards
    auto remain_card_num = room_msg_proto_.remain_cards_num();
    room_msg_proto_.mutable_remain_cards()->Reserve(remain_card_num);
    for (unsigned i = 0; i < remain_card_num; i++) {
        room_msg_proto_.add_remain_cards(vec.at(i)); // some kind of ugly
    }

    // room player cards and player personal data
    auto card_index = remain_card_num;
    for (unsigned i = 0; i < players_.size(); i++) {
        auto player        = players_.at(i);
		auto room_proto    = room_msg_protos.at(player->player_id());
        auto card_num      = CardConstants::ONE_PLAYER_CARD_NUM;
        auto player_cards  = room_msg_proto_.mutable_player_cards(i);
        auto player_cards2 = room_proto->mutable_player_cards(i);

        player_cards->set_invisible_hand_cards_num(card_num);
        player_cards2->set_invisible_hand_cards_num(card_num);
        player_cards->mutable_invisible_hand_cards()->Reserve(CardConstants::ONE_PLAYER_CARD_NUM2);
        player_cards2->mutable_invisible_hand_cards()->Reserve(CardConstants::ONE_PLAYER_CARD_NUM2);
        for (auto j = 0; j < card_num; j++) {
            player_cards->add_invisible_hand_cards(vec.at(card_index));
            player_cards2->add_invisible_hand_cards(vec.at(card_index));
            // TODO : visible cards and waiting cards
            ++card_index;
        }

		// player personal data
		std::string serialized_data = "";
		DataManager::instance()->GetCachedPlayerPersonalData(player->player_id(), &serialized_data);
		if ("" != serialized_data) {			
			auto player_proto = room_proto->add_players();
			if ( !player_proto->ParseFromString(serialized_data) ) {
				// TODO : log
				printf("test");
			}
		} else {
			// TODO : log
		}
    }

    // send game start msg to all players
    auto banker_player_id = 0;
    for (int i = 0; i < (int)players_.size(); i++) {
        auto player = players_.at(i);
        auto player_id = player->player_id();
        auto proto = room_msg_protos.at(player_id);

        if (player_id == room_msg_proto_.banker_id()) {
            banker_player_id = player_id;
        }

        auto bev = PlayerManager::instance()->GetOnlinePlayerBufferevent(player_id);
        if (nullptr != bev) {
            MsgManager::instance()->SendMsg((msg_header_t)MsgTypes::S2C_MSG_TYPE_ROOM,
                (msg_header_t)MsgIDs::MSG_ID_ROOM_START_GAME,
                (msg_header_t)MsgCodes::MSG_CODE_SUCCESS,
                *proto,
                bev);
        } else {
            // TODO : log
            //return MsgCodes::MSG_RESPONSE_CODE_FAILED1;
        }
    }

    // set player hand cards for player obj(reference)
    for (unsigned i = 0; i < players_.size(); i++) {
        players_.at(i)->InitPlayerCards(room_msg_proto_.mutable_player_cards(i));
    }
    
    // send play card operation msg to the banker player
    if (0 != banker_player_id) {
        PlayCardMsgProtocol proto;
        proto.set_player_id(banker_player_id);
        proto.set_room_id(room_id_);
        proto.set_cur_round(room_msg_proto_.cur_round());
        proto.set_operation_id(PlayCardOperationIDs::OPERATION_UNKNOW);
        proto.set_next_operate_player_id(banker_player_id);

        auto room_proto = room_msg_protos.at(banker_player_id);
        for (int i = 0; i < room_proto->player_cards_size(); i++) {
            if (room_proto->player_cards(i).player_id() == banker_player_id) {
                auto new_card = this->next_one_new_card();
                players_.at(i)->UpdateInvisibleHandCard(new_card);
                proto.set_new_card(new_card);

                auto ret = players_.at(i)->GetAvailableOperationID(new_card, &proto);
                proto.set_my_available_operation_id(ret);                
                players_.at(i)->set_cur_available_operation_id(ret);
                
                this->SendPlayCardMsg(proto, banker_player_id);
                break;
            }
        }
    }

    // release allocated
    for (auto itr = room_msg_protos.begin(); itr != room_msg_protos.end(); itr++) {
        itr->second->mutable_player_cards()->DeleteSubrange(0, itr->second->player_cards_size());
        delete itr->second;
    }

    return MsgCodes::MSG_CODE_SUCCESS;
}

template<typename Player>
MsgCodes Room<Player>::DealWithPlayCard(PlayCardMsgProtocol& proto) {
	// check whether player in the room
	auto player_id = proto.player_id();
	auto player = this->player(player_id);
	if (nullptr == player) {
		// TODO : log
		return MsgCodes::MSG_CODE_ROOM_PLAYER_NOT_IN_ROOM;
	}

	int operation_id = proto.operation_id();
	switch (operation_id) {
	case PlayCardOperationIDs::OPERATION_DISCARD: {
		return this->DealWithOperationDiscard(proto, player);

		break;
	}
	case PlayCardOperationIDs::OPERATION_CHI: {
		if (2 != proto.operating_cards_size()) {
			// TODO : log
			return MsgCodes::MSG_CODE_OPERATION_CHI_OPERATING_CARDS_INVALID;
		}

		if (!player->IsChi(proto.discard())) {
			// TODO : log
			return MsgCodes::MSG_CODE_OPERATION_CHI_NOT_AVAILABLE;
		}

		// update hand card
		auto card_valid = player->UpdateCardForChi(proto.discard(), proto.operating_cards(0),
			proto.operating_cards(1));
		if (!card_valid) {
			// TODO : log
			return MsgCodes::MSG_CODE_OPERATION_CHI_OPERATING_CARDS_INVALID;
		}

		// send chi succeed msg
		proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
		proto.set_next_operate_player_id(player_id);
		proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
		player->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
		for (auto& p : players_) {
			this->SendPlayCardMsg(proto, p->player_id());
		}

		break;
	}
	case PlayCardOperationIDs::OPERATION_PENG: {
		if (!player->IsPeng(proto.discard())) {
			// TODO : log
			return MsgCodes::MSG_CODE_OPERATION_PENG_NOT_AVAILABLE;
		}

		// update hand card
		player->UpdateCardForPeng(proto.discard());

		// send peng succeed msg
		proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
		proto.set_next_operate_player_id(player_id);
		proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
		player->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
		for (auto& p : players_) {
			this->SendPlayCardMsg(proto, p->player_id());
		}

		// remove player of sended msg peng
		this->RemovePlayerOfSendedMsgPeng(player_id);

		break;
	}
	case PlayCardOperationIDs::OPERATION_PENG_GANG: {
		if (!player->IsPengAndGang(proto.discard())) {
			// TODO : log
			return MsgCodes::MSG_CODE_OPERATION_PENG_GANG_NOT_AVAILABLE;
		}

		// update hand card
		player->UpdateCardForPengAndGang(proto.discard());

		// send new card msg and peng gang msg
		proto.set_next_operate_player_id(player_id);
		for (auto& p : players_) {
			if (p->player_id() == player_id) {
				auto new_card = this->next_one_new_card();
				p->UpdateInvisibleHandCard(new_card);
				auto ret = p->GetAvailableOperationID(new_card, &proto);
				p->set_cur_available_operation_id(ret);
				proto.set_my_available_operation_id(ret);
				proto.set_new_card(new_card);
				proto.set_has_next_operate_player_new_card(false);
			} else {
				p->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
				proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
				proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
				proto.set_has_next_operate_player_new_card(true);
			}

			this->SendPlayCardMsg(proto, p->player_id());
		}

		// remove player of sended msg peng gang
		this->RemovePlayerOfSendedMsgPeng(player_id);

		break;
	}
	case PlayCardOperationIDs::OPERATION_MING_GANG: {
		if (!player->IsMingGang(proto.discard())) {
			// TODO : log
			return MsgCodes::MSG_CODE_OPERATION_MING_GANG_NOT_AVAILABLE;
		}

		// update hand card
		player->UpdateCardForMingGang(proto.discard());

		// send ming gang msg
		proto.set_next_operate_player_id(player_id);
		for (auto& p : players_) {
			if (p->player_id() == player_id) {
				auto new_card = this->next_one_new_card();
				p->UpdateInvisibleHandCard(new_card);
				auto ret = p->GetAvailableOperationID(new_card, &proto);
				p->set_cur_available_operation_id(ret);
				proto.set_my_available_operation_id(ret);
				proto.set_new_card(new_card);
				proto.set_has_next_operate_player_new_card(false);
			} else {
				p->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
				proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
				proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
				proto.set_has_next_operate_player_new_card(true);
			}

			this->SendPlayCardMsg(proto, p->player_id());
		}

		break;
	}
	case PlayCardOperationIDs::OPERATION_AN_GANG: {
		if (!player->IsAnGang(proto.discard())) {
			// TODO : log
			return MsgCodes::MSG_CODE_OPERATION_AN_GANG_NOT_AVAILABLE;
		}

		// update hand card
		player->UpdateCardForAnGang(proto.discard());

		// send an gang succeed msg
		proto.set_next_operate_player_id(player_id);
		for (auto& p : players_) {
			if (p->player_id() == player_id) {
				auto new_card = this->next_one_new_card();
				p->UpdateInvisibleHandCard(new_card);
				auto ret = p->GetAvailableOperationID(new_card, &proto);
				p->set_cur_available_operation_id(ret);
				proto.set_my_available_operation_id(ret);
				proto.set_new_card(new_card);
				proto.set_has_next_operate_player_new_card(false);
			} else {
				p->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
				proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
				proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
				proto.set_has_next_operate_player_new_card(true);
			}

			this->SendPlayCardMsg(proto, p->player_id());
		}

		break;
	}
	case PlayCardOperationIDs::OPERATION_BU_HUA: {
		// check and update hand cards
		int cards_of_hua_removed[CardConstants::HUA_CARD_NUM_MAX] = { 0 };
		int num_cards_of_hua_removed = 0;
		auto ok = player->UpdateCardForBuhua(cards_of_hua_removed, num_cards_of_hua_removed);
		if (!ok) {
			// TODO : log
			return MsgCodes::MSG_CODE_OPERATION_BU_HUA_NOT_AVAILABLE;
		}

		// send bu hua succeed msg
		PlayCardMsgProtocol proto_other; // for sending to other player
		proto_other.set_player_id(player_id);
		proto_other.set_room_id(room_id_);
		proto_other.set_cur_round(room_msg_proto_.cur_round());
		proto_other.set_operation_id(PlayCardOperationIDs::OPERATION_BU_HUA);
		proto_other.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
		proto_other.set_new_card(CardConstants::INVALID_CARD_VALUE);
		proto_other.set_has_next_operate_player_new_card(true);

		for (int i = 0; i < num_cards_of_hua_removed; i++) {
			proto_other.add_operating_cards(cards_of_hua_removed[i]);
		}

		for (auto& p : players_) {
			auto playerid = p->player_id();
			if (playerid == player_id) { // get new card for the player of bu hua
				PlayCardMsgProtocol proto_self;

				proto_self.set_player_id(player_id);
				proto_self.set_room_id(room_id_);
				proto_self.set_cur_round(room_msg_proto_.cur_round());
				proto_self.set_operation_id(PlayCardOperationIDs::OPERATION_BU_HUA);
				proto_self.set_next_operate_player_id(player_id);
				proto_self.set_has_next_operate_player_new_card(false);

				if (num_cards_of_hua_removed > 1) {
					int new_cards[CardConstants::HUA_CARD_NUM_MAX] = { 0 };

					for (int i = 0; i < num_cards_of_hua_removed; i++) {
						new_cards[i] = this->next_one_new_card();
						p->UpdateInvisibleHandCard(new_cards[i]);
						proto_self.add_operating_cards(new_cards[i]);
					}

					auto priority_operation = (int)PlayCardOperationIDs::OPERATION_UNKNOW;

					for (int i = 0; i < num_cards_of_hua_removed; i++) {
						priority_operation = p->GetAvailableOperationID(new_cards[i], &proto_self);
						if (priority_operation == PlayCardOperationIDs::OPERATION_BU_HUA ||
							priority_operation == PlayCardOperationIDs::OPERATION_TING ||
							priority_operation == PlayCardOperationIDs::OPERATION_ZI_MO) {
							break;
						}
					}

					p->set_cur_available_operation_id(priority_operation);
					proto_self.set_my_available_operation_id(priority_operation);
				} else {
					auto new_card = this->next_one_new_card();
					p->UpdateInvisibleHandCard(new_card);
					proto_self.set_new_card(new_card);
					auto ret = p->GetAvailableOperationID(new_card, &proto_self);
					p->set_cur_available_operation_id(ret);
					proto_self.set_my_available_operation_id(ret);
				}

				this->SendPlayCardMsg(proto_self, playerid);
			}
			else {
				p->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);

				this->SendPlayCardMsg(proto_other, playerid);
			}
		}

		break;
	}
	case PlayCardOperationIDs::OPERATION_TING: {
		if (!player->IsTing()) {
			// TODO : log
			return MsgCodes::MSG_CODE_OPERATION_TING_NOT_AVAILABLE;
		}

		// send ting msg
		proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
		proto.set_next_operate_player_id(CardConstants::INVALID_PLAYER_ID);
		proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
		proto.clear_ting_cards();
		player->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
		player->set_has_selected_operation_ting(true);
		for (auto& p : players_) {
			this->SendPlayCardMsg(proto, p->player_id());
		}

		// deal with discard
		proto.set_operation_id(PlayCardOperationIDs::OPERATION_DISCARD);
		this->DealWithOperationDiscard(proto, player);

		break;
	}
	case PlayCardOperationIDs::OPERATION_HU: {
		if (1 == players_sended_msg_hu_.size()) {
			if (!player->IsHu(proto.discard())) {
				// TODO : log
				return MsgCodes::MSG_CODE_OPERATION_HU_NOT_AVAILABLE;
			}

			// TODO : send discard msg to players those can't hu and is not last discard player

			// send hu msg to all players
			proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
			proto.set_next_operate_player_id(player_id);
			for (auto& p : players_) {
				// prepare invisible hand cards
				if (p->player_id() == proto.player_id()) {
					p->CopyInvisibleHandCardsTo(*proto.mutable_invisible_hand_cards());
					break;
				}
			}

			for (auto& p : players_) {
				this->SendPlayCardMsg(proto, p->player_id());
			}

			// send game end msg to all players
			this->DealWithGameEnd(player);

			players_sended_msg_hu_.clear();
		}
		else if (2 == players_sended_msg_hu_.size()) {
			// TODO
			if (!player->IsHu(proto.discard())) {
				// TODO : log
				return MsgCodes::MSG_CODE_OPERATION_HU_NOT_AVAILABLE;
			}
			this->RemovePlayerOfSendedMsgHu(player_id);
			players_selected_hu_.push_back(player);
		}
		else if (3 == players_sended_msg_hu_.size()) {
			// TODO
			if (!player->IsHu(proto.discard())) {
				// TODO : log
				return MsgCodes::MSG_CODE_OPERATION_HU_NOT_AVAILABLE;
			}
			this->RemovePlayerOfSendedMsgHu(player_id);
			players_selected_hu_.push_back(player);
		}

		break;
	}
	case PlayCardOperationIDs::OPERATION_ZI_MO: {
		if (!player->IsZimo()) {
			// TODO : log
			return MsgCodes::MSG_CODE_OPERATION_ZIMO_NOT_AVAILABLE;
		}

		// send zi mo succeed msg        
		proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
		proto.set_next_operate_player_id(player_id);
		for (auto& p : players_) {
			this->SendPlayCardMsg(proto, p->player_id());
		}

		// send game end msg to all players
		this->DealWithGameEnd(player);

		break;
	}
	case PlayCardOperationIDs::OPERATION_GIVE_UP: {
		this->DealWithOperationGiveUp(proto, player);
		break;
	}
	default:
		// TODO : log
		return MsgCodes::MSG_CODE_OPERATION_UNKNOW;
	}

	return MsgCodes::MSG_CODE_SUCCESS;
}

template<typename Player>
void Room<Player>::DealWithFirstGameStart() {
    // room common data
    if ( !room_msg_proto_.IsInitialized() ) {
        auto room_owner_id = create_room_msg_proto_.room_owner_id();
        auto players_num = create_room_msg_proto_.players_num();
        room_msg_proto_.set_room_id(room_id_);
        room_msg_proto_.set_room_owner_id(room_owner_id);
        room_msg_proto_.set_players_num(players_num);
        room_msg_proto_.set_cur_round(1);
        room_msg_proto_.set_total_round(create_room_msg_proto_.rounds_num());
        room_msg_proto_.set_remain_cards_num(CardConstants::TOTAL_CARDS_NUM -
            players_num * CardConstants::ONE_PLAYER_CARD_NUM);
        room_msg_proto_.set_operating_player_id(room_owner_id);
        room_msg_proto_.set_banker_id(room_owner_id);
        room_msg_proto_.set_banker_is_same_time(0);

        for (auto& player : players_) {
            auto player_cards = room_msg_proto_.add_player_cards();
            player_cards->set_player_id(player->player_id());
        }
    }
}

template<typename Player>
void Room<Player>::DealWithNonFirstGameStart() {
    if (room_msg_proto_.IsInitialized()) {
        if (room_msg_proto_.cur_round() < room_msg_proto_.total_round()) {
            room_msg_proto_.set_cur_round(room_msg_proto_.cur_round() + 1);
        }
        
        for (auto i = 0; i < room_msg_proto_.player_cards_size(); i++) {
            auto player_card = room_msg_proto_.mutable_player_cards(i);
            player_card->clear_invisible_hand_cards();
            player_card->clear_flower_cards();
            player_card->clear_season_cards();
            player_card->clear_peng_cards();
            player_card->clear_chi_cards();
            player_card->clear_ming_gang_cards();
            player_card->clear_an_gang_cards();
            player_card->clear_discards();
            player_card->clear_ting_cards();
        }
        
        room_msg_proto_.clear_remain_cards();
        //room_msg_proto_.clear_player_cards();
    }
}

template<typename Player>
MsgCodes Room<Player>::DealWithOperationDiscard(PlayCardMsgProtocol& proto,
                                                Player* player) {
    // check hand cards
    if ( !player->InvisibleHandCardsContains(proto.discard()) ) {
        // TODO : log
        return MsgCodes::MSG_CODE_OPERATION_DISCARD_INVALID;
    }

    last_discard_player_ = player;

    // update hand card and discard
    player->UpdateCardForDiscard(proto.discard());

    // check whether is hu for other players
    auto player_id = player->player_id();
    auto playertmp = player;
    for (unsigned i = 0; i < players_.size(); i++) {
        auto right_player = this->GetTheRightPlayer(playertmp->player_id());
        auto playerid = right_player->player_id();
        playertmp = right_player;
        if (playerid == player_id) {
            continue;
        }

        if (right_player->IsHu(proto.discard())) {
            right_player->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_HU);
            proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_HU);
            proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
            proto.set_next_operate_player_id(playerid);

            if (this->SendPlayCardMsg(proto, playerid)) {
                players_sended_msg_hu_.push_back(right_player);
            }
        }
    }

    // check whether is peng for other players
    if (0 == players_sended_msg_hu_.size()) {
        proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
        playertmp = player;
        for (unsigned i = 0; i < players_.size() - 1; i++) {
            auto right_player = this->GetTheRightPlayer(playertmp->player_id());
            auto playerid = right_player->player_id();
            playertmp = right_player;
            if (playerid == player_id) {
                continue;
            }

            auto count = right_player->CountInvisibleHandCards(proto.discard());
            if (2 == count) { // peng
                right_player->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_PENG);
                proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_PENG);
                // if the player is first right player, check whether is chi available
                if (0 == i) {
                    int cards[9] = { 0 };
                    int len = 0;
                    if (right_player->IsChi(proto.discard(), cards, len)) {
                        for (auto j = 0; j < len; j++) {
                            proto.add_operating_cards(cards[j]);
                        }
                        right_player->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_CHI_OR_PENG);
                        proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_CHI_OR_PENG);
                    }
                }
            } else if (3 == count) { // peng gang
                right_player->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_PENG_GANG);
                proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_PENG_GANG);
                // if the player is first right player, check whether is chi available
                if (0 == i) {
                    int cards[9] = { 0 };
                    int len = 0;
                    if (right_player->IsChi(proto.discard(), cards, len)) {
                        for (auto j = 0; j < len; j++) {
                            proto.add_operating_cards(cards[j]);
                        }
                        right_player->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_CHI_OR_PENG_OR_GANG);
                        proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_CHI_OR_PENG_OR_GANG);
                    }
                }
            } 

            if (count >= 2) {                
                proto.set_next_operate_player_id(playerid);
                if (this->SendPlayCardMsg(proto, playerid)) {
                    players_sended_msg_peng_.push_back(right_player);
                }
                break;
            }
        }
    }

    // check whether is chi for first right players
    if (0 == players_sended_msg_hu_.size() && 0 == players_sended_msg_peng_.size()) {
        auto right_player = this->GetTheRightPlayer(player->player_id());
        auto playerid = right_player->player_id();
        int cards[9] = { 0 };
        int len = 0;
        if (right_player->IsChi(proto.discard(), cards, len)) {
            // send chi msg to first right player
            right_player->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_CHI);
            proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_CHI);
            proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
            proto.set_next_operate_player_id(playerid);
            for (auto i = 0; i < len; i++) {
                proto.add_operating_cards(cards[i]);
            }

            this->SendPlayCardMsg(proto, right_player->player_id());

            // send discard msg to other player
            proto.clear_operating_cards();
            for (unsigned i = 0; i < players_.size() - 1; i++) {
                auto p = this->GetTheRightPlayer(right_player->player_id());
                auto id = p->player_id();
                if (id != playerid && id != player_id) {
                    p->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
                    proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
                    proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
                    this->SendPlayCardMsg(proto, id);
                }
            }

            return MsgCodes::MSG_CODE_SUCCESS;
        }
    }

    // send discard msg to other players if no players can hu, peng, chi
    if (0 == players_sended_msg_hu_.size() && 0 == players_sended_msg_peng_.size()) {
        auto next_operation_player_id = 0;
        playertmp = player;
        for (unsigned i = 0; i < players_.size(); i++) {
            auto right_player = this->GetTheRightPlayer(playertmp->player_id());
            auto playerid = right_player->player_id();
            playertmp = right_player;
            if (0 == i) { // get a new card for the first right player
                auto new_card = this->next_one_new_card();
                right_player->UpdateInvisibleHandCard(new_card);
                // whether is zi mo or ming gang or an gang or bu hua with new card
                auto ret = right_player->GetAvailableOperationID(new_card, &proto);
                right_player->set_cur_available_operation_id(ret);
                proto.set_my_available_operation_id(ret);
                proto.set_new_card(new_card);
                proto.set_next_operate_player_id(playerid);
                proto.set_has_next_operate_player_new_card(false);
                next_operation_player_id = playerid;
            } else {
                right_player->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
                proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
                proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
                proto.set_next_operate_player_id(next_operation_player_id);
                proto.set_has_next_operate_player_new_card(true);
            }

            this->SendPlayCardMsg(proto, playerid);
        }
    }

	return MsgCodes::MSG_CODE_SUCCESS;
}

template<typename Player>
void Room<Player>::DealWithOperationGiveUp(PlayCardMsgProtocol& proto,
                                           Player* player) {
    int available_operation_id = player->cur_available_operation_id();
    switch (available_operation_id)
    {
    case PlayCardOperationIDs::OPERATION_CHI: {
        // send a new card to player
        auto new_card = this->next_one_new_card();
        player->UpdateInvisibleHandCard(new_card);
        auto ret = player->GetAvailableOperationID(new_card, &proto);
        player->set_cur_available_operation_id(ret);
        proto.set_my_available_operation_id(ret);
        proto.set_new_card(new_card);
        proto.set_next_operate_player_id(player->player_id());
        proto.set_has_next_operate_player_new_card(false);

        this->SendPlayCardMsg(proto, player->player_id());

        // send new card msg to other player
        proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
        proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
        proto.set_has_next_operate_player_new_card(true);
        for (auto& p : players_) {
            if (p->player_id() != player->player_id()) {
                this->SendPlayCardMsg(proto, p->player_id());
            }
        }

        break;
    }
    case PlayCardOperationIDs::OPERATION_PENG: {
        this->DealWithOperationGiveUpPengOrPengGang(proto);
        break;
    }
    case PlayCardOperationIDs::OPERATION_CHI_OR_PENG: {
        this->DealWithOperationGiveUpPengOrPengGang(proto);
        break;
    }
    case PlayCardOperationIDs::OPERATION_CHI_OR_PENG_OR_GANG: {
        this->DealWithOperationGiveUpPengOrPengGang(proto);
        break;
    }
    case PlayCardOperationIDs::OPERATION_PENG_GANG: {
        this->DealWithOperationGiveUpPengOrPengGang(proto);
        break;
    }
    case PlayCardOperationIDs::OPERATION_MING_GANG: {
        // Do nothing ?
        break;
    }
    case PlayCardOperationIDs::OPERATION_AN_GANG: {
        // Do nothing ?
        break;
    }
    case PlayCardOperationIDs::OPERATION_HU: {
        // check whether is peng or chi for other player
        this->RemovePlayerOfSendedMsgHu(player->player_id());
        players_selected_giveup_.push_back(player);

        if (0 != players_sended_msg_hu_.size())
            return;

        if (0 != players_selected_hu_.size()) {
            // send hu msg
            auto player_hu = this->GetPlayerOfHigherPriorityForHu();
            if (nullptr != player_hu) {
                // TODO
            }
        } else {
            // check whether is peng
            auto player_peng_id = 0;
            for (auto& p : players_) {
                if (p->player_id() != player->player_id() &&
                    p->player_id() != last_discard_player_->player_id()) {
                    auto count = p->CountInvisibleHandCards(proto.discard());
                    if (2 == count) {
                        auto operation_id = PlayCardOperationIDs::OPERATION_PENG;
                        p->set_cur_available_operation_id(operation_id);
                        proto.set_my_available_operation_id(operation_id);
                        player_peng_id = p->player_id();
                        break;
                    } else if (3 == count) {
                        auto operation_id = PlayCardOperationIDs::OPERATION_PENG_GANG;
                        p->set_cur_available_operation_id(operation_id);
                        proto.set_my_available_operation_id(operation_id);
                        player_peng_id = p->player_id();
                        break;
                    }
                }
            }

            // send peng msg or check whether is chi
            if (0 != player_peng_id) {
                this->SendPlayCardMsg(proto, player_peng_id);
            }
            else {
                // check whether is chi
                auto right_player = this->GetTheRightPlayer(last_discard_player_->player_id());
                if (right_player->player_id() != player->player_id()) {
                    int cards[9] = { 0 };
                    int len = 0;
                    if (right_player->IsChi(proto.discard(), cards, len)) {
                        auto operation_id = PlayCardOperationIDs::OPERATION_CHI;
                        right_player->set_cur_available_operation_id(operation_id);
                        proto.set_my_available_operation_id(operation_id);
                        proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
                        proto.set_next_operate_player_id(right_player->player_id());
                        for (auto i = 0; i < len; i++) {
                            proto.add_operating_cards(cards[i]);
                        }
                        this->SendPlayCardMsg(proto, right_player->player_id());
                    }
                } else { // means right_player is the player of give up hu
                       // send new card msg
                    auto new_card = this->next_one_new_card();
                    right_player->UpdateInvisibleHandCard(new_card);
                    auto ret = right_player->GetAvailableOperationID(new_card, &proto);
                    right_player->set_cur_available_operation_id(ret);
                    proto.set_my_available_operation_id(ret);
                    proto.set_new_card(new_card);
                    proto.set_next_operate_player_id(right_player->player_id());
                    proto.set_has_next_operate_player_new_card(false);

                    this->SendPlayCardMsg(proto, right_player->player_id());
                }
            }
        }
 
        break;
    }
    case PlayCardOperationIDs::OPERATION_ZI_MO: {
        // Do nothing ?
        break;
    }
    default:
        break;
    }
}

template<typename Player>
void Room<Player>::DealWithOperationGiveUpPengOrPengGang(PlayCardMsgProtocol& 
    proto) {
    // check whether is chi for the right player of last discard player
    if (nullptr == last_discard_player_) {
        // TODO : log
        return;
    }

    auto right_player = this->GetTheRightPlayer(last_discard_player_->player_id());
    auto right_player_id = right_player->player_id();
    auto send_new_card_msg = [&]() {
        // send new card msg to the first right player of last discard player
        auto new_card = this->next_one_new_card();
        right_player->UpdateInvisibleHandCard(new_card);
        auto ret = right_player->GetAvailableOperationID(new_card, &proto);
        right_player->set_cur_available_operation_id(ret);
        proto.set_my_available_operation_id(ret);
        proto.set_new_card(new_card);
        proto.set_next_operate_player_id(right_player_id);
        proto.set_has_next_operate_player_new_card(false);
        this->SendPlayCardMsg(proto, right_player_id);

        // send new card msg to other player
        proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
        proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
        proto.set_has_next_operate_player_new_card(true);
        for (auto& p : players_) {
            if (p->player_id() != right_player_id) {
                this->SendPlayCardMsg(proto, p->player_id());
            }
        }
    };

    if (right_player_id == proto.player_id()) {
        // the player of give peng or pang gang is first right player of last discard player, should send new card msg 
        // send new card msg to all players
        send_new_card_msg();
    } else {
        // the player of give peng or pang gang is NOT first right player of last discard player
        // check whether is chi for first right player of last discard player
        int cards[9] = { 0 };
        int len = 0;
        if (right_player->IsChi(proto.discard(), cards, len)) {
            // send chi is available msg
            right_player->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_CHI);
            proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_CHI);
            proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
            proto.set_next_operate_player_id(right_player_id);
            for (auto i = 0; i < len; i++) {
                proto.add_operating_cards(cards[i]);
            }

            this->SendPlayCardMsg(proto, right_player_id);
        } else {
            // send new card msg to all players
            send_new_card_msg();
        }
    }

    this->RemovePlayerOfSendedMsgPeng(proto.player_id());
}

template<typename Player>
void Room<Player>::DealWithGameEnd(Player* player_win) {
    GameEndMsgProtocol proto;
    proto.set_room_id(room_id_);
    proto.set_room_owner_id(room_msg_proto_.room_owner_id());
    proto.set_winner_id(player_win->player_id());
    proto.set_players_num(room_msg_proto_.players_num());
    proto.set_cur_round(room_msg_proto_.cur_round());
    proto.set_total_round(room_msg_proto_.total_round());
    proto.set_banker_id(room_msg_proto_.banker_id());
    
    protocol::PlayerMsgProtocol player_proto;

    for (auto& player : players_) {
        std::string player_data = "";
        DataManager::instance()->GetCachedPlayerPersonalData(player->player_id(), &player_data);
        
        if ( !player_data.empty() ) {
            if ( !player_proto.ParseFromString(player_data) ) {
                // TODO:log
                continue;
            }

            auto game_end_data = proto.add_game_end_data();
            game_end_data->set_player_id(player->player_id());
            game_end_data->set_nick_name(player_proto.nick_name());
			game_end_data->set_num_ming_gang(player->num_ming_gang());
			game_end_data->set_num_an_gang(player->num_an_gang());

            auto gold_old = player_proto.score_gold();
            int gold = create_room_msg_proto_.score_gold();

			// score
            if (player->player_id() == player_win->player_id()) {                
				player_proto.set_score_gold(gold_old + gold);
                game_end_data->set_diff_score_gold(gold);
				player->set_num_win(player->num_win() + 1);
            } else {
                int gold_new = gold_old - gold;
                if (gold_new < 0) {
                    gold_new = 0;
                }
				player_proto.set_score_gold(gold_new);

                game_end_data->set_diff_score_gold(-gold);
            }

			// win rate
			float win_rate = 0;
			if (room_msg_proto_.total_round() > 0) {
				win_rate = float(player->num_win()) / float(room_msg_proto_.total_round());
			}
			game_end_data->set_rate_winning(win_rate);

            if (player_proto.SerializeToString(&player_data)) {
                DataManager::instance()->CachePlayerPersonalData(player->player_id(), player_data);
            }
        }
    }

    for (auto& player : players_) {
        auto bev = PlayerManager::instance()->GetOnlinePlayerBufferevent(player->player_id());
        if (nullptr != bev) {
            MsgManager::instance()->SendMsg((msg_header_t)MsgTypes::S2C_MSG_TYPE_ROOM,
                (msg_header_t)MsgIDs::MSG_ID_ROOM_GAME_END,
                (msg_header_t)MsgCodes::MSG_CODE_SUCCESS,
                proto,
                bev);
        } else {
            // TODO : log
        }
    }
}

template<typename Player>
void Room<Player>::InitRoomMsgProtocol(const std::string& serialized_data) {
    room_msg_proto_.ParseFromString(serialized_data);
}

template<typename Player>
Player* Room<Player>::GetTheRightPlayer(id_t player_id) {
    for (unsigned i = 0; i < players_.size(); i++) {
        if (players_.at(i)->player_id() == player_id) {
            auto j = (players_.size() - 1) == i ? 0 : i + 1;
            return players_.at(j);
        }
    }
    return nullptr;
}

template<typename Player>
inline bool Room<Player>::IsLeftPlayer(id_t src_player_id, id_t target_player_id) {
    for (unsigned i = 0; i < players_.size(); i++) {
        if (players_.at(i)->player_id() == src_player_id) {
            if (0 == i) {
                return players_.at(players_.size() - 1)->player_id() == target_player_id;
            } else {
                return players_.at(i - 1)->player_id() == target_player_id;
            }
        }
    }
    return false;
}

template<typename Player>
bool Room<Player>::SendPlayCardMsg(PlayCardMsgProtocol& proto, 
								   id_t player_id) const {
    auto bev = PlayerManager::instance()->GetOnlinePlayerBufferevent(player_id);
    if (nullptr != bev) {
        return MsgManager::instance()->SendMsg((msg_header_t)MsgTypes::S2C_MSG_TYPE_ROOM,
                                               (msg_header_t)MsgIDs::MSG_ID_ROOM_PLAY_CARD,
                                               (msg_header_t)MsgCodes::MSG_CODE_SUCCESS,
                                               proto,
                                               bev);
    } else {
        // TODO : log
        return false;
    }
    return false;
}

template<typename Player>
void Room<Player>::RemovePlayerOfSendedMsgHu(id_t player_id) {
    for (auto itr = players_sended_msg_hu_.begin(); itr != players_sended_msg_hu_.end(); itr++) {
        if ((*itr)->player_id() == player_id) {
            players_sended_msg_hu_.erase(itr);
            break;
        }
    }
}

template<typename Player>
void gamer::Room<Player>::RemovePlayerOfSendedMsgPeng(id_t player_id) {
    for (auto itr = players_sended_msg_peng_.begin(); itr != players_sended_msg_peng_.end(); 
        itr++) {
        if ((*itr)->player_id() == player_id) {
            players_sended_msg_peng_.erase(itr);
            break;
        }
    }
}

template<typename Player>
Player* Room<Player>::GetPlayerOfHigherPriorityForHu() {
    if (players_selected_hu_.size() > 0 && nullptr != last_discard_player_) {
        auto right_player = last_discard_player_;
        for (unsigned i = 0; i < players_.size(); i++) {
            right_player = this->GetTheRightPlayer(right_player->player_id());
            for (auto& player : players_selected_hu_) {
                if (right_player->player_id() == player->player_id()) {
                    return player;
                }
            }
        }
    }
    return nullptr;
}

template<typename Player>
bool gamer::Room<Player>::Init(id_t room_id) {
	room_id_ = room_id;
    return true;
}

template<typename Player>
inline int Room<Player>::next_one_new_card() {
    int card = CardConstants::INVALID_CARD_VALUE;
    auto size = room_msg_proto_.remain_cards_size();
    if (size > 0) {
        card = room_msg_proto_.remain_cards(size - 1);
        room_msg_proto_.mutable_remain_cards()->RemoveLast();
    }
    return card;
}

} // namespace gamer

#endif // CONNOR_GAME_SRC_ROOM_H_