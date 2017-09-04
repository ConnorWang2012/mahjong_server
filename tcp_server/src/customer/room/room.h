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

    inline gamer::protocol::RoomMsgProtocol* get_room_msg_protocol();

    MsgCodes DealWithPlayCard(gamer::protocol::PlayCardMsgProtocol& proto);

  private:   
    Room();

    bool Init(int room_id);

    void DealWithOperationDiscard(gamer::protocol::PlayCardMsgProtocol& proto, Player* player);

    void DealWithOperationGiveUp(gamer::protocol::PlayCardMsgProtocol& proto, Player* player);

    void DealWithOperationGiveUpPengOrPengGang(gamer::protocol::PlayCardMsgProtocol& proto);

    Player* GetTheRightPlayer(int player_id);

    bool IsLeftPlayer(int src_player_id, int target_player_id);

    bool SendPlayCardMsg(gamer::protocol::PlayCardMsgProtocol& proto, int player_id) const;

    void RemovePlayerOfSendedMsgHu(int player_id);

    void RemovePlayerOfSendedMsgPeng(int player_id);

    inline int next_one_new_card();

    gamer::protocol::RoomMsgProtocol room_msg_proto_;

	int room_id_;
    Player* last_discard_player_;
    Player* player_sended_msg_chi_;
    std::vector<Player*> players_;
    std::vector<Player*> players_sended_msg_hu_;
    std::vector<Player*> players_sended_msg_peng_;
};

template<typename Player>
gamer::Room<Player>::Room()
	:room_id_(0)
    ,last_discard_player_(nullptr)
    ,player_sended_msg_chi_(nullptr) {

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

    int operation_id = proto.operation_id();
    switch (operation_id) {
    case PlayCardOperationIDs::OPERATION_DISCARD: {
        // check hand cards
        if ( !player->InvisibleHandCardsContains(proto.discard()) ) {
            // TODO : log
            // TODO : specify error code
            return MsgCodes::MSG_RESPONSE_CODE_FAILED1;
        }

        this->DealWithOperationDiscard(proto, player);

        break;
    }
    case PlayCardOperationIDs::OPERATION_CHI: {
        if (2 != proto.operating_cards_size()) {
            // TODO : log
            // TODO : specify error code
            return MsgCodes::MSG_RESPONSE_CODE_FAILED1;
        }

        if ( !player->IsChi(proto.discard()) ) {
            // TODO : log
            // TODO : specify error code
            return MsgCodes::MSG_RESPONSE_CODE_FAILED1;
        }

        // update hand card
        auto card_valid = player->UpdateCardForChi(proto.discard(), proto.operating_cards(0), 
            proto.operating_cards(1));
        if ( !card_valid ) {
            // TODO : log
            // TODO : specify error code
            return MsgCodes::MSG_RESPONSE_CODE_FAILED1;
        }

        // send chi succeed msg
        proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
        proto.set_next_operate_player_id(player_id);
        for (auto& p : players_) {
            this->SendPlayCardMsg(proto, p->player_id());
        }

        break;
    }
    case PlayCardOperationIDs::OPERATION_PENG: {
        if ( !player->IsPeng(proto.discard()) ) {
            // TODO : log
            // TODO : specify error code
            return MsgCodes::MSG_RESPONSE_CODE_FAILED1;
        }

        // update hand card
        player->UpdateCardForPeng(proto.discard());

        // send peng succeed msg
        proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
        proto.set_next_operate_player_id(player_id);
        for (auto& p : players_) {
            this->SendPlayCardMsg(proto, p->player_id());
        }

        // remove player of sended msg peng
        this->RemovePlayerOfSendedMsgPeng(player_id);

        break;
    }
    case PlayCardOperationIDs::OPERATION_PENG_GANG: {
        if ( !player->IsPengAndGang(proto.discard()) ) {
            // TODO : log
            // TODO : specify error code
            return MsgCodes::MSG_RESPONSE_CODE_FAILED1;
        }

        // update hand card
        player->UpdateCardForPengAndGang(proto.discard());

        // send peng and gang succeed msg
        proto.set_next_operate_player_id(player_id);
        for (auto& p : players_) {
            if (p->player_id() == player_id) {
                auto new_card = this->next_one_new_card();
                p->UpdateInvisibleHandCard(new_card);
                auto ret = p->GetAvailableOperationID(new_card);
                p->set_cur_available_operation_id(ret);
                proto.set_my_available_operation_id(ret);
                proto.set_new_card(new_card);                
            } else {
                p->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
                proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
                proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
            }

            this->SendPlayCardMsg(proto, p->player_id());
        }

        // remove player of sended msg peng gang
        this->RemovePlayerOfSendedMsgPeng(player_id);

        break;
    }
    case PlayCardOperationIDs::OPERATION_MING_GANG: {
        if ( !player->IsMingGang(proto.discard()) ) {
            // TODO : log
            // TODO : specify error code
            return MsgCodes::MSG_RESPONSE_CODE_FAILED1;
        }

        // update hand card
        player->UpdateCardForMingGang(proto.discard());

        // send ming gang succeed msg
        proto.set_next_operate_player_id(player_id);
        for (auto& p : players_) {
            if (p->player_id() == player_id) {
                auto new_card = this->next_one_new_card();
                p->UpdateInvisibleHandCard(new_card);
                auto ret = p->GetAvailableOperationID(new_card);
                p->set_cur_available_operation_id(ret);
                proto.set_my_available_operation_id(ret);
                proto.set_new_card(new_card);                
            } else {
                p->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
                proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
                proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
            }

            this->SendPlayCardMsg(proto, p->player_id());
        }

        break;
    }
    case PlayCardOperationIDs::OPERATION_AN_GANG: {
        if ( !player->IsAnGang(proto.discard()) ) {
            // TODO : log
            // TODO : specify error code
            return MsgCodes::MSG_RESPONSE_CODE_FAILED1;
        }

        // update hand card
        player->UpdateCardForAnGang(proto.discard());

        // send an gang succeed msg
        proto.set_next_operate_player_id(player_id);
        for (auto& p : players_) {
            if (p->player_id() == player_id) {
                auto new_card = this->next_one_new_card();
                p->UpdateInvisibleHandCard(new_card);
                auto ret = p->GetAvailableOperationID(new_card);
                p->set_cur_available_operation_id(ret);
                proto.set_my_available_operation_id(ret);
                proto.set_new_card(new_card);
            } else {
                p->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
                proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
                proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
            }

            this->SendPlayCardMsg(proto, p->player_id());
        }

        break;
    }
    case PlayCardOperationIDs::OPERATION_BU_HUA: {
        // check hand cards
        if ( !player->InvisibleHandCardsContains(proto.discard()) ) {
            // TODO : log
            // TODO : specify error code
            return MsgCodes::MSG_RESPONSE_CODE_FAILED1;
        }

        // update hand card and discard
        player->UpdateCardForDiscard(proto.discard());

        // send bu hua succeed msg
        for (auto& p : players_) {
            auto playerid = p->player_id();
            if (playerid == player_id) { // get a new card for the player of bu hua
                auto new_card = this->next_one_new_card();
                p->UpdateInvisibleHandCard(new_card);
                auto ret = p->GetAvailableOperationID(new_card);
                p->set_cur_available_operation_id(ret);
                proto.set_my_available_operation_id(ret);
                proto.set_new_card(new_card);
                proto.set_next_operate_player_id(playerid);
            } else {
                p->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
                proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
                proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
            }

            this->SendPlayCardMsg(proto, playerid);
        }
    }
    case PlayCardOperationIDs::OPERATION_HU: {
        if (1 == players_sended_msg_hu_.size()) {
            if (player_id != players_sended_msg_hu_.at(0)->player_id()) {
                // TODO : log
                // TODO : specify error code
                return MsgCodes::MSG_RESPONSE_CODE_FAILED1;
            }

            if ( !player->IsHu(proto.discard()) ) {
                // TODO : log
                // TODO : specify error code
                return MsgCodes::MSG_RESPONSE_CODE_FAILED1;
            }

            // send hu msg to all players
            proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
            proto.set_next_operate_player_id(player_id);
            for (auto& p : players_) {
                this->SendPlayCardMsg(proto, p->player_id());
            }

            players_sended_msg_hu_.clear();

        } else if (2 == players_sended_msg_hu_.size()) {
            this->RemovePlayerOfSendedMsgHu(player_id);

        } else if (3 == players_sended_msg_hu_.size()) {
            this->RemovePlayerOfSendedMsgHu(player_id);
        }

        break;
    }
    case PlayCardOperationIDs::OPERATION_ZI_MO: {
        if (!player->IsZimo()) {
            // TODO : log
            // TODO : specify error code
            return MsgCodes::MSG_RESPONSE_CODE_FAILED1;
        }

        // send zi mo succeed msg        
        proto.set_discard(CardConstants::INVALID_CARD_VALUE);
        proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
        proto.set_next_operate_player_id(player_id);
        for (auto& p : players_) {
            auto bev = PlayerManager::instance()->GetOnlinePlayerBufferevent(p->player_id());
            if (nullptr != bev) {
                MsgManager::instance()->SendMsg((msg_header_t)MsgTypes::S2C_MSG_TYPE_ROOM,
                    (msg_header_t)MsgIDs::MSG_ID_ROOM_PLAY_CARD,
                    (msg_header_t)MsgCodes::MSG_RESPONSE_CODE_SUCCESS,
                    proto,
                    bev);
            }
            else {
                // TODO : log
            }
        }

        break;
    }
    case PlayCardOperationIDs::OPERATION_GIVE_UP: {
        this->DealWithOperationGiveUp(proto, player);
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
void Room<Player>::DealWithOperationDiscard(gamer::protocol::PlayCardMsgProtocol& proto,
                                            Player* player) {
    last_discard_player_ = player;

    // update hand card and discard
    player->UpdateCardForDiscard(proto.discard());

    // check whether is hu for other players
    auto player_id = player->player_id();
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
                // TODO : log
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

            return;
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
                auto ret = right_player->GetAvailableOperationID(new_card);
                right_player->set_cur_available_operation_id(ret);
                proto.set_my_available_operation_id(ret);
                proto.set_new_card(new_card);
                proto.set_next_operate_player_id(playerid);
                next_operation_player_id = playerid;
            }
            else {
                right_player->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
                proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
                proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
                proto.set_next_operate_player_id(next_operation_player_id);
                proto.set_has_next_operate_player_new_card(true);
            }

            this->SendPlayCardMsg(proto, playerid);
        }
    }
}

template<typename Player>
void Room<Player>::DealWithOperationGiveUp(gamer::protocol::PlayCardMsgProtocol& proto,
                                           Player* player) {
    int available_operation_id = player->cur_available_operation_id();
    switch (available_operation_id)
    {
    case PlayCardOperationIDs::OPERATION_CHI: {
        // send a new card to player
        auto new_card = this->next_one_new_card();
        player->UpdateInvisibleHandCard(new_card);
        auto ret = player->GetAvailableOperationID(new_card);
        player->set_cur_available_operation_id(ret);
        proto.set_my_available_operation_id(ret);
        proto.set_new_card(new_card);
        proto.set_next_operate_player_id(player->player_id());
        proto.set_has_next_operate_player_new_card(true);

        this->SendPlayCardMsg(proto, player->player_id());

        // send new card msg to other player
        proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
        proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
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

        if (0 != players_sended_msg_hu_.size() || nullptr == last_discard_player_)
            return;

        // check whether is peng
        auto player_peng_id = 0;
        for (auto& p : players_) {
            if (p->player_id() != player->player_id() &&
                p->player_id() != last_discard_player_->player_id()) {
                auto count = p->CountInvisibleHandCards(proto.discard());
                if (3 == count) {
                    p->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_PENG_GANG);
                    proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_PENG_GANG);
                    player_peng_id = p->player_id();
                    break;
                } else if (2 == count) {
                    p->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_PENG);
                    proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_PENG);
                    player_peng_id = p->player_id();
                    break;
                }
            }
        }

        if (0 != player_peng_id) {
            this->SendPlayCardMsg(proto, player_peng_id);
        } else {
            // check whether is chi
            auto right_player = this->GetTheRightPlayer(last_discard_player_->player_id());
            int cards[9] = { 0 };
            int len = 0;
            if (right_player->IsChi(proto.discard(), cards, len)) {
                right_player->set_cur_available_operation_id(PlayCardOperationIDs::OPERATION_CHI);
                proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_CHI);
                proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
                proto.set_next_operate_player_id(right_player->player_id());
                for (auto i = 0; i < len; i++) {
                    proto.add_operating_cards(cards[i]);
                }
                this->SendPlayCardMsg(proto, right_player->player_id());
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
void Room<Player>::DealWithOperationGiveUpPengOrPengGang(gamer::protocol::PlayCardMsgProtocol& 
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
        auto ret = right_player->GetAvailableOperationID(new_card);
        right_player->set_cur_available_operation_id(ret);
        proto.set_my_available_operation_id(ret);
        proto.set_new_card(new_card);
        proto.set_next_operate_player_id(right_player_id);
        this->SendPlayCardMsg(proto, right_player_id);

        // send new card msg to other player
        proto.set_my_available_operation_id(PlayCardOperationIDs::OPERATION_NONE);
        proto.set_new_card(CardConstants::INVALID_CARD_VALUE);
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
inline bool Room<Player>::IsLeftPlayer(int src_player_id, int target_player_id) {
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
bool Room<Player>::SendPlayCardMsg(gamer::protocol::PlayCardMsgProtocol& proto, 
                                   int player_id) const {
    auto bev = PlayerManager::instance()->GetOnlinePlayerBufferevent(player_id);
    if (nullptr != bev) {
        return MsgManager::instance()->SendMsg((msg_header_t)MsgTypes::S2C_MSG_TYPE_ROOM,
                                               (msg_header_t)MsgIDs::MSG_ID_ROOM_PLAY_CARD,
                                               (msg_header_t)MsgCodes::MSG_RESPONSE_CODE_SUCCESS,
                                               proto,
                                               bev);
    } else {
        // TODO : log
        return false;
    }
    return false;
}

template<typename Player>
void Room<Player>::RemovePlayerOfSendedMsgHu(int player_id) {
    for (auto itr = players_sended_msg_hu_.begin(); itr != players_sended_msg_hu_.end(); itr++) {
        if ((*itr)->player_id() == player_id) {
            players_sended_msg_hu_.erase(itr);
            break;
        }
    }
}

template<typename Player>
void gamer::Room<Player>::RemovePlayerOfSendedMsgPeng(int player_id) {
    for (auto itr = players_sended_msg_peng_.begin(); itr != players_sended_msg_peng_.end(); 
        itr++) {
        if ((*itr)->player_id() == player_id) {
            players_sended_msg_peng_.erase(itr);
            break;
        }
    }
}

template<typename Player>
bool gamer::Room<Player>::Init(int room_id) {
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