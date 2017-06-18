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
    virtual bool is_online() const override;

    inline protocol::PlayerMsgProtocol* get_player_msg_protocol();

  private:
    bool is_online_;
    
    protocol::PlayerMsgProtocol play_msg_proto_;
};

bool Player::is_online() const {
    return is_online_;
}

gamer::protocol::PlayerMsgProtocol* Player::get_player_msg_protocol() {
    return &play_msg_proto_;
}

} // namespace gamer

#endif // CONNOR_GAME_SRC_PLAYER_H_