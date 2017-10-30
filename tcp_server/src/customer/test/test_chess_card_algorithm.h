/*******************************************************************************
@ copyright(C), 2015-2020, ConnorAndHisFriendsCompany.Inc
@ filename:	    test_chess_card_algorithm.h
@ author:	    Connor
@ version:	    1.0.0
@ date:		    2017-06-01
@ description:  test chess card algorithm.
@ others:
@ history:
1.date:
author:
modification:
********************************************************************************/

#ifndef CONNOR_GAME_SRC_TEST_CHESS_CARD_ALGORITHM_H_
#define CONNOR_GAME_SRC_TEST_CHESS_CARD_ALGORITHM_H_

#include "framework/util/chess_card_algorithm.h"
#include "customer/msg/protocol/ting_card_msg_protocol.pb.h"

namespace gamer {

void test_shuffle_algorithm() {
    std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    gamer::ChessCard::Shuffle(vec);
    for (auto& x : vec) {
        printf("shuffle : %d\n", x);
    }
}

void test_is_hu_algorithm() {
    //int cards[14] = { 1, 1, 1, 2, 3, 4, 27, 27, 27, 29, 29 };
	int cards[5] = { 33, 33, 33, 31, 31 };
    auto ret = gamer::ChessCard::IsHu(cards, 5);
    if (ret) {
        printf("IsHu : true\n");
    } else {
        printf("IsHu : false\n");
    }
}

void test_is_ting_algorithm() {
    //int cards[13] = { 0, 0, 0,  1, 1, 1,  2, 3, 4,  23, 23, 23, 24 };
    //int cards[14] = { 0, 0,  0, 1, 2,  0, 1, 2,  23, 23, 23, 28,  29, 29 };
    //int cards[14] = { 0, 0, 0, 0, 1,  4, 5, 6,  23, 23, 23, 28,  29, 29 };
    //int cards[14] = { 0, 0, 1, 2, 0, 1, 2, 23, 23, 23, 23, 24, 25, 27 };
    int cards[14] = { 0, 0, 0, 2, 3, 4, 5, 6, 23, 23, 23, 29, 29, 29 };
    gamer::protocol::TingCardMsgProtocol proto;

    auto ret = gamer::ChessCard::IsTing(cards, 14, &proto);
    if (ret) {
        if (1 == proto.cards_of_ting_size()) {
            printf("IsTing : true, ting cards : %d, discard : %d\n", proto.cards_of_ting(0), proto.discard());
        } else if (2 == proto.cards_of_ting_size()) {
            printf("IsTing : true, ting cards : %d, %d, discard : %d\n", proto.cards_of_ting(0), proto.cards_of_ting(1), proto.discard());
        }
    } else {
        printf("IsTing : false\n");
    }
}

}

#endif // CONNOR_GAME_SRC_TEST_CHESS_CARD_ALGORITHM_H_
