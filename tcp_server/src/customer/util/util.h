/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    util.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-28
@ description:  util.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_CUSTOMER_UTIL_H_
#define CONNOR_GAME_SRC_CUSTOMER_UTIL_H_

#include "room/card_constants.h"

namespace gamer {

// TODO : not right
static CardTypes GetCardType(int card) {
	if (card >= CardConstants::CARD_VALUE_BAMBOO_1 && 
		card <= CardConstants::CARD_VALUE_BAMBOO_9) {
		return CardTypes::CARD_TYPE_BAMBOO;
	} else if (card >= CardConstants::CARD_VALUE_CHARACTER_1 && 
		       card <= CardConstants::CARD_VALUE_CHARACTER_9) {
		return CardTypes::CARD_TYPE_CHARACTER;
	} else if (card >= CardConstants::CARD_VALUE_DOT_1 &&
		       card <= CardConstants::CARD_VALUE_DOT_9) {
		return CardTypes::CARD_TYPE_DOT;
	} else if (card >= CardConstants::CARD_VALUE_WIND_OR_DRAGON_1 &&
		       card <= CardConstants::CARD_VALUE_WIND_OR_DRAGON_4) {
		return CardTypes::CARD_TYPE_WIND;
	} else if (card > CardConstants::CARD_VALUE_WIND_OR_DRAGON_4 &&
		       card <= CardConstants::CARD_VALUE_WIND_OR_DRAGON_7) {
		return CardTypes::CARD_TYPE_DRAGON;
	} else if (card >= CardConstants::CARD_VALUE_SEASON_OR_FLOWER_1 &&
		       card <= CardConstants::CARD_VALUE_SEASON_OR_FLOWER_4) {
		return CardTypes::CARD_TYPE_SEASON;
	} else if (card > CardConstants::CARD_VALUE_SEASON_OR_FLOWER_4 &&
		       card <= CardConstants::CARD_VALUE_SEASON_OR_FLOWER_8) {
		return CardTypes::CARD_TYPE_FLOWER;
	}
	return CardTypes::CARD_TYPE_UNKNOW;
}

} // namespace gamer

#endif // CONNOR_GAME_SRC_CUSTOMER_UTIL_H_