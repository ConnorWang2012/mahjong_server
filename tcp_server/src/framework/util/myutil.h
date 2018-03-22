/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    myutil.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-01
@ description:  myutil
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_FRAMEWORK_MYUTIL_H_
#define CONNOR_GAME_SRC_FRAMEWORK_MYUTIL_H_

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

// use for deleting std::vector object in std::for_each.
struct delete_vector_obj {
	template <typename T>
	void operator() (const T* ptr) const {
		SAFE_DELETE(ptr);
	}
};

// use for deleting std::map object in std::for_each.
struct delete_map_obj {
	template <typename T1, typename T2>
	void operator() (const T1, const T2* ptr) const {
		SAFE_DELETE(ptr);
	}
};

template<typename T>
static T GenerateRandom(T min, T max) {
    std::uniform_int_distribution<T> distribution(min, max);
	std::random_device rd;
    std::mt19937 engine(rd());
    auto generator = std::bind(distribution, engine);
    return generator();
}

// E:\a\b\abc.txt --> E:/a/b/abc.txt
static std::string ConvertPathFormatToUnixStyle(const std::string& path) {
	if (!path.empty()) {
		std::string ret = path;
		int len = ret.length();
		for (int i = 0; i < len; ++i)
		{
			if (ret[i] == '\\')
			{
				ret[i] = '/';
			}
		}
		return ret;
	}

	return std::string();
}

static std::string GetPathOfApp() {
#if defined(_WIN32)
	/*
	char fullpath[MAX_PATH];
	auto total_len = GetModuleFileNameA(NULL, fullpath, MAX_PATH);

	std::string s = fullpath;
	auto i = s.find_last_of("\\");
	return s.substr(0, i);
	*/
	WCHAR utf16_path[MAX_PATH] = { 0 };
	GetModuleFileNameW(NULL, utf16_path, MAX_PATH - 1);
	WCHAR* utf16_exe_path = &(utf16_path[0]);

	WCHAR* utf16_dir_end = wcsrchr(utf16_exe_path, L'\\');

	char utf8_exe_dir[MAX_PATH] = { 0 };
	WideCharToMultiByte(CP_UTF8, 0, utf16_exe_path, utf16_dir_end - utf16_exe_path + 1, 
		utf8_exe_dir, sizeof(utf8_exe_dir), nullptr, nullptr);

	return gamer::ConvertPathFormatToUnixStyle(utf8_exe_dir);
#elif defined(__linux__)
	char fullpath[MAX_PATH] = { 0 };
	ssize_t length = readlink("/proc/self/exe", fullpath, sizeof(fullpath) - 1);

	if (length <= 0) {
		return std::string();
	}

	fullpath[length] = '\0';
	return fullpath;
#elif defined(__unix__)
	// TODO :
#endif
	return "";
}

} // namespace gamer

#endif // CONNOR_GAME_SRC_FRAMEWORK_MYUTIL_H_