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

    inline void set_cur_available_operation_id(int operation_id);

    inline int cur_available_operation_id() const;

	void SetHandCards(const protocol::PlayerCardsMsgProtocol& from);

	bool InvisibleHandCardsContains(int card) const;

	void UpdateCardForDiscard(int discard);

    bool UpdateCardForChi(int card_of_chi, int card_match_chi_1, int card_match_chi_2);

    void UpdateCardForPeng(int card_of_peng);

    void UpdateCardForPengAndGang(int card_of_peng_gang);

    void UpdateCardForMingGang(int card_of_ming_gang);

    void UpdateCardForAnGang(int card_of_an_gang);

    void UpdateInvisibleHandCard(int new_card);

    // must invoke after update invisible cards
    int GetAvailableOperationID(int card) const;

    int CountInvisibleHandCards(int invisible_card) const;

    bool IsHu(int card) const;

    bool IsZimo() const;

    bool IsChi(int card) const;

    bool IsChi(int card, int* cards_chi, int& cards_chi_len) const;

    bool IsPeng(int card) const;

    bool IsPengAndGang(int card) const;

    bool IsMingGang(int card) const;

    bool IsAnGang(int card) const;

    bool IsBuhua(int card) const;

  private:
	bool Init(int player_id);

    void GetInvisibleHandCards(int* cards, int& len) const;

    bool PengCardsContains(int card) const;

    bool RemoveInvisibleHandCards(int card, int num);

    bool is_online_;
	int player_id_;
    int cur_available_operation_id_;
	protocol::PlayerCardsMsgProtocol cards_msg_proto_;
};

inline void Player::set_cur_available_operation_id(int operation_id) {
    cur_available_operation_id_ = operation_id;
}

inline int Player::cur_available_operation_id() const {
    return cur_available_operation_id_;
}

} // namespace gamer

#endif // CONNOR_GAME_SRC_PLAYER_H_