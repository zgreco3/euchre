// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}
TEST(test_card_less) {
    Card c1(ACE, HEARTS);
    Card c2(NINE, HEARTS);
    Card c3(JACK, DIAMONDS);
    Card c4(JACK, HEARTS);
    Card c5(JACK, SPADES);
    Card c6(KING, SPADES);

    ASSERT_EQUAL(Card_less(c1,c2, SPADES), false);
}

// Add more test cases here

TEST_MAIN()
