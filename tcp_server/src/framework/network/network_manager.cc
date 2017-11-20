/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	   network_manager.cc
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

#include "network_manager.h"

#ifdef _WIN32
#include <WinSock2.h>
#elif defined(__linux__)
#include <arpa/inet.h>
#include <netinet/in.h>
#elif defined(__unix__)
#include <sys/socket.h>
#endif

#include <memory.h>

#include "event2/buffer.h"
#include "event2/bufferevent.h"
#include "event2/event.h"
#include "event2/listener.h"

#include "framework/base/msg.h"
#include "framework/cache/cache_proxy.h"
#include "framework/log/mylog.h"
#include "framework/event/event_manager.h"
#include "framework/network/network_event_id.h"

#include "msg/msg_manager.h"

namespace gamer {

NetworkManager::NetworkManager() : NetworkManager("127.0.0.1", 4994) {
}

NetworkManager::NetworkManager(const std::string& ip, int port)
	: ip_(ip),
	  port_(port),
	  evbase_(nullptr),
	  connlistener_(nullptr) {
}

void NetworkManager::InitSocket() {
    this->InitIPAndPort();

	struct sockaddr_in sin;

#ifdef _WIN32
	WSADATA wsadata;
	WSAStartup(0x0201, &wsadata);
#endif
	
    CacheProxy::instance()->Init(); // TODO : do it in somewhere

	if (nullptr == evbase_) {
		evbase_ = event_base_new();
	}
	if (nullptr == evbase_) {
		LOGERROR("[NetworkManager::InitSocket] event_base_new failed!");
		return;
	}

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(ip_.c_str());
	//sin.sin_addr.s_addr = htonl(0);
	sin.sin_port = htons(port_);

	if (nullptr == connlistener_) {
		connlistener_ = evconnlistener_new_bind(evbase_,
			(evconnlistener_cb)OnConnAccepted,
			nullptr,
			LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE,
			-1,
			(struct sockaddr*)&sin,
			sizeof(sin));
	}
	if (nullptr == connlistener_) {
		LOGERROR("[NetworkManager::InitSocket] evconnlistener_new_bind failed!");
		return;
	}

	LOGGREEN("[NetworkManager::InitSocket] tcp listening on : %s, port : %d", ip_.c_str(), port_);

	evconnlistener_set_error_cb(connlistener_, OnConnErrorOccur);

	event_base_dispatch(evbase_);
}

bool NetworkManager::Send(struct bufferevent* bev, void* ctx, size_t ctxlen) {
	if (nullptr == ctx) {
		printf("[NetworkManager::send] context invalid");
		return false;
	}

	if (ctxlen > NetworkManager::MAX_BUFFER_LEN) {
		printf("[NetworkManager::send] context len invalid");
		return false;
	}

	if (bev) {
		auto ret = bufferevent_write(bev, ctx, ctxlen);
		if (0 == ret) {
			return true;
		}
	}

	return false;
}

void NetworkManager::OnConnAccepted(struct evconnlistener* listener, 
								    evutil_socket_t fd,
                                    struct socketaddr* address,
								    int socklen,
                                    void* ctx) {
	// We got a new connection! Set up a bufferevent for it.
	LOGGREEN("[NetworkManager::InitSocket] one client connected");	
	auto base = evconnlistener_get_base(listener);
	auto bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	bufferevent_setcb(bev, OnBuffereventRead, OnBuffereventWrite, OnBuffereventReceived, nullptr);
	bufferevent_enable(bev, EV_READ | EV_WRITE);
}

void NetworkManager::OnConnErrorOccur(struct evconnlistener* listener, void* ctx) {
	auto base = evconnlistener_get_base(listener);
	int err = EVUTIL_SOCKET_ERROR();
	//fprintf(stderr, "Got an error %d (%s) on the listener. "
	//	"Shutting down.", err, evutil_socket_error_to_string(err));
	event_base_loopexit(base, nullptr);
}

void NetworkManager::OnBuffereventReceived(struct bufferevent* bev, short event, void* ctx) {
	if (event & BEV_EVENT_ERROR) {
		LOGERROR("[NetworkManager::OnBuffereventArrive] error from bufferevent!");
		EventManager::instance()->Dispatch((id_t)NetworkEventIDs::NETWORK_EVENT_ID_SOCKET_DISCONNECTED);
	}

	if (event & (BEV_EVENT_EOF | BEV_EVENT_ERROR)) {
		bufferevent_free(bev);
	}

	if (event & BEV_EVENT_CONNECTED) {
		LOGGREEN("[NetworkManager::OnBuffereventArrive] client connected");
		EventManager::instance()->Dispatch((id_t)NetworkEventIDs::NETWORK_EVENT_ID_SOCKET_CONNECTED);
	} 
	
	if (event & BEV_EVENT_TIMEOUT) {
		LOGERROR("[NetworkManager::OnBuffereventArrive] client connect timeout");
		EventManager::instance()->Dispatch((id_t)NetworkEventIDs::NETWORK_EVENT_ID_SOCKET_CONNECT_TIMEOUT);
	}
}

void NetworkManager::OnBuffereventRead(struct bufferevent* bev, void* ctx) {
    // This callback is invoked when there is data to read on bev.
    auto input = bufferevent_get_input(bev);

    auto buf_len = evbuffer_get_length(input);
    if (buf_len <= 0 || buf_len > NetworkManager::MAX_BUFFER_LEN) {
        LOGERROR("[NetworkManager::onBufferRead] buffer len is invalid");
        return;
    }

    char buf[NetworkManager::MAX_BUFFER_LEN] = { 0 };
    if (evbuffer_remove(input, buf, buf_len) <= 0) {
        LOGERROR("[NetworkManager::onBufferRead] read buffer failed");
        return;
    }

    unsigned parsed_buf_len = 0;
    do {
        gamer::ClientMsg msg = { 0, 0, 0, nullptr };
        NetworkManager::instance()->ParseBuffer(buf, msg);
        MsgManager::instance()->OnMsgReceived(msg, bev);
        parsed_buf_len += msg.total_len;
    } while (parsed_buf_len < buf_len);
}

void NetworkManager::OnBuffereventWrite(struct bufferevent* bev, void* ctx) {
	//printf("client read_cb");
	//char msg[] = "client msg";
	//bufferevent_write(bev, msg, sizeof(msg));
}

void NetworkManager::InitIPAndPort() {
	// TODO : init from cfg
	ip_ = "127.0.0.1";
    //ip_ = "192.168.1.101";
	port_ = 4994;
}

void NetworkManager::ParseBuffer(char* buf, gamer::ClientMsg& msg) {
    memcpy(&msg.total_len, buf, sizeof(msg_header_t));
    memcpy(&msg.type, buf + sizeof(msg_header_t), sizeof(msg_header_t));
    memcpy(&msg.id, buf + sizeof(msg_header_t) * 2, sizeof(msg_header_t));
    if (msg.total_len > gamer::client_msg_header_len()) {
        msg.context = buf + gamer::client_msg_header_len();
    }
}

} // namespace gamer