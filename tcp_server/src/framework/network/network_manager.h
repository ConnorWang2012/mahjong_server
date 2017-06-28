/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	   network_manager.h
@ author:	   Connor
@ version:	   1.0.0
@ date:		   2017-04-01
@ description: network manager.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_FRAMEWORK_NETWORK_MANAGER_H_
#define CONNOR_GAME_SRC_FRAMEWORK_NETWORK_MANAGER_H_

#include <string>

#include "event2/util.h"

#include "base/basic_manager.h"
#include "base/macros.h"

struct bufferevent;
struct event_base;
struct evconnlistener;

namespace gamer {

struct ClientMsg;

class NetworkManager : public BasicManager<NetworkManager> {
  public:
	NetworkManager();

	//NetworkManager& operator=(const NetworkManager&) = delete;

	//NetworkManager(const NetworkManager&) = delete;

	//void *operator new(std::size_t) = delete;

	//static NetworkManager* instance();

	void InitSocket();

    bool Send(struct bufferevent* bev, void* ctx, size_t ctxlen);

  private:
	NetworkManager(const std::string& ip, int port);

	static void OnConnAccepted(struct evconnlistener* listener, 
		                     evutil_socket_t fd,
	                         struct socketaddr* addr, 
							 int socklen, 
							 void* ctx);

	static void OnConnErrorOccur(struct evconnlistener* listener, void* ctx);

	static void OnBuffereventReceived(struct bufferevent* bev, short event, void* ctx);

	static void OnBuffereventRead(struct bufferevent* bev, void* ctx);

	static void OnBuffereventWrite(struct bufferevent* bev, void* ctx);

	void InitIPAndPort();

    void ParseBuffer(char* buf, gamer::ClientMsg& msg);

	struct event_base* evbase_;
	struct evconnlistener* connlistener_;

	std::string ip_;
	int port_;

    static const int MAX_BUFFER_LEN = 4096;
}; // namespace gamer

} // namespace gamer

#endif // CONNOR_GAME_SRC_FRAMEWORK_NETWORK_MANAGER_H_
