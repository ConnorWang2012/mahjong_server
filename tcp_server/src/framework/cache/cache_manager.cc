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

#ifdef _WIN32
#include <WinSock2.h>
#endif

#include "framework/util/algorithm.h"

namespace gamer {

void gamer::CacheManager::Init() {
#ifdef _WIN32
	WSADATA wsadata;
	WSAStartup(0x0201, &wsadata);
#endif

	if ( !redis_client_.is_connected() ) {
		redis_client_.connect();
	}
}

void CacheManager::GetCachedData(const std::string& key, std::string& value) {
    redis_client_.get(key, [&](cpp_redis::reply& reply) {
        if (reply.is_string()) {
            value = reply.as_string();
        }
    });
    redis_client_.sync_commit();
}

void CacheManager::CacheData(const std::string& key, const std::string& value) {
    redis_client_.set(key, value);
    redis_client_.sync_commit();
}

int CacheManager::GeneratePlayerID() {
	++available_player_id_;
	redis_client_.set("player.id:available", std::to_string(available_player_id_));
	redis_client_.sync_commit();
	return available_player_id_;
}

void CacheManager::UpdateAvailablePlayerID() {
	redis_client_.get("player.id:available", [&](cpp_redis::reply& reply) {
		if (reply.is_integer()) {
			available_player_id_ = reply.as_integer();
		}
	});
	redis_client_.sync_commit();
}

inline cpp_redis::redis_client& CacheManager::redis_client() {
	return redis_client_;
}

}