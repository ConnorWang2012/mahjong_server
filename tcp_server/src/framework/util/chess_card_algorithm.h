/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    algorithm.h
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

    // whether mahjong is hu
    static bool IsHu(int* hand_cards, int hand_cards_len) {
        int n[34] = { 0 };
        auto ret = ChessCard::Analyse(hand_cards, hand_cards_len, n);
        if ( !ret ) {
            // TODO : log
            return false;
        }
        for (int i = 0; i < 34; i++) {
            for (int kotsu_first = 0; kotsu_first < 2; kotsu_first++) {
                int t[34] = { 0 };
                memcpy(t, n, sizeof(n));
                if (t[i] >= 2) {
                    // pair
                    t[i] -= 2;

                    if (kotsu_first == 0) {
                        // pung
                        for (int j = 0; j < 34; j++) {
                            if (t[j] >= 3) {
                                t[j] -= 3;
                                //kotsu.add(j);
                            }
                        }
                        // chow
                        for (int a = 0; a < 3; a++) {
                            for (int b = 0; b < 7;) {
                                if (t[9 * a + b] >= 1 &&
                                    t[9 * a + b + 1] >= 1 &&
                                    t[9 * a + b + 2] >= 1) {
                                    t[9 * a + b]--;
                                    t[9 * a + b + 1]--;
                                    t[9 * a + b + 2]--;
                                    //shuntsu.add(9 * a + b);
                                } else {
                                    b++;
                                }
                            }
                        }
                    }
                    else {
                        // chow
                        for (int a = 0; a < 3; a++) {
                            for (int b = 0; b < 7;) {
                                if (t[9 * a + b] >= 1 &&
                                    t[9 * a + b + 1] >= 1 &&
                                    t[9 * a + b + 2] >= 1) {
                                    t[9 * a + b]--;
                                    t[9 * a + b + 1]--;
                                    t[9 * a + b + 2]--;
                                    //shuntsu.add(9 * a + b);
                                } else {
                                    b++;
                                }
                            }
                        }
                        // pung
                        for (int j = 0; j < 34; j++) {
                            if (t[j] >= 3) {
                                t[j] -= 3;
                                //kotsu.add(j);
                            }
                        }
                    }

                    // is hu
                    auto is_hu = true;
                    for (int k = 0; k < 34; k++) {
                        if (t[k] != 0) {
                            is_hu = false;
                            break;
                        }
                    }
                    if (is_hu) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    static inline bool is_season_or_flower(int card) {
        if (card >= CardConstants::CARD_VALUE_SEASON_OR_FLOWER_1) {
            return true;
        }
        return false;
    }

  private:
    // result : len is 34
    static bool Analyse(int* hand_cards, int hand_cards_len, int* result) {
        for (auto i = 0; i < hand_cards_len; i++) {
            if (hand_cards[i] < 0 || hand_cards[i] > CardConstants::DRAGON_WHITE) {
                return false;
            }
            result[hand_cards[i]]++;
        }
        return true;
    }
};

}

#endif // CONNOR_GAME_SRC_FRAMEWORK_ALGORITHM_H_