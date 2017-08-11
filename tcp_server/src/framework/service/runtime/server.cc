/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	   server.cc
@ author:	   Connor
@ version:	   1.0.0
@ date:		   2017-04-01
@ description: start and stop server.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#include "server.h"

#include "customer/msg/msg_manager.h"
#include "framework/base/log_headers.h"
#include "framework/network/network_manager.h"
//#include "framework/cache/cache_manager.h"

namespace gamer {

Server* Server::instance() {
	static Server s_server;
	return &s_server;
}

void Server::Start() {
    //CacheManager::instance()->Init(); // why here will crash
	gamer::log::init();
	WRITELOG("[Server::Start] server starting");
    MsgManager::instance()->Init();
	NetworkManager::instance()->InitSocket();
}

void Server::Stop() {
}

void Server::ServerDidFinishLaunching() {
}

void Server::ServerWillExit() {
}

} // namespace gamer