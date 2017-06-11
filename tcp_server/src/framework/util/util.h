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

#ifndef CONNOR_GAME_SRC_UTIL_H_
#define CONNOR_GAME_SRC_UTIL_H_

#include <functional>
#include <random>
#include <vector>

namespace gamer {

// TODO : use template template<typename Min, typename Max>
static int GenerateRandom(int min, int max) {
    std::uniform_int_distribution<int> distribution(min, max);
    std::mt19937 engine;
    auto generator = std::bind(distribution, engine);
    return generator();
}

} // namespace gamer

#endif // CONNOR_GAME_SRC_UTIL_H_