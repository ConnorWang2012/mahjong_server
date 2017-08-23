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
    ,cur_available_operation_id_(PlayCardOperationIDs::OPERATION_NONE) {
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

inline void Player::set_player_id(int player_id) {
	player_id_ = player_id;
}

inline int Player::player_id() const {
	return player_id_;
}

inline void Player::set_is_online(bool online) {
	is_online_ = online;
}

inline bool Player::is_online() const {
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

    // add the discard to discards or season cards or flower cards
    if (discard > CardConstants::INVALID_CARD_VALUE && 
        discard < CardConstants::SEASON_SPRING) {
        cards_msg_proto_.add_discards(discard);
    } else if (discard >= CardConstants::SEASON_SPRING &&
               discard <= CardConstants::SEASON_WINTER) {
        cards_msg_proto_.add_season_cards(discard);
  
    } else if (discard >= CardConstants::FLOWER_PLUM &&
               discard <= CardConstants::FLOWER_BAMBOO) {
        cards_msg_proto_.add_flower_cards(discard);
    }
}

bool Player::UpdateCardForChi(int card_of_chi, int card_match_chi_1, int card_match_chi_2) {
    // check invisible hand cards
    if ( !this->InvisibleHandCardsContains(card_match_chi_1) ||
         !this->InvisibleHandCardsContains(card_match_chi_2)) {
        return false;
    }

    // check whether match chi
    auto min = std::min(std::min(card_of_chi, card_match_chi_1), card_match_chi_2);
    auto max = std::max(std::max(card_of_chi, card_match_chi_1), card_match_chi_2);
    if (2 != max - min) {
        return false;
    }

    // remove invisible hand cards
    this->RemoveInvisibleHandCards(card_match_chi_1, 1);
    this->RemoveInvisibleHandCards(card_match_chi_2, 1);

    // add visible hand cards
    cards_msg_proto_.add_visible_hand_cards(card_of_chi);
    cards_msg_proto_.add_visible_hand_cards(card_match_chi_1);
    cards_msg_proto_.add_visible_hand_cards(card_match_chi_2);

    return true;
}

void Player::UpdateCardForPeng(int card_of_peng) {
    // remove 2 cards(value equal card_of_peng) from invisible hand cards
    if ( !this->RemoveInvisibleHandCards(card_of_peng, 2) ) {
        return;
    }

    // add 3 peng cards to visible hand cards
    auto size = cards_msg_proto_.visible_hand_cards_size();
    cards_msg_proto_.mutable_visible_hand_cards()->Resize(size + 3, card_of_peng);
}

void Player::UpdateCardForPengAndGang(int card_of_peng_gang) {
    // remove 3 cards(value equal card_of_peng_gang) from invisible hand cards
    if ( !this->RemoveInvisibleHandCards(card_of_peng_gang, 3) ) {
        return;
    }

    // add 4 peng cards to visible hand cards
    auto size = cards_msg_proto_.visible_hand_cards_size();
    cards_msg_proto_.mutable_visible_hand_cards()->Resize(size + 4, card_of_peng_gang);
}

void Player::UpdateCardForMingGang(int card_of_ming_gang) {
    // 1.remove 4 cards(value equal card_of_ming_gang) from invisible hand cards 
    // and add 4 cards(value equal card_of_ming_gang) to visible hand cards
    // or
    // 2.remove 1 cards(value equal card_of_ming_gang) from invisible hand cards 
    // and add 1 card(value equal card_of_ming_gang) to visible hand cards

    if (4 == this->CountInvisibleHandCards(card_of_ming_gang)) {
        this->RemoveInvisibleHandCards(card_of_ming_gang, 4);
        auto size = cards_msg_proto_.visible_hand_cards_size();
        cards_msg_proto_.mutable_visible_hand_cards()->Resize(size + 4, card_of_ming_gang);
    } else if (3 == this->CountVisibleHandCards(card_of_ming_gang)) {
        this->RemoveInvisibleHandCards(card_of_ming_gang, 1);
        cards_msg_proto_.mutable_visible_hand_cards()->Add(card_of_ming_gang);
    }
}

void Player::UpdateCardForAnGang(int card_of_an_gang) {
    // remove 4 cards(value equal card_of_an_gang) from invisible hand cards
    if ( !this->RemoveInvisibleHandCards(card_of_an_gang, 4) ) {
        return;
    }

    // add 4 cards(value equal card_of_an_gang) to an gang cards
    auto size = cards_msg_proto_.an_gang_cards_size();
    cards_msg_proto_.mutable_an_gang_cards()->Resize(size + 4, card_of_an_gang);
}

void Player::UpdateInvisibleHandCard(int new_card) {
    if (cards_msg_proto_.invisible_hand_cards_size() <= CardConstants::ONE_PLAYER_CARD_NUM) {
        cards_msg_proto_.add_invisible_hand_cards(new_card);
    }
}

int Player::GetAvailableOperationID(int card) const {
    // zi mo or ming gang or an gang or bu hua
    if (this->IsBuhua(card)) {
        return PlayCardOperationIDs::OPERATION_BU_HUA;
    } else if (this->IsZimo()) {
        return PlayCardOperationIDs::OPERATION_ZI_MO;
    } else if (this->IsMingGang(card)) {
        return PlayCardOperationIDs::OPERATION_MING_GANG;
    } else if (this->IsAnGang(card)) {
        return PlayCardOperationIDs::OPERATION_AN_GANG;
    }
    return PlayCardOperationIDs::OPERATION_NONE;
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

bool Player::IsZimo() const {
    int cards[CardConstants::ONE_PLAYER_CARD_NUM2] = { 0 };
    auto len = 0;
    this->GetInvisibleHandCards(cards, len);
    if (len > CardConstants::ONE_PLAYER_CARD_NUM2) {
        // TODO : error log
        return false;
    }
    return ChessCard::IsHu(cards, len);
}

bool Player::IsChi(int card) const {
    if (card < CardConstants::BAMBOO_1 || card > CardConstants::FLOWER_BAMBOO) {
        // TODO : error log
        return false;
    }

    auto card_pre = card - 1;
    auto card_pre2 = card - 2;
    auto card_next = card + 1;
    auto card_next2 = card + 2;
    auto has_card_pre = false;
    auto has_card_pre2 = false;
    auto has_card_next = false;
    auto has_card_next2 = false;
    for (int i = 0; i < cards_msg_proto_.invisible_hand_cards_size(); i++) {
        auto cardtmp = cards_msg_proto_.invisible_hand_cards(i);
        if (cardtmp == card_pre) {
            has_card_pre = true;
        }
        else if (cardtmp == card_pre2) {
            has_card_pre2 = true;
        }
        else if (cardtmp == card_next) {
            has_card_next = true;
        }
        else if (cardtmp == card_next2) {
            has_card_next2 = true;
        }

        if ((has_card_pre && has_card_pre2) ||
            (has_card_pre && has_card_next) ||
            (has_card_next && has_card_next2)) {
            return true;
        }
    }

    return false;
}

bool Player::IsChi(int card, int* cards_chi, int& cards_chi_len) const {
    if (card < CardConstants::BAMBOO_1 || 
        card > CardConstants::FLOWER_BAMBOO ||
        nullptr == cards_chi) {
        // TODO : error log
        return false;
    }

    auto card_pre = card - 1;
    auto card_pre2 = card - 2;
    auto card_next = card + 1;
    auto card_next2 = card + 2;
    auto has_card_pre = false;
    auto has_card_pre2 = false;
    auto has_card_next = false;
    auto has_card_next2 = false;
    for (int i = 0; i < cards_msg_proto_.invisible_hand_cards_size(); i++) {
        auto cardtmp = cards_msg_proto_.invisible_hand_cards(i);
        if (cardtmp == card_pre) {
            has_card_pre = true;
        } else if (cardtmp == card_pre2) {
            has_card_pre2 = true;
        } else if (cardtmp == card_next) {
            has_card_next = true;
        } else if (cardtmp == card_next2) {
            has_card_next2 = true;
        }
    }

    auto len = 0;
    if (has_card_pre && has_card_pre2) {
        cards_chi[0] = card_pre2;
        cards_chi[1] = card_pre;
        cards_chi[2] = card;
        len = 3;
    }
    if (has_card_pre && has_card_next) {
        cards_chi[len] = card_pre;
        cards_chi[len + 1] = card;
        cards_chi[len + 2] = card_next;
        len += 3;
    }
    if (has_card_next && has_card_next2) {
        cards_chi[len] = card;
        cards_chi[len + 1] = card_next;
        cards_chi[len + 2] = card_next2;
        len += 3;
    }

    if (len > 0) {
        cards_chi_len = len;
        return true;
    }

    return false;
}

bool Player::IsPeng(int card) const {
    return this->CountInvisibleHandCards(card) >= 2;
}

bool Player::IsPengAndGang(int card) const {
    return this->CountInvisibleHandCards(card) == 3;
}

bool Player::IsMingGang(int card) const {
    return 4 == this->CountInvisibleHandCards(card) || 3 == this->CountVisibleHandCards(card);
}

bool Player::IsAnGang(int card) const {
    return 4 == this->CountInvisibleHandCards(card);
}

bool Player::IsBuhua(int card) const {
    if (card > CardConstants::DRAGON_WHITE && card <= CardConstants::FLOWER_BAMBOO) {
        return this->InvisibleHandCardsContains(card);
    }
    return false;
}

bool Player::Init(int player_id) {
	player_id_ = player_id;
	return true;
}

void Player::GetInvisibleHandCards(int* cards, int& len) const {
    len = 0;
    for (int i = 0; i < cards_msg_proto_.invisible_hand_cards_size(); i++) {
        if (cards_msg_proto_.invisible_hand_cards(i) < CardConstants::SEASON_SPRING) {
            cards[len++] = cards_msg_proto_.invisible_hand_cards(i);
        }
    }
}

int Player::CountInvisibleHandCards(int invisible_card) const {
    auto count = 0;
    for (int i = 0; i < cards_msg_proto_.invisible_hand_cards_size(); i++) {
        if (cards_msg_proto_.invisible_hand_cards(i) == invisible_card) {
            count++;
        }
    }
    return count;
}

int Player::CountVisibleHandCards(int visible_card) const {
    auto count = 0;
    for (int i = 0; i < cards_msg_proto_.visible_hand_cards_size(); i++) {
        if (cards_msg_proto_.visible_hand_cards(i) == visible_card) {
            count++;
        }
    }
    return count;
}

bool Player::RemoveInvisibleHandCards(int card, int num) {
    if (card < CardConstants::BAMBOO_1 ||
        card > CardConstants::FLOWER_BAMBOO ||
        num > 4) {
        return false;
    }

    auto cards = cards_msg_proto_.mutable_invisible_hand_cards();
    auto n = cards->size();
    auto count = 0;
    for (int i = 0; i < n; i++) {
        if (cards->Get(i) == card) {
            auto index = n - count - 1;
            if (index > -1 && index != i) {
                cards->SwapElements(i, index);
            }
            ++count;
        }
        if (count >= num) {
            for (auto j = 0; j < num; j++) {
                cards->RemoveLast();
            }

            return true;
        }
    }

    return false;
}

}