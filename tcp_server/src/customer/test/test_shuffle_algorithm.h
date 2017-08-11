/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    test_shuffle_algorithm.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-01
@ description:  test shuffle algorithm.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_TEST_SHUFFLE_ALGORITHM_H_
#define CONNOR_GAME_SRC_TEST_SHUFFLE_ALGORITHM_H_

#include "framework/util/chess_card_algorithm.h"

namespace gamer {

void test_shuffle_algorithm() {
    std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    gamer::ChessCard::Shuffle(vec);
    for (auto& x : vec) {
        printf("shuffle : %d\n", x);
    }
}

void test_is_hu_algorithm() {
    int hai[14] = { 1, 1, 1, 2, 3, 4, 27, 27, 27, 29, 29 };
    auto ret = gamer::ChessCard::IsHu(hai, 11);
    if (ret) {
        printf("is_hu : true");
    } else {
        printf("is_hu : false");
    }
}

}

#endif // CONNOR_GAME_SRC_TEST_SHUFFLE_ALGORITHM_H_
