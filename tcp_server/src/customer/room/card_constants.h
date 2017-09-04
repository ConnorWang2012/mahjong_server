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
    ONE_PLAYER_CARD_NUM2          = 14,  // one player card num, including one new card

    INVALID_PLAYER_ID   = 0,

    // card index
    INVALID_CARD_VALUE  = -1,
    BAMBOO_1            = 0,  // bamboo
    BAMBOO_2            = 1,  
    BAMBOO_3            = 2,
    BAMBOO_4            = 3,
    BAMBOO_5            = 4,
    BAMBOO_6            = 5,
    BAMBOO_7            = 6,
    BAMBOO_8            = 7,
    BAMBOO_9            = 8,
    CHARACTER_1         = 9,  // character
    CHARACTER_2         = 10,
    CHARACTER_3         = 11,
    CHARACTER_4         = 12,
    CHARACTER_5         = 13,
    CHARACTER_6         = 14,
    CHARACTER_7         = 15,
    CHARACTER_8         = 16,
    CHARACTER_9         = 17,
    DOT_1               = 18,  // dot
    DOT_2               = 19,
    DOT_3               = 20,
    DOT_4               = 21,
    DOT_5               = 22,
    DOT_6               = 23,
    DOT_7               = 24,
    DOT_8               = 25,
    DOT_9               = 26,
    WIND_EAST           = 27,   // east, south, west, north, dragon green, dragon red, dragon white
    WIND_SOUTH          = 28, 
    WIND_WEST           = 29, 
    WIND_NORTH          = 30, 
    DRAGON_GREEN        = 31, 
    DRAGON_RED          = 32, 
    DRAGON_WHITE        = 33,
    SEASON_SPRING       = 34,  // spring, summer, autumn, winter, plum, orchid, chrysanthemum, bamboo
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
    OPERATION_DISCARD,
    OPERATION_NONE,			        // just a new card, no operation(only server to client)
    OPERATION_CHI,			        // chi
    OPERATION_PENG,			        // peng
    OPERATION_CHI_OR_PENG,	        // chi or peng(only server to client)
    OPERATION_CHI_OR_PENG_OR_GANG,	// chi or peng or gang(only server to client)
    OPERATION_PENG_GANG,	        // peng + gang
    OPERATION_MING_GANG,	        // ming gang
    OPERATION_AN_GANG,		        // an gang
    OPERATION_BU_HUA,		        // bu hua
    OPERATION_HU,			        // hu
    OPERATION_ZI_MO,	            // zi mo
    OPERATION_GIVE_UP		        // give up
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_CARD_CONSTANTS_H_