/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	   log.cc
@ author:	   Connor
@ version:	   1.0.0
@ date:		   2017-05-01
@ description: log.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#include "mylog.h"

#include <chrono>
#include <iostream>
#include <iomanip>

#ifdef _WIN32
#include <direct.h> 
#include <io.h> 
#include <windows.h>
#endif

namespace gamer {

namespace log {
	
void init() {
	auto now = std::chrono::system_clock::now();
	auto curtime = std::chrono::system_clock::to_time_t(now);
	auto tm = std::localtime(&curtime);
	auto y = tm->tm_year + 1900;
	auto m = tm->tm_mon + 1;
	auto d = tm->tm_mday;
	char buf[20];
	snprintf(buf, sizeof(buf), "log/%d-%d-%d", y, m, d);

#ifdef _WIN32
	if (_access(buf, 0) < 0) {
		_mkdir(buf);
	}
#else
	// TODO : other platform
#endif
	
	s_log_path_ = std::string(buf) + "/mylog.dat";
}

void writelog(const char* format, ...) {
	if ( !s_ofs_log_.is_open() ) {
		s_ofs_log_.open(s_log_path_.c_str(),
			std::ofstream::out | std::ofstream::binary | std::ofstream::app);
	}
	
	// time
	auto now = std::chrono::system_clock::now();
	auto curtime = std::chrono::system_clock::to_time_t(now);
	auto tm = std::localtime(&curtime);
	auto time = std::put_time(tm, "%Y-%m-%d %H:%M:%S");

	// context
	va_list args;
	va_start(args, format);
	char buf[256];
	vsnprintf(buf, sizeof(buf), format, args);
	s_ofs_log_ << time << " " << buf << "\n";
	va_end(args);

	s_ofs_log_.close();
}

void printf(const char* s) {
	while (*s) {
		if (*s == '%' && *(++s) != '%')
			throw std::runtime_error("invalid format string: missing arguments");
		std::cout << *s++;
	}
}

void printfcolor(Colors c, const char* format, ...) {
	va_list args;
	va_start(args, format);
	char buf[256];
	vsnprintf(buf, sizeof(buf), format, args);
#ifdef _WIN32
	auto h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | (int)c);
	std::cout << buf << std::endl;
	SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | (int)Colors::COLOR_WHITE);
#else
	// TODO : other platform
	std::cout << buf << std::endl;
#endif
	va_end(args);
}

void printfgreen(const char* format, ...) {
	va_list args;
	va_start(args, format);
	char buf[256];
	vsnprintf(buf, sizeof(buf), format, args);
#ifdef _WIN32
	auto h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | (int)log::Colors::COLOR_GREEN);
	std::cout << buf << std::endl;
	SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | (int)log::Colors::COLOR_WHITE);
#else
	// TODO : other platform
	std::cout << buf << std::endl;
#endif
	va_end(args);
}

void printfwarning(const char* format, ...) {
	va_list args;
	va_start(args, format);
	char buf[256];
	vsnprintf(buf, sizeof(buf), format, args);
#ifdef _WIN32
	auto h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | (int)log::Colors::COLOR_YELLOW);
	std::cout << buf << std::endl;
	SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | (int)log::Colors::COLOR_WHITE);
#else
	// TODO : other platform
	std::cout << buf << std::endl;
#endif
	va_end(args);
}

void printferror(const char* format, ...) {
	va_list args;
	va_start(args, format);
	char buf[256];
	vsnprintf(buf, sizeof(buf), format, args);
#ifdef _WIN32
	auto h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | (int)log::Colors::COLOR_RED);
	std::cout << buf << std::endl;
	SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | (int)log::Colors::COLOR_WHITE);
#else
	// TODO : other platform
	std::cout << buf << std::endl;
#endif
	va_end(args);
}

} // namespace log

} // namespace gamer