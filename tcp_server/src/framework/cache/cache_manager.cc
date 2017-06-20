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

#include "cache_manager.h"

namespace gamer {

void gamer::CacheManager::Init() {
	if ( !redis_client_.is_connected() ) {
		redis_client_.connect();
	}
}

inline cpp_redis::redis_client& CacheManager::redis_client() {
	return redis_client_;
}


}