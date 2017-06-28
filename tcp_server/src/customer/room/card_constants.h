/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    card_constants.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-16
@ description:  card constants.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_CARD_CONSTANTS_H_
#define CONNOR_GAME_SRC_CARD_CONSTANTS_H_

namespace gamer {

enum CardConstants {
    TOTAL_CARDS_NUM               = 144, // total cards num
    ONE_PLAYER_CARD_NUM           = 13,  // one player card num
    CARD_VALUE_BAMBOO_1           = 11,  // bamboo 1
    CARD_VALUE_BAMBOO_9           = 19,  // bamboo 9
    CARD_VALUE_CHARACTER_1        = 21,  // character 1
    CARD_VALUE_CHARACTER_9        = 29,  // character 9
    CARD_VALUE_DOT_1              = 31,  // dot 1
    CARD_VALUE_DOT_9              = 39,  // dot 9
    CARD_VALUE_WIND_OR_DRAGON_1   = 41,  // east, south, west, north, dragon green, dragon red, dragon white
    CARD_VALUE_WIND_OR_DRAGON_4   = 44,
    CARD_VALUE_WIND_OR_DRAGON_7   = 47,  
    CARD_VALUE_SEASON_OR_FLOWER_1 = 51,  // season spring, summer, autumn, spring, flower plum, orchid, bamboo, chrysanthemum
    CARD_VALUE_SEASON_OR_FLOWER_4 = 54,
    CARD_VALUE_SEASON_OR_FLOWER_8 = 58, 
};

enum class CardTypes {
	CARD_TYPE_UNKNOW,
	CARD_TYPE_BAMBOO,
	CARD_TYPE_CHARACTER,
	CARD_TYPE_DOT,
	CARD_TYPE_WIND,
	CARD_TYPE_DRAGON,
	CARD_TYPE_SEASON,
	CARD_TYPE_FLOWER
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_CARD_CONSTANTS_H_