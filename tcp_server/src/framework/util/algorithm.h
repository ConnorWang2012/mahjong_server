/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    algorithm.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-01
@ description:  algorithm
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_FRAMEWORK_ALGORITHM_H_
#define CONNOR_GAME_SRC_FRAMEWORK_ALGORITHM_H_

#include <vector>

#include "framework/util/util.h"

namespace gamer {

static void Shuffle(std::vector<int>& cards) {
    auto n = (int)cards.size();
    for (auto i = 0; i < n; i++) {
        int j = gamer::GenerateRandom<int>(0, i); 
        std::swap(cards[i], cards[j]);
    }
}

}

#endif // CONNOR_GAME_SRC_FRAMEWORK_ALGORITHM_H_