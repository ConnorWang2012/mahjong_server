/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    network_event_id.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-02-01
@ description:  network event id.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_NETWORK_EVENT_ID_H_
#define CONNOR_GAME_SRC_NETWORK_EVENT_ID_H_

namespace gamer {

enum class NetworkEventIDs {
	NETWORK_EVENT_ID_SOCKET_CONNECTED				= 1001,
	NETWORK_EVENT_ID_SOCKET_DISCONNECTED			= 1002,
	NETWORK_EVENT_ID_SOCKET_CONNECT_TIMEOUT			= 1003
};

}

#endif // CONNOR_GAME_SRC_NETWORK_EVENT_ID_H_