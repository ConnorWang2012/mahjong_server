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
    INVALID_CARD_VALUE            = 50,

    // card value
    CARD_VALUE_BAMBOO_1           = 11,  // bamboo 1
    CARD_VALUE_BAMBOO_9           = 19,  // bamboo 9
    CARD_VALUE_CHARACTER_1        = 21,  // character 1
    CARD_VALUE_CHARACTER_9        = 29,  // character 9
    CARD_VALUE_DOT_1              = 31,  // dot 1
    CARD_VALUE_DOT_9              = 39,  // dot 9
    CARD_VALUE_WIND_OR_DRAGON_1   = 41,  // east, south, west, north, dragon green, dragon red, dragon white
    CARD_VALUE_WIND_OR_DRAGON_4   = 44,
    CARD_VALUE_WIND_OR_DRAGON_7   = 47,  
    CARD_VALUE_SEASON_OR_FLOWER_1 = 51,  // season : spring, summer, autumn, winter, flower : plum, orchid, chrysanthemum, bamboo
    CARD_VALUE_SEASON_OR_FLOWER_4 = 54,
    CARD_VALUE_SEASON_OR_FLOWER_8 = 58, 

    // card index
    BAMBOO_1            = 0,
    BAMBOO_2            = 1,
    BAMBOO_3            = 2,
    BAMBOO_4            = 3,
    BAMBOO_5            = 4,
    BAMBOO_6            = 5,
    BAMBOO_7            = 6,
    BAMBOO_8            = 7,
    BAMBOO_9            = 8,
    CHARACTER_1         = 9,
    CHARACTER_2         = 10,
    CHARACTER_3         = 11,
    CHARACTER_4         = 12,
    CHARACTER_5         = 13,
    CHARACTER_6         = 14,
    CHARACTER_7         = 15,
    CHARACTER_8         = 16,
    CHARACTER_9         = 17,
    DOT_1               = 18,
    DOT_2               = 19,
    DOT_3               = 20,
    DOT_4               = 21,
    DOT_5               = 22,
    DOT_6               = 23,
    DOT_7               = 24,
    DOT_8               = 25,
    DOT_9               = 26,
    WIND_EAST           = 27, 
    WIND_SOUTH          = 28, 
    WIND_WEST           = 29, 
    WIND_NORTH          = 30, 
    DRAGON_GREEN        = 31, 
    DRAGON_RED          = 32, 
    DRAGON_WHITE        = 33,
    SEASON_SPRING       = 34,
    SEASON_SUMMER       = 35,
    SEASON_AUTUMN       = 36,
    SEASON_WINTER       = 37,
    FLOWER_PLUM         = 38,
    FLOWER_ORCHID       = 39,
    FLOWER_CHRYSANTHEMUM = 40,
    FLOWER_BAMBOO       = 41,
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

enum PlayCardOperationIDs {
    DISCARD,
    NEW_CARD,			    // just a new card
    MELD_CARD_GIVE_UP,		// give up
    MELD_CARD_CHI,			// chi
    MELD_CARD_PENG,			// peng
    MELD_CARD_PENG_GANG,	// peng + gang
    MELD_CARD_GANG,			// ming gang
    MELD_CARD_AN_GANG,		// an gang
    MELD_CARD_BU_HUA,		// bu hua
    MELD_CARD_HU,			// hu
    MELD_CARD_ZI_MO,		// zi mo
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_CARD_CONSTANTS_H_