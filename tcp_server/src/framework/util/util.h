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

#ifndef CONNOR_GAME_SRC_FRAMEWORK_UTIL_H_
#define CONNOR_GAME_SRC_FRAMEWORK_UTIL_H_

#include <functional>
#include <random>
#include <vector>

namespace gamer {

template<typename T>
static T GenerateRandom(T min, T max) {
    std::uniform_int_distribution<T> distribution(min, max);
	std::random_device rd;
    std::mt19937 engine(rd());
    auto generator = std::bind(distribution, engine);
    return generator();
}

} // namespace gamer

#endif // CONNOR_GAME_SRC_FRAMEWORK_UTIL_H_