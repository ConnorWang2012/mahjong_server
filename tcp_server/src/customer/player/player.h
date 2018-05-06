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

#include "framework/base/macros.h"
#include "framework/base/typedef.h"
#include "customer/base/common_typedef.h"
#include "customer/player/player_protocol.h"
#include "customer/player/player_constants.h"
#include "customer/msg/protocol/player_cards_msg_protocol.pb.h"
#include "customer/msg/protocol/play_card_msg_protocol.pb.h"
#include "customer/msg/protocol/ting_card_msg_protocol.pb.h"

namespace gamer {

class Player : public PlayerProtocol {
  public:
    typedef gamer::protocol::PlayerCardsMsgProtocol                     PlayerCardsMsgProtocol;
    typedef gamer::protocol::PlayCardMsgProtocol                        PlayCardMsgProtocol;
    typedef gamer::protocol::TingCardMsgProtocol                        TingCardMsgProtocol;
    typedef google::protobuf::RepeatedField<google::protobuf::uint32>   RepeatedFieldInt;

	enum class PortraitTypes {
		LOCAL, 
		PERSONNAL
	};

	Player& operator=(const Player&) = delete;

	Player(const Player&) = delete;

	Player(id_t player_id);

	Player(id_t player_id, PlayerTypes type, Sex sex);

	static Player* Create(id_t player_id);

	virtual inline void set_player_id(id_t player_id) override;

	virtual inline id_t player_id() const override;

	virtual inline void set_is_online(bool online) override;

    virtual inline bool is_online() const override;

	virtual inline void set_player_type(PlayerTypes player_type) override;

	virtual inline PlayerTypes player_type() const override;

	virtual inline void set_sex(Sex sex) override;

	virtual inline Sex sex() const override;

    inline void set_account(const std::string& account);

    inline const std::string& account() const;

	inline void set_cur_table_id(id_t table_id);

	inline id_t cur_table_id() const;

    inline void set_cur_available_operation_id(int operation_id);

    inline int cur_available_operation_id() const;

    inline void set_has_selected_operation_ting(bool selected);

    inline bool has_selected_operation_ting() const;

	inline void set_num_ming_gang(uint8 num);

	inline uint8 num_ming_gang() const;

	inline void set_num_an_gang(uint8 num);

	inline uint8 num_an_gang() const;

	inline void set_num_win(uint8 num);

	inline uint8 num_win() const;

	void InitForGameStart();

    // do not keep the ownership
    void InitPlayerCards(PlayerCardsMsgProtocol* proto);

    void CopyInvisibleHandCardsTo(RepeatedFieldInt& to);

	bool InvisibleHandCardsContains(int card) const;

	void UpdateCardForDiscard(int discard);

    bool UpdateCardForChi(int card_of_chi, int card_match_chi_1, int card_match_chi_2);

    void UpdateCardForPeng(int card_of_peng);

    void UpdateCardForPengAndGang(int card_of_peng_gang);

    bool UpdateCardForBuhua(int* cards_of_hua_removed, int& num_cards_of_hua_removed);

    void UpdateCardForMingGang(int card_of_ming_gang);

    void UpdateCardForAnGang(int card_of_an_gang);

    void UpdateInvisibleHandCard(int new_card);

    // must be invoked after update invisible cards
    int GetAvailableOperationID(int new_card, PlayCardMsgProtocol* play_card_proto) const;

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

    // must be invoked after update invisible cards
    bool IsBuhua(int* cards_of_hua, int& cards_of_hua_len) const;

    bool IsBuhua(PlayCardMsgProtocol* proto) const;

    bool IsBuhua(int new_card) const;

    bool IsBuhua() const;

  protected:
	PlayerTypes		player_type_;
	Sex				sex_;

  private:
	bool Init();

    void GetInvisibleHandCards(int* cards, int& len) const;

    bool PengCardsContains(int card) const;

    bool RemoveInvisibleHandCards(int card, int num);

    bool GetTingOrZimoOperationID(int& operation_id, PlayCardMsgProtocol* proto) const;

    std::string		account_;
	id_t			player_id_;
	id_t			cur_table_id_;
    bool			is_online_;
    bool			has_selected_operation_ting_;
    id_t			cur_available_operation_id_;
	uint8			num_ming_gang_;
	uint8			num_an_gang_;
	uint8			num_win_;

	PlayerCardsMsgProtocol* cards_msg_proto_;
};

inline void Player::set_player_id(id_t player_id) {
    player_id_ = player_id;
}

inline id_t Player::player_id() const {
    return player_id_;
}

inline void Player::set_is_online(bool online) {
    is_online_ = online;
}

inline bool Player::is_online() const {
    return is_online_;
}

inline void Player::set_player_type(PlayerTypes player_type) {
	player_type_ = player_type;
}

inline PlayerTypes Player::player_type() const {
	return player_type_;
}

inline void Player::set_sex(Sex sex) {
	sex_ = sex;
}

inline Sex Player::sex() const {
	return sex_;
}

inline void Player::set_account(const std::string& account) {
    account_ = account;
}

inline const std::string& Player::account() const {
    return account_;
}

inline void Player::set_cur_table_id(id_t table_id) {
	cur_table_id_ = table_id;
}

inline id_t Player::cur_table_id() const {
	return cur_table_id_;
}

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

inline void Player::set_num_ming_gang(uint8 num) {
	num_ming_gang_ = num;
}

inline uint8 Player::num_ming_gang() const {
	return num_ming_gang_;
}

inline void Player::set_num_an_gang(uint8 num) {
	num_an_gang_ = num;
}

inline uint8 Player::num_an_gang() const {
	return num_an_gang_;
}

inline void Player::set_num_win(uint8 num) {
	num_win_ = num;
}

inline uint8 Player::num_win() const {
	return num_win_;
}

} // namespace gamer

#endif // CONNOR_GAME_SRC_PLAYER_H_