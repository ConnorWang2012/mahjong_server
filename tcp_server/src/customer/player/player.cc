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
	,is_online_(false) {
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
	for (auto i = 0; i < cards_msg_proto_.invisible_hand_cards_size(); i++) {
		if (cards_msg_proto_.invisible_hand_cards(i) == card) {
			return true;
		}
	}
	return false;
}

void Player::UpdateCardForDiscard(int discard) {
	// remove the discard from invisible hand cards
    auto cards = cards_msg_proto_.mutable_invisible_hand_cards();
    auto n = cards->size();
    for (int i = 0; i < n; i++) {
        if (cards->Get(i) == discard) {
            if (i != n - 1) {
                cards->SwapElements(i, n - 1);
            }            
            cards->RemoveLast();
            break;
        }
    }

    // add the discard to discards
    cards_msg_proto_.add_discards(discard);
}

void Player::UpdateInvisibleHandCard(int new_card) {
    if (cards_msg_proto_.invisible_hand_cards_size() <= CardConstants::ONE_PLAYER_CARD_NUM) {
        cards_msg_proto_.add_invisible_hand_cards(new_card);
    }
}

void Player::GetInvisibleHandCards(int* cards, int& len) const {
    len = 0;
    for (int i = 0; i < cards_msg_proto_.invisible_hand_cards_size(); i++) {
        if (cards_msg_proto_.invisible_hand_cards(i) < CardConstants::SEASON_SPRING) {
            cards[len++] = cards_msg_proto_.invisible_hand_cards(i);
        }
    }
}

int Player::GetAvailableOperationID(int new_card) const {
    // zimo or ming gang or an gang or bu hua
    // zi mo
    int cards[CardConstants::ONE_PLAYER_CARD_NUM2] = { 0 };
    auto len = 0;
    this->GetInvisibleHandCards(cards, len);
    if (len >= CardConstants::ONE_PLAYER_CARD_NUM2) {
        // TODO : error log
        return PlayCardOperationIDs::NEW_CARD;
    }

    if (len <= CardConstants::ONE_PLAYER_CARD_NUM) {
        cards[len] = new_card;
        len += 1;
    }

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

bool Player::IsHu(int new_card) const
{
    int cards[CardConstants::ONE_PLAYER_CARD_NUM2] = { 0 };
    auto len = 0;
    this->GetInvisibleHandCards(cards, len);
    if (len > CardConstants::ONE_PLAYER_CARD_NUM2) {
        // TODO : error log
        return false;
    }

    if (len <= CardConstants::ONE_PLAYER_CARD_NUM) {
        cards[len] = new_card;
        len += 1;
    }

    return ChessCard::IsHu(cards, len);
}

bool Player::Init(int player_id) {
	player_id_ = player_id;
	return true;
}

}