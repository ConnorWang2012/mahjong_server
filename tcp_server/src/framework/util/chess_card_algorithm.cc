/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    chess_card_algorithm.cc
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-01
@ description:  see the header.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#include "chess_card_algorithm.h"
#include <algorithm>

namespace gamer {

bool ChessCard::IsTing(int* hand_cards, 
                       int hand_cards_len, 
                       gamer::protocol::TingCardMsgProtocol* proto) {
    int n[34] = { 0 };

    if (!ChessCard::Analyse(hand_cards, hand_cards_len, n) ||
         nullptr == proto) {
        // TODO : log
        return false;
    }

    for (int kotsu_first = 0; kotsu_first < 2; kotsu_first++) {
        int t[34] = { 0 };

        memcpy(t, n, sizeof(n));
        if (0 == kotsu_first) {
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
        } else {
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

        // whether is ting 
        int tb[5] = { 0 };
        auto j = 0;
        auto can_ting = true;

        for (int i = 0; i < 34; i++) {
            if (t[i] > 0) {
                ++j;
                if (j > 5) { // more than 5 cards, can't ting
                    can_ting = false;
                    break;
                }

                tb[j - 1] = i;
                
                if (2 == t[i]) {
                    ++j;
                    if (j > 5) { // more than 5 cards, can't ting
                        can_ting = false;
                        break;
                    }

                    tb[j - 1] = i;
                }
            }
        }

        // ugly
        if ( !can_ting ) {
            continue;
        }

        if (2 == j) { // 2 cards
            proto->add_cards_of_ting(tb[0]);
            proto->set_discard(tb[1]);
            return true;
        } else { // 5 cards
            std::sort(tb, tb + 4);
            if (tb[0] == tb[1]) { // look like: 1, 1, x, y, z
                if (tb[2] == tb[3]) {
                    proto->add_cards_of_ting(tb[0]);
                    proto->add_cards_of_ting(tb[2]);
                    proto->set_discard(tb[4]);
                    return true;
                } else if (tb[3] == tb[4]) {
                    proto->add_cards_of_ting(tb[0]);
                    proto->add_cards_of_ting(tb[3]);
                    proto->set_discard(tb[2]);
                    return true;
                } else {
                    if (1 == tb[3] - tb[2]) {
                        proto->add_cards_of_ting(tb[2] - 1);
                        proto->add_cards_of_ting(tb[3] + 1);
                        proto->set_discard(tb[4]);
                        return true;
                    } else if (2 == tb[3] - tb[2]) {
                        proto->add_cards_of_ting(tb[2] + 1);
                        proto->set_discard(tb[4]);
                        return true;
                        // TODO
                    } else if (1 == tb[4] - tb[3]) {
                        proto->add_cards_of_ting(tb[3] - 1);
                        if (tb[4] < 26) { // DOT_9 = 26
                            proto->add_cards_of_ting(tb[4] + 1);
                        }
                        proto->set_discard(tb[2]);
                        return true;
                    } else if (2 == tb[4] - tb[3]) {
                        proto->add_cards_of_ting(tb[3] + 1);
                        proto->set_discard(tb[2]);
                        return true;
                    }
                }
            } else if (tb[1] == tb[2]) { // look like: x, 1, 1, y, z
                if (tb[4] == tb[3]) {
                    proto->add_cards_of_ting(tb[1]);
                    proto->add_cards_of_ting(tb[3]);
                    proto->set_discard(tb[0]);
                    return true;
                } else if (1 == tb[4] - tb[3]) {
                    proto->add_cards_of_ting(tb[3] - 1);
                    if (tb[4] < 26) { // DOT_9 = 26
                        proto->add_cards_of_ting(tb[4] + 1);
                    }
                    proto->set_discard(tb[0]);
                    return true;
                } else if (2 == tb[4] - tb[3]) {
                    proto->add_cards_of_ting(tb[3] + 1);
                    proto->set_discard(tb[0]);
                    return true;
                }
            } else if (tb[2] == tb[3]) { // look like: x, y, 1, 1, z
                if (1 == tb[1] - tb[0]) {
                    if (0 == tb[0]) {
                        proto->add_cards_of_ting(tb[1] + 1);
                        proto->set_discard(tb[4]);
                        return true;
                    } else {
                        proto->add_cards_of_ting(tb[0] - 1);
                        proto->add_cards_of_ting(tb[1] + 1);
                        proto->set_discard(tb[4]);
                        return true;
                    }
                } else if (2 == tb[1] - tb[0]) {
                    proto->add_cards_of_ting(tb[0] + 1);
                    proto->set_discard(tb[4]);
                    return true;
                }
            } else if (tb[3] == tb[4]) { // look like:  x, y, z, 1, 1
                if (1 == tb[1] - tb[0]) {
                    if (0 == tb[0]) {
                        proto->add_cards_of_ting(tb[1] + 1);
                        proto->set_discard(tb[2]);
                        return true;
                    } else {
                        proto->add_cards_of_ting(tb[1] + 1);
                        proto->add_cards_of_ting(tb[0] - 1);
                        proto->set_discard(tb[2]);
                        return true;
                    }
                } else if (2 == tb[1] - tb[0]) {
                    proto->add_cards_of_ting(tb[0] + 1);
                    proto->set_discard(tb[2]);
                    return true;
                    // TODO
                } else if (1 == tb[2] - tb[1]) {
                    proto->add_cards_of_ting(tb[2] + 1);
                    proto->add_cards_of_ting(tb[1] - 1);
                    proto->set_discard(tb[0]);
                    return true;
                } else if (2 == tb[2] - tb[1]) {
                    proto->add_cards_of_ting(tb[1] + 1);
                    proto->set_discard(tb[0]);
                    return true;
                }
            }
        }
    } // for

    return false;
}

bool ChessCard::IsTing(int* hand_cards, int hand_cards_len) {
    int n[34] = { 0 };

    if (!ChessCard::Analyse(hand_cards, hand_cards_len, n)) {
        // TODO : log
        return false;
    }

    for (int kotsu_first = 0; kotsu_first < 2; kotsu_first++) {
        int t[34] = { 0 };

        memcpy(t, n, sizeof(n));
        if (0 == kotsu_first) {
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
        } else {
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

        // whether is ting 
        int tb[5] = { 0 };
        auto j = 0;
        auto can_ting = true;

        for (int i = 0; i < 34; i++) {
            if (t[i] > 0) {
                ++j;
                if (j > 5) { // more than 5 cards, can't ting
                    can_ting = false;
                    break;
                }

                tb[j - 1] = i;

                if (2 == t[i]) {
                    ++j;
                    if (j > 5) { // more than 5 cards, can't ting
                        can_ting = false;
                        break;
                    }

                    tb[j - 1] = i;
                }
            }
        }

        // ugly
        if (!can_ting) {
            continue;
        }

        if (2 == j) { // 2 cards
            return true;
        } else { // 5 cards
            std::sort(tb, tb + 4);
            if (tb[0] == tb[1]) { // look like: 1, 1, x, y, z
                if (tb[2] == tb[3]) {
                    return true;
                } else if (tb[3] == tb[4]) {
                    return true;
                } else {
                    if (1 == tb[3] - tb[2]) {
                        return true;
                    } else if (2 == tb[3] - tb[2]) {
                        return true;
                    } else if (1 == tb[4] - tb[3]) {
                        return true;
                    } else if (2 == tb[4] - tb[3]) {
                        return true;
                    }
                }
            } else if (tb[1] == tb[2]) { // look like: x, 1, 1, y, z
                if (tb[4] == tb[3]) {
                    return true;
                } else if (1 == tb[4] - tb[3]) {
                    return true;
                } else if (2 == tb[4] - tb[3]) {
                    return true;
                }
            } else if (tb[2] == tb[3]) { // look like: x, y, 1, 1, z
                if (1 == tb[1] - tb[0]) {
                    if (0 == tb[0]) {
                        return true;
                    } else {
                        return true;
                    }
                }
                else if (2 == tb[1] - tb[0]) {
                    return true;
                }
            } else if (tb[3] == tb[4]) { // look like:  x, y, z, 1, 1
                if (1 == tb[1] - tb[0]) {
                    if (0 == tb[0]) {
                        return true;
                    } else {
                        return true;
                    }
                } else if (2 == tb[1] - tb[0]) {
                    return true;
                } else if (1 == tb[2] - tb[1]) {
                    return true;
                } else if (2 == tb[2] - tb[1]) {
                    return true;
                }
            }
        }
    } // for

    return false;
}

bool ChessCard::IsHu(int* hand_cards, int hand_cards_len) {
    int n[34] = { 0 };

    if ( !ChessCard::Analyse(hand_cards, hand_cards_len, n) ) {
        // TODO : log
        return false;
    }

    for (int i = 0; i < 34; i++) {
        for (int kotsu_first = 0; kotsu_first < 2; kotsu_first++) {
            int t[34] = { 0 };

            memcpy(t, n, sizeof(n));
            if (t[i] >= 2) {
                t[i] -= 2; // pair

                if (0 == kotsu_first) {
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
                } else {
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

                // whether is hu
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
            } // if (t[i] >= 2)
        } // for 1
    } // for 2

    return false;
}

} // namespace gamer