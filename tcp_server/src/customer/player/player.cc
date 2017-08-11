/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    player.cc
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-14
@ description:  player.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#include "player.h"

#include "base/macros.h"
#include "customer/util/util.h"
#include "customer/room/card_constants.h"
#include "framework/util/chess_card_algorithm.h"

namespace gamer {

Player::Player()
	:player_id_(0)
	,is_online_(false)
	,new_invisible_hand_card_index_(-1) {
}

Player* Player::Create(int player_id) {
	auto player = new Player;
	if (nullptr != player) {
		if (!player->Init(player_id)) {
			SAFE_DELETE(player);
			return nullptr;
		}
	}
	return player;
}

void Player::set_player_id(int player_id) {
	player_id_ = player_id;
}

int Player::player_id() const {
	return player_id_;
}

void Player::set_is_online(bool online) {
	is_online_ = online;
}

bool Player::is_online() const {
	return is_online_;
}

void Player::SetHandCards(const protocol::PlayerCardsMsgProtocol& from) {
	cards_msg_proto_.CopyFrom(from);
}

bool Player::InvisibleHandCardsContains(int card) const {
	auto cards_size = cards_msg_proto_.invisible_hand_cards_size();
	for (auto i = 0; i < cards_size; i++) {
		if (cards_msg_proto_.invisible_hand_cards(i) == card) {
			return true;
		}
	}
	return false;
}

void Player::UpdateCardForDiscard(int discard) {
	// update invisible hand cards
    auto n = cards_msg_proto_.invisible_hand_cards_size();
    for (int i = 0; i < n; i++) {
        if (cards_msg_proto_.invisible_hand_cards(i) == discard) {
            cards_msg_proto_.set_invisible_hand_cards(i, CardConstants::INVALID_CARD_VALUE);
            new_invisible_hand_card_index_ = i;
            break;
        }
    }

    // update discard
    cards_msg_proto_.add_discards(discard);
}

void Player::UpdateInvisibleHandCard(int new_card) {
    auto n = cards_msg_proto_.invisible_hand_cards_size();
    if (CardConstants::ONE_PLAYER_CARD_NUM == n) {
        cards_msg_proto_.add_invisible_hand_cards(new_card);
    } else if (new_invisible_hand_card_index_ > -1 && 
               new_invisible_hand_card_index_ < n) {
        cards_msg_proto_.set_invisible_hand_cards(new_invisible_hand_card_index_, new_card);
    }
}

void Player::GetInvisibleHandCards(int* cards, int& len) const {
    len = 0;
    for (int i = 0; i < cards_msg_proto_.invisible_hand_cards_size(); i++) {
        if (cards_msg_proto_.invisible_hand_cards(i) != CardConstants::INVALID_CARD_VALUE) {
            cards[len++] = cards_msg_proto_.invisible_hand_cards(i);
        }
    }
}

int Player::GetAvailableOperationID(int new_card) const {
    // zimo or ming gang or an gang or bu hua
    // zi mo
    int cards[14] = { 0 };
    int len = 0;
    this->GetInvisibleHandCards(cards, len);
    cards[len] = new_card;
    len += 1;
    if (ChessCard::IsHu(cards, len)) {
        return PlayCardOperationIDs::MELD_CARD_ZI_MO;
    }

    // ming gang
    auto n = cards_msg_proto_.visible_hand_cards_size();
    auto count = 0;
    for (int i = 0; i < n; i++) {
        if (cards_msg_proto_.visible_hand_cards(i) == new_card) {
            count++;
        }
    }
    if (3 == count) {
        return PlayCardOperationIDs::MELD_CARD_GANG;
    }

    // an gang
    n = cards_msg_proto_.invisible_hand_cards_size();
    count = 0;
    for (int i = 0; i < n; i++) {
        if (cards_msg_proto_.invisible_hand_cards(i) == new_card) {
            count++;
        }
    }
    if (3 == count) {
        return PlayCardOperationIDs::MELD_CARD_AN_GANG;
    }

    // bu hua
    if (new_card >= CardConstants::CARD_VALUE_SEASON_OR_FLOWER_1) {
        return PlayCardOperationIDs::MELD_CARD_BU_HUA;
    }

    return PlayCardOperationIDs::NEW_CARD;
}

bool Player::Init(int player_id) {
	player_id_ = player_id;
	return true;
}

}