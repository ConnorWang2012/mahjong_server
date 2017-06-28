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
#include "room/card_constants.h"

namespace gamer {

Player::Player()
	:player_id_(0)
	,is_online_(false)
	,new_invisible_hand_card_index_(-1){
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

void Player::CopyHandCards(const protocol::PlayerCardsMsgProtocol& from) {
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

//void Player::UpdateHandCardWhenDiscarded(int card) {
//	// invisible hand cards
//	auto card_type = gamer::GetCardType(card);
//	if (CardTypes::CARD_TYPE_SEASON == card_type) {
//		cards_msg_proto_.add_season_cards(card);
//	} else if (CardTypes::CARD_TYPE_FLOWER == card_type) {
//		cards_msg_proto_.add_flower_cards(card);
//	}
//	auto card = cards_msg_proto_.invisible_hand_cards(new_invisible_hand_card_index_);
//	if (card <= 0) {
//
//	}
//}

void Player::ClearInvisibleHandCard(int card) {
	auto cards_size = cards_msg_proto_.invisible_hand_cards_size();
	for (auto i = 0; i < cards_size; i++) {
		if (cards_msg_proto_.invisible_hand_cards(i) == card) {
			cards_msg_proto_.set_visible_hand_cards(i, 0);
			new_invisible_hand_card_index_ = i;
		}
	}
}

bool Player::Init(int player_id) {
	player_id_ = player_id;
	return true;
}

}