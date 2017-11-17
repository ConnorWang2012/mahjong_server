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
#include <string>

#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#elif defined(__unix__)
#endif

namespace gamer {

template<typename T>
static T GenerateRandom(T min, T max) {
    std::uniform_int_distribution<T> distribution(min, max);
	std::random_device rd;
    std::mt19937 engine(rd());
    auto generator = std::bind(distribution, engine);
    return generator();
}

static std::string GetPathOfExecutable() {
#if defined(_WIN32)
	char fullpath[MAX_PATH];
	auto total_len = GetModuleFileNameA(NULL, fullpath, MAX_PATH);

	std::string s = fullpath;
	auto i = s.find_last_of("\\");
	return s.substr(0, i);
#elif defined(__linux__)
#elif defined(__unix__)
#endif
	return "";
}

} // namespace gamer

#endif // CONNOR_GAME_SRC_FRAMEWORK_UTIL_H_