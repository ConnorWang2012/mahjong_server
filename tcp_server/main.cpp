/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	   main.cpp
@ author:	   Connor
@ version:	   1.0.0
@ date:		   2017-05-01
@ description:
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#include "framework/service/runtime/server.h"

int main(int argc, char* argv[]) {
	gamer::Server::instance()->Start();
	return 0;
}