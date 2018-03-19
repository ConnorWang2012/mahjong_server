/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    chess_card_algorithm.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-01
@ description:  algorithm about chess & cards
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_FRAMEWORK_ALGORITHM_H_
#define CONNOR_GAME_SRC_FRAMEWORK_ALGORITHM_H_

#include "customer/room/card_constants.h"
#include "framework/util/util.h"
#include "customer/msg/protocol/ting_card_msg_protocol.pb.h"

namespace gamer {

class ChessCard {
  public:
    template<typename Cards>
    static void Shuffle(Cards& cards) {
        auto n = (int)cards.size();
        for (auto i = 0; i < n; i++) {
            int j = gamer::GenerateRandom<int>(0, i);
            std::swap(cards[i], cards[j]);
        }
    }

    // whether mahjong is ting
    static bool IsTing(int* hand_cards,
                       int hand_cards_len,
                       gamer::protocol::TingCardMsgProtocol* proto);

    // whether mahjong is ting
    static bool IsTing(int* hand_cards, int hand_cards_len);

    // whether mahjong is hu
    static bool IsHu(int* hand_cards, int hand_cards_len);

    static inline bool is_season_or_flower(int card);

  private:
    // result : len is 34
    static bool Analyse(int* hand_cards, int hand_cards_len, int* result) {
        for (int i = 0; i < hand_cards_len; i++) {
            if (hand_cards[i] < 0 || hand_cards[i] > CardConstants::DRAGON_WHITE) {
                return false;
            }
            result[hand_cards[i]]++;
        }
        return true;
    }
};

inline bool ChessCard::is_season_or_flower(int card) {
    if (card >= CardConstants::SEASON_SPRING && card <= CardConstants::FLOWER_BAMBOO) {
        return true;
    }
    return false;
}

}

#endif // CONNOR_GAME_SRC_FRAMEWORK_ALGORITHM_H_