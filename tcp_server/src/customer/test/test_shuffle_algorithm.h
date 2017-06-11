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

#include "customer/util/algorithm.h"

namespace gamer {

void test_shuffle_algorithm() {
    std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    gamer::Shuffle(vec);
    for (auto& x : vec) {
        printf("shuffle : %d\n", x);
    }
}

}

#endif // CONNOR_GAME_SRC_TEST_SHUFFLE_ALGORITHM_H_
