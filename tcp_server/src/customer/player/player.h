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

#include "player_protocol.h"
#include "msg/protocol/player_cards_msg_protocol.pb.h"

namespace gamer {

class Player : public PlayerProtocol {
  public:
	Player& operator=(const Player&) = delete;

	Player(const Player&) = delete;

	Player();

	static Player* Create(int player_id);

	virtual inline void set_player_id(int player_id) override;

	virtual inline int player_id() const override;

	virtual inline void set_is_online(bool online) override;

    virtual inline bool is_online() const override;

	void SetHandCards(const protocol::PlayerCardsMsgProtocol& from);

	bool InvisibleHandCardsContains(int card) const;

	void UpdateCardForDiscard(int discard);

    void UpdateInvisibleHandCard(int new_card);

    void GetInvisibleHandCards(int* cards, int& len) const;

    int GetAvailableOperationID(int new_card) const;

  private:
	bool Init(int player_id);

    bool is_online_;
	int player_id_;
	protocol::PlayerCardsMsgProtocol cards_msg_proto_;
	int new_invisible_hand_card_index_;
    int tag_;
};

} // namespace gamer

#endif // CONNOR_GAME_SRC_PLAYER_H_