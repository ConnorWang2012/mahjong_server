﻿/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    cache_proxy.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-20
@ description:  cache proxy.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_FRAMEWORK_CACHE_PROXY_H_
#define CONNOR_GAME_SRC_FRAMEWORK_CACHE_PROXY_H_

#include "base/basic_manager.h"
#include "cpp_redis/redis_client.hpp"

namespace gamer {

class CacheProxy : public BasicManager<CacheProxy> {
  public:
	void Init();

	inline cpp_redis::redis_client* redis_client() { return &redis_client_; }

  private:
	cpp_redis::redis_client redis_client_; // use sync_commit
};

}

#endif // CONNOR_GAME_SRC_FRAMEWORK_CACHE_PROXY_H_