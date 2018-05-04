/*******************************************************************************
 @ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
 @ filename:	  typedef.h
 @ author:		  Connor
 @ version:	      1.0.0
 @ date:		  2018-04-23
 @ description:   define common base type.
 @ others:
 @ history:
 1.date:
 author:
 modification:
 ********************************************************************************/

#ifndef CONNOR_GAME_SRC_FRAMEWORK_TYPEDEF_H_
#define CONNOR_GAME_SRC_FRAMEWORK_TYPEDEF_H_

namespace gamer {

#if defined(_WIN32)
	typedef __int8                  int8;
	typedef __int16                 int16;
	typedef __int32                 int32;
	typedef __int64                 int64;

	typedef unsigned __int8         uint8;
	typedef unsigned __int16        uint16;
	typedef unsigned __int32        uint32;
	typedef unsigned __int64        uint64;
#elif defined(__linux__) 
	typedef signed char             int8;
	typedef short                   int16;
	typedef int                     int32;
	typedef long long               int64;
	typedef unsigned char           uint8;
	typedef unsigned short          uint16;
	typedef unsigned int            uint32;
	typedef unsigned long long      uint64;
#elif defined(__unix__)
	typedef int8_t                  int8;
	typedef int16_t                 int16;
	typedef int32_t                 int32;
	typedef int64_t                 int64;

	typedef uint8_t                 uint8;
	typedef uint16_t                uint16;
	typedef uint32_t                uint32;
	typedef uint64_t                uint64;
#endif

#ifdef _WIN64
	typedef __int64					intptr_t;
#else
	typedef int						intptr_t;
#endif

#ifdef _WIN32
#define socket_t					intptr_t
#else
#define socket_t					int
#endif

typedef	unsigned int				id_t;
typedef	unsigned int				msg_header_t;

} // namespace gamer

#endif // CONNOR_GAME_SRC_FRAMEWORK_TYPEDEF_H_
