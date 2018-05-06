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

#include <algorithm>

#include "framework/base/macros.h"
#include "framework/algorithm/chess_card_algorithm.h"
#include "customer/util/util.h"
#include "customer/room/card_constants.h"

namespace gamer {

Player::Player(id_t player_id)
	: Player(player_id, PlayerTypes::REAL_PLAYER, Sex::FEMALE) {
}

Player::Player(id_t player_id, PlayerTypes type, Sex sex)
    : player_id_(player_id),
      player_type_(type),
      sex_(sex),
	  account_(""),
      cur_table_id_(0),
      is_online_(false),
      cur_available_operation_id_(PlayCardOperationIDs::OPERATION_NONE),
      has_selected_operation_ting_(false),
      cards_msg_proto_(nullptr),
      num_ming_gang_(0),
      num_an_gang_(0),
      num_win_(0){
}

Player* Player::Create(id_t player_id) {
	auto player = new (std::nothrow) Player(player_id);
	if (nullptr != player) {
		if ( !player->Init() ) {
			SAFE_DELETE(player);
			return nullptr;
		}
	}
	return player;
}

void Player::InitForGameStart() {

}

void Player::InitPlayerCards(PlayerCardsMsgProtocol* proto) {
    if (nullptr != proto) {
        cards_msg_proto_ = proto;
        auto cards = proto->mutable_invisible_hand_cards();
        std::sort(cards->begin(), cards->end());
    }
}

void Player::CopyInvisibleHandCardsTo(RepeatedFieldInt& to) {
    to.CopyFrom(cards_msg_proto_->invisible_hand_cards());
}

bool Player::InvisibleHandCardsContains(int card) const {
	for (auto i = 0; i < cards_msg_proto_->invisible_hand_cards_size(); i++) {
		if (cards_msg_proto_->invisible_hand_cards(i) == card) {
			return true;
		}
	}
	return false;
}

void Player::UpdateCardForDiscard(int discard) {
	// remove the discard from invisible hand cards
    auto cards = cards_msg_proto_->mutable_invisible_hand_cards();
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
        cards_msg_proto_->add_discards(discard);
    } else if (discard >= CardConstants::SEASON_SPRING &&
               discard <= CardConstants::SEASON_WINTER) {
        cards_msg_proto_->add_season_cards(discard);
  
    } else if (discard >= CardConstants::FLOWER_PLUM &&
               discard <= CardConstants::FLOWER_BAMBOO) {
        cards_msg_proto_->add_flower_cards(discard);
    }
}

bool Player::UpdateCardForChi(int card_of_chi, int card_match_chi_1, int card_match_chi_2) {
    // check invisible hand cards
    if ( !this->InvisibleHandCardsContains(card_match_chi_1) ||
         !this->InvisibleHandCardsContains(card_match_chi_2)) {
        return false;
    }

    // check whether match chi
	//int min = std::min(std::min(card_of_chi, card_match_chi_1), card_match_chi_2);
    //int max = std::max(std::max(card_of_chi, card_match_chi_1), card_match_chi_2);
	auto min1 = card_of_chi < card_match_chi_1 ? card_of_chi : card_match_chi_1;
	auto max1 = card_of_chi > card_match_chi_1 ? card_of_chi : card_match_chi_1;
	auto min = min1 < card_match_chi_2 ? min1 : card_match_chi_2;
	auto max = max1 > card_match_chi_2 ? max1 : card_match_chi_2;
    if (2 != max - min) {
        return false;
    }

    // remove invisible hand cards
    this->RemoveInvisibleHandCards(card_match_chi_1, 1);
    this->RemoveInvisibleHandCards(card_match_chi_2, 1);

    // add chi cards
    cards_msg_proto_->add_chi_cards(card_of_chi);
    cards_msg_proto_->add_chi_cards(card_match_chi_1);
    cards_msg_proto_->add_chi_cards(card_match_chi_2);

    return true;
}

void Player::UpdateCardForPeng(int card_of_peng) {
    // remove 2 cards(value equal card_of_peng) from invisible hand cards
    if ( !this->RemoveInvisibleHandCards(card_of_peng, 2) ) {
        return;
    }

    // add 3 peng cards to visible hand cards
    auto size = cards_msg_proto_->peng_cards_size();
    cards_msg_proto_->mutable_peng_cards()->Resize(size + 3, card_of_peng);
}

void Player::UpdateCardForPengAndGang(int card_of_peng_gang) {
    // remove 3 cards(value equal card_of_peng_gang) from invisible hand cards
    if ( !this->RemoveInvisibleHandCards(card_of_peng_gang, 3) ) {
        return;
    }

    // add 4 peng cards to ming gang cards
    auto size = cards_msg_proto_->ming_gang_cards_size();
    cards_msg_proto_->mutable_ming_gang_cards()->Resize(size + 4, card_of_peng_gang);
}

bool Player::UpdateCardForBuhua(int* cards_of_hua_removed, int& num_cards_of_hua_removed) {
    auto count = 0;
    for (auto i = (int)CardConstants::SEASON_SPRING; i < CardConstants::FLOWER_BAMBOO + 1; i++) {
        if (this->RemoveInvisibleHandCards(i, 1)) {
            cards_of_hua_removed[count++] = i;
        }
    }
    if (count > 0) {
        num_cards_of_hua_removed = count;
        return true;
    }
    return false;
}

void Player::UpdateCardForMingGang(int card_of_ming_gang) {
    // 1.remove 4 cards(value equal card_of_ming_gang) from invisible hand cards 
    // and add 4 cards(value equal card_of_ming_gang) to ming gang cards
    // or
    // 2.remove 1 card(value equal card_of_ming_gang) from invisible hand cards    
    // and remove 3 cards(value equal card_of_ming_gang) from peng cards 
    // and add 4 cards(value equal card_of_ming_gang) to ming gang cards

    if (4 == this->CountInvisibleHandCards(card_of_ming_gang)) {
        this->RemoveInvisibleHandCards(card_of_ming_gang, 4);
        auto size = cards_msg_proto_->ming_gang_cards_size();
        cards_msg_proto_->mutable_ming_gang_cards()->Resize(size + 4, card_of_ming_gang);
		num_ming_gang_++;
    } else if (this->PengCardsContains(card_of_ming_gang)) {
        this->RemoveInvisibleHandCards(card_of_ming_gang, 1);
        cards_msg_proto_->mutable_ming_gang_cards()->Add(card_of_ming_gang);
		num_ming_gang_++;
    }
}

void Player::UpdateCardForAnGang(int card_of_an_gang) {
    // remove 4 cards(value equal card_of_an_gang) from invisible hand cards
    if ( !this->RemoveInvisibleHandCards(card_of_an_gang, 4) ) {
        return;
    }

    // add 4 cards(value equal card_of_an_gang) to an gang cards
    auto size = cards_msg_proto_->an_gang_cards_size();
    cards_msg_proto_->mutable_an_gang_cards()->Resize(size + 4, card_of_an_gang);
	num_an_gang_++;
}

void Player::UpdateInvisibleHandCard(int new_card) {
    if (cards_msg_proto_->invisible_hand_cards_size() <= CardConstants::ONE_PLAYER_CARD_NUM) {
        cards_msg_proto_->add_invisible_hand_cards(new_card);
    }
}

int Player::GetAvailableOperationID(int new_card, PlayCardMsgProtocol* proto) const {
    // bu hua or ting or zimo or ming gang or an gang
    auto ting_or_zimo_operation = 0;
    if (this->IsBuhua(proto)) {
        return PlayCardOperationIDs::OPERATION_BU_HUA;
    } else if (this->has_selected_operation_ting()) {
        if (this->IsZimo()) {
            return PlayCardOperationIDs::OPERATION_ZI_MO;
        } else if (this->IsMingGang(new_card)) {
            return PlayCardOperationIDs::OPERATION_MING_GANG;
        } else if (this->IsAnGang(new_card)) {
            return PlayCardOperationIDs::OPERATION_AN_GANG;
        }
    } else if (this->GetTingOrZimoOperationID(ting_or_zimo_operation, proto)) {
        return ting_or_zimo_operation;
    } else if (this->IsMingGang(new_card)) {
        return PlayCardOperationIDs::OPERATION_MING_GANG;
    } else if (this->IsAnGang(new_card)) {
        return PlayCardOperationIDs::OPERATION_AN_GANG;
    }
    return PlayCardOperationIDs::OPERATION_NONE;
}

bool Player::IsTing(TingCardMsgProtocol* proto) const {
    int cards[CardConstants::ONE_PLAYER_CARD_NUM2] = { 0 };
    auto len = 0;
    this->GetInvisibleHandCards(cards, len);
    if (len > CardConstants::ONE_PLAYER_CARD_NUM2) {
        // TODO : error log
        return false;
    }
    return ChessCard::IsTing(cards, len, proto);
}

bool Player::IsTing() const
{
    int cards[CardConstants::ONE_PLAYER_CARD_NUM2] = { 0 };
    auto len = 0;
    this->GetInvisibleHandCards(cards, len);
    if (len > CardConstants::ONE_PLAYER_CARD_NUM2) {
        // TODO : error log
        return false;
    }
    return ChessCard::IsTing(cards, len);
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
    if (card < CardConstants::BAMBOO_1 ||
        card > CardConstants::DOT_9) {
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
    for (int i = 0; i < cards_msg_proto_->invisible_hand_cards_size(); i++) {
        auto cardtmp = cards_msg_proto_->invisible_hand_cards(i);
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
    }

    if (card <= CardConstants::BAMBOO_9) {
        if (has_card_pre && has_card_pre2) {
            return true;
        }
        if (has_card_pre && has_card_next && card_next <= CardConstants::BAMBOO_9) {
            return true;
        }
        if (has_card_next && has_card_next2 && card_next2 <= CardConstants::BAMBOO_9) {
            return true;
        }
    } else if (card <= CardConstants::CHARACTER_9) {
        if (has_card_pre && has_card_pre2 && card_pre2 >= CardConstants::CHARACTER_1) {
            return true;
        }
        if (has_card_pre && has_card_next && card_pre >= CardConstants::CHARACTER_1 &&
            card_next <= CardConstants::CHARACTER_9) {
            return true;
        }
        if (has_card_next && has_card_next2 && card_next2 <= CardConstants::CHARACTER_9) {
            return true;
        }
    } else {
        if (has_card_pre && has_card_pre2 && card_pre2 >= CardConstants::DOT_1) {
            return true;
        }
        if (has_card_pre && has_card_next && card_pre >= CardConstants::DOT_1 &&
            card_next <= CardConstants::DOT_9) {
            return true;
        }
        if (has_card_next && has_card_next2 && card_next2 <= CardConstants::DOT_9) {
            return true;
        }
    }

    return false;
}

bool Player::IsChi(int card, int* cards_chi, int& cards_chi_len) const {
    if (card < CardConstants::BAMBOO_1 || 
        card > CardConstants::DOT_9 ||
        nullptr == cards_chi) {
        // TODO : error log
        return false;
    }

    auto card_pre       = card - 1;
    auto card_pre2      = card - 2;
    auto card_next      = card + 1;
    auto card_next2     = card + 2;
    auto has_card_pre   = false;
    auto has_card_pre2  = false;
    auto has_card_next  = false;
    auto has_card_next2 = false;
    for (int i = 0; i < cards_msg_proto_->invisible_hand_cards_size(); i++) {
        auto cardtmp = cards_msg_proto_->invisible_hand_cards(i);
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
    if (card <= CardConstants::BAMBOO_9) {
        if (has_card_pre && has_card_pre2) {
            cards_chi[0] = card_pre2;
            cards_chi[1] = card_pre;
            cards_chi[2] = card;
            len = 3;
        }
        if (has_card_pre && has_card_next && card_next <= CardConstants::BAMBOO_9) {
            cards_chi[len] = card_pre;
            cards_chi[len + 1] = card;
            cards_chi[len + 2] = card_next;
            len += 3;
        }
        if (has_card_next && has_card_next2 && card_next2 <= CardConstants::BAMBOO_9) {
            cards_chi[len] = card;
            cards_chi[len + 1] = card_next;
            cards_chi[len + 2] = card_next2;
            len += 3;
        }
    } else if (card <= CardConstants::CHARACTER_9) {
        if (has_card_pre && has_card_pre2 && card_pre2 >= CardConstants::CHARACTER_1) {
            cards_chi[0] = card_pre2;
            cards_chi[1] = card_pre;
            cards_chi[2] = card;
            len = 3;
        }
        if (has_card_pre && has_card_next && card_pre >= CardConstants::CHARACTER_1 &&
            card_next <= CardConstants::CHARACTER_9) {
            cards_chi[len] = card_pre;
            cards_chi[len + 1] = card;
            cards_chi[len + 2] = card_next;
            len += 3;
        }
        if (has_card_next && has_card_next2 && card_next2 <= CardConstants::CHARACTER_9) {
            cards_chi[len] = card;
            cards_chi[len + 1] = card_next;
            cards_chi[len + 2] = card_next2;
            len += 3;
        }
    } else {
        if (has_card_pre && has_card_pre2 && card_pre2 >= CardConstants::DOT_1) {
            cards_chi[0] = card_pre2;
            cards_chi[1] = card_pre;
            cards_chi[2] = card;
            len = 3;
        }
        if (has_card_pre && has_card_next && card_pre >= CardConstants::DOT_1 && 
            card_next <= CardConstants::DOT_9) {
            cards_chi[len] = card_pre;
            cards_chi[len + 1] = card;
            cards_chi[len + 2] = card_next;
            len += 3;
        }
        if (has_card_next && has_card_next2 && card_next2 <= CardConstants::DOT_9) {
            cards_chi[len] = card;
            cards_chi[len + 1] = card_next;
            cards_chi[len + 2] = card_next2;
            len += 3;
        }
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
    return 3 == this->CountInvisibleHandCards(card);
}

bool Player::IsMingGang(int card) const {
    if (4 == this->CountInvisibleHandCards(card)) {
        return true;
    } else if (this->PengCardsContains(card)) {
        return true;
    }
    return false;
}

bool Player::IsAnGang(int card) const {
    return 4 == this->CountInvisibleHandCards(card);
}

bool Player::IsBuhua(int* cards_of_hua, int& cards_of_hua_len) const {
    auto count = 0;
    for (auto i = (int)CardConstants::SEASON_SPRING; i < CardConstants::FLOWER_BAMBOO + 1; i++) {
        if (this->InvisibleHandCardsContains(i)) {
            cards_of_hua[count++] = i;
        }
    }

    if (count > 0) {
        cards_of_hua_len = count;
        return true;
    }
    return false;
}

bool Player::IsBuhua(PlayCardMsgProtocol* proto) const {
    auto ret = false;
    auto size = cards_msg_proto_->invisible_hand_cards_size();
    for (int i = size - 1; i > -1; i--) {
        if (ChessCard::is_season_or_flower(cards_msg_proto_->invisible_hand_cards(i))) {
            proto->add_operating_cards(cards_msg_proto_->invisible_hand_cards(i));
            ret = true;
        } else if (i <= size - 2) {
            break;
        }
    }
    return ret;
}

bool Player::IsBuhua(int new_card) const {
    return ChessCard::is_season_or_flower(new_card);
}

bool Player::IsBuhua() const
{
    for (auto i = (int)CardConstants::SEASON_SPRING; i < CardConstants::FLOWER_BAMBOO + 1; i++) {
        if (this->InvisibleHandCardsContains(i)) {
            return true;
        }
    }
    return false;
}

bool Player::Init() {
	return true;
}

void Player::GetInvisibleHandCards(int* cards, int& len) const {
    len = 0;
    for (int i = 0; i < cards_msg_proto_->invisible_hand_cards_size(); i++) {
        if (cards_msg_proto_->invisible_hand_cards(i) < CardConstants::SEASON_SPRING) {
            cards[len++] = cards_msg_proto_->invisible_hand_cards(i);
        }
    }
}

int Player::CountInvisibleHandCards(int invisible_card) const {
    auto count = 0;
    for (int i = 0; i < cards_msg_proto_->invisible_hand_cards_size(); i++) {
        if (cards_msg_proto_->invisible_hand_cards(i) == invisible_card) {
            count++;
        }
    }
    return count;
}

bool Player::PengCardsContains(int card) const {
    for (int i = 0; i < cards_msg_proto_->peng_cards_size(); i++) {
        if (cards_msg_proto_->peng_cards(i) == card) {
            return true;
        }
    }
    return false;
}

bool Player::RemoveInvisibleHandCards(int card, int num) {
    if (card < CardConstants::BAMBOO_1 ||
        card > CardConstants::FLOWER_BAMBOO ||
        num > 4) {
        return false;
    }

    auto cards = cards_msg_proto_->mutable_invisible_hand_cards();
    auto n = cards->size();
    auto count = 0;

    for (int i = 0; i < n; i++) {
        if (cards->Get(i) == card) {
		    auto index = n - count - 1;
			if (index < 0) {
				break;
			}

			if (cards->Get(index) == card) {
				++count;

				for (int j = index - 1; j > i; j--) {
					if (cards->Get(j) != card) {
						cards->SwapElements(i, j);
						break;
					} else {
						++count;
					}
				}
			} else if (index != i) {
				cards->SwapElements(i, index);
			}
			
			++count;
			if (count >= num) {
				for (auto j = 0; j < num; j++) {
					cards->RemoveLast();
				}
				return true;
			}
        }
    }

	if (count >= num) {
		for (auto j = 0; j < num; j++) {
			cards->RemoveLast();
		}
		return true;
	}

    return false;
}

bool Player::GetTingOrZimoOperationID(int& operation_id, PlayCardMsgProtocol* proto) const {
    int cards[CardConstants::ONE_PLAYER_CARD_NUM2] = { 0 };
    auto len = 0;
    this->GetInvisibleHandCards(cards, len);
    if (len > CardConstants::ONE_PLAYER_CARD_NUM2) {
        // TODO : error log
        return false;
    }

    if (ChessCard::IsHu(cards, len)) {
        operation_id = PlayCardOperationIDs::OPERATION_ZI_MO;
        return true;
    } else {
        if (proto->ting_cards_size() > 0) {
            proto->mutable_ting_cards(0)->Clear();
            if (ChessCard::IsTing(cards, len, proto->mutable_ting_cards(0))) {
                operation_id = PlayCardOperationIDs::OPERATION_TING;
                return true;
            }
        } else if (ChessCard::IsTing(cards, len, proto->add_ting_cards())) {
            operation_id = PlayCardOperationIDs::OPERATION_TING;
            return true;
        }
    }

    return false;
}

} // namespace gamer