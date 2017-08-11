/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    cache_manager.cc
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-20
@ description:  cache manager.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#include "cache_proxy.h"

#ifdef _WIN32
#include <WinSock2.h>
#endif

namespace gamer {

void gamer::CacheProxy::Init() {
#ifdef _WIN32
    WSADATA wsadata;
    WSAStartup(0x0201, &wsadata);
#endif

	if ( !redis_client_.is_connected() ) {
		redis_client_.connect();
	}
}

}