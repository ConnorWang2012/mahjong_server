/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    player.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-14
@ description:  player.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_PLAYER_H_
#define CONNOR_GAME_SRC_PLAYER_H_

#include "msg/protocol/player_msg_protocol.pb.h"
#include "player_protocol.h"

namespace gamer {

class Player : public PlayerProtocol {
  public:
	Player& operator=(const Player&) = delete;

	Player(const Player&) = delete;

	Player();

	static Player* Create();

	virtual void set_player_id(int player_id) override;

	virtual int player_id() const override;

	virtual void set_is_online(bool online) override;

    virtual bool is_online() const override;

  private:
    bool is_online_;
	int player_id_;
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_PLAYER_H_