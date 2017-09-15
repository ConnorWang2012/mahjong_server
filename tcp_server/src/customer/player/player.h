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

#include "customer/msg/protocol/player_cards_msg_protocol.pb.h"
#include "customer/msg/protocol/ting_card_msg_protocol.pb.h"
#include "player_protocol.h"

namespace gamer {

class Player : public PlayerProtocol {
  public:
    typedef gamer::protocol::PlayerCardsMsgProtocol PlayerCardsMsgProtocol;
    typedef gamer::protocol::TingCardMsgProtocol TingCardMsgProtocol;
    typedef google::protobuf::RepeatedField<google::protobuf::int32> RepeatedFieldInt;

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

    inline void set_has_selected_operation_ting(bool selected);

    inline bool has_selected_operation_ting() const;

	void CopyHandCardsFrom(const PlayerCardsMsgProtocol& from);

    void CopyInvisibleHandCardsTo(RepeatedFieldInt& to);

	bool InvisibleHandCardsContains(int card) const;

	void UpdateCardForDiscard(int discard);

    bool UpdateCardForChi(int card_of_chi, int card_match_chi_1, int card_match_chi_2);

    void UpdateCardForPeng(int card_of_peng);

    void UpdateCardForPengAndGang(int card_of_peng_gang);

    void UpdateCardForMingGang(int card_of_ming_gang);

    void UpdateCardForAnGang(int card_of_an_gang);

    void UpdateInvisibleHandCard(int new_card);

    // must be invoked after update invisible cards
    int GetAvailableOperationID(int new_card, TingCardMsgProtocol* proto) const;

    int CountInvisibleHandCards(int invisible_card) const;

    bool IsTing(TingCardMsgProtocol* proto) const;

    bool IsTing() const;

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

    bool GetTingOrZimoOperationID(int& operation_id, TingCardMsgProtocol* proto) const;

    bool is_online_;
    bool has_selected_operation_ting_;
	int player_id_;
    int cur_available_operation_id_;
	PlayerCardsMsgProtocol cards_msg_proto_;
};

inline void Player::set_cur_available_operation_id(int operation_id) {
    cur_available_operation_id_ = operation_id;
}

inline int Player::cur_available_operation_id() const {
    return cur_available_operation_id_;
}

inline void Player::set_has_selected_operation_ting(bool selected) {
    has_selected_operation_ting_ = selected;
}

inline bool Player::has_selected_operation_ting() const {
    return has_selected_operation_ting_;
}

} // namespace gamer

#endif // CONNOR_GAME_SRC_PLAYER_H_