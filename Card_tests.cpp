// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;

//need a test with a led card and two more cards one of which is of led suit and one isnt(neither are trump)
TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(test_face_or_ace) {
    Card three_spades = Card(THREE, SPADES);
    ASSERT_FALSE(three_spades.is_face_or_ace());

    Card king_spades = Card(KING, SPADES);
    ASSERT_TRUE(king_spades.is_face_or_ace());

    Card ace_spades = Card(ACE, SPADES);
    ASSERT_TRUE(ace_spades.is_face_or_ace());
}
TEST(test_is_right_bower_false) {
    const Suit &trump = HEARTS;
    Card three_spades = Card(THREE, SPADES);
    ASSERT_FALSE(three_spades.is_right_bower(trump));
}
TEST(test_is_left_bower_false) {
    const Suit &trump = HEARTS;
    Card three_spades = Card(THREE, SPADES);
    ASSERT_FALSE(three_spades.is_left_bower(trump));
}
TEST(test_is_right_bower_true) {
    const Suit &trump = HEARTS;
    Card jack_hearts = Card(JACK, HEARTS);
    ASSERT_TRUE(jack_hearts.is_right_bower(trump));
}
TEST(test_is_right_bower_is_not_left_bower) {
    const Suit &trump = HEARTS;
    Card jack_hearts = Card(JACK, HEARTS);
    ASSERT_FALSE(jack_hearts.is_left_bower(trump));
}
TEST(test_is_left_bower) {
    const Suit &trump = HEARTS;
    Card jack_diamonds = Card(JACK, DIAMONDS);
    ASSERT_TRUE(jack_diamonds.is_left_bower(trump));
}
TEST(test_is_left_bower_is_not_right_bower) {
    const Suit &trump = HEARTS;
    Card jack_diamonds = Card(JACK, DIAMONDS);
    ASSERT_FALSE(jack_diamonds.is_right_bower(trump));
}
TEST(test_card_less) {
    Card c1(ACE, HEARTS);
    Card c2(NINE, HEARTS);
    Card c3(JACK, DIAMONDS);
    Card c4(JACK, HEARTS);
    Card c5(JACK, SPADES);
    Card c6(KING, SPADES);
    ASSERT_EQUAL(Card_less(c1,c2, SPADES), false);
    ASSERT_EQUAL(Card_less(c3,c4, HEARTS), true);
}
TEST(test_less_greater) {
    Card ten_clubs = Card(TEN, CLUBS);
    Card jack_clubs = Card(JACK, CLUBS);
    ASSERT_TRUE(jack_clubs > ten_clubs);

}
TEST(test_card_suit_and_rank) {
    Card two_spades = Card();
    ASSERT_EQUAL(two_spades.get_rank(),TWO);
    ASSERT_EQUAL(two_spades.get_suit(), SPADES);

    Card three_spades = Card(THREE, SPADES);
    ASSERT_EQUAL(three_spades.get_rank(), THREE);
    ASSERT_EQUAL(three_spades.get_suit(), SPADES);
    ASSERT_EQUAL(three_spades.get_suit(CLUBS), SPADES);
}

TEST(test_card_type) {
    Card three_spades = Card(THREE, SPADES);
    ASSERT_FALSE(three_spades.is_face_or_ace());
    ASSERT_FALSE(three_spades.is_right_bower(CLUBS));
    ASSERT_FALSE(three_spades.is_left_bower(CLUBS));
    ASSERT_FALSE(three_spades.is_trump(CLUBS));
}

TEST(test_card_self_comparison) {
    Card three_spades = Card(THREE, SPADES);
    ASSERT_FALSE(three_spades < three_spades);
    ASSERT_TRUE(three_spades <= three_spades);
    ASSERT_FALSE(three_spades > three_spades);
    ASSERT_TRUE(three_spades >= three_spades);
    ASSERT_TRUE(three_spades == three_spades);
    ASSERT_FALSE(three_spades != three_spades);
}

TEST(test_Suit_next) {
    ASSERT_EQUAL(Suit_next(CLUBS), SPADES);
    ASSERT_EQUAL(Suit_next(SPADES), CLUBS);
    ASSERT_EQUAL(Suit_next(DIAMONDS), HEARTS);
    ASSERT_EQUAL(Suit_next(HEARTS), DIAMONDS);
}

TEST(test_Card_less_self) {
    Card three_spades = Card(THREE, SPADES);
    ASSERT_FALSE(Card_less(three_spades, three_spades, CLUBS));
    ASSERT_FALSE(Card_less(three_spades, three_spades, three_spades,
                           CLUBS));
}

TEST(test_card_insertion) {
    Card three_spades = Card(THREE, SPADES);
    ostringstream oss;
    oss << three_spades;
    ASSERT_EQUAL(oss.str(), "Three of Spades");
}
TEST(test_string_to_suit) {
    string str = "Hearts";
    ASSERT_EQUAL(string_to_suit(str), HEARTS);
}
TEST(test_is_trump_true) {
    Card three_spades = Card(THREE, SPADES);
    ASSERT_EQUAL(three_spades.is_trump(SPADES), true);
}
TEST(test_is_trump_false) {
    Card three_spades = Card(THREE, SPADES);
    ASSERT_EQUAL(three_spades.is_trump(HEARTS), false);
}
TEST(test_is_trump_left_bower) {
    Card three_spades = Card(JACK, SPADES);
    ASSERT_EQUAL(three_spades.is_trump(CLUBS), true);
}
TEST(test_is_less) {
    Suit trump = HEARTS;
    Card led_card = Card(KING, HEARTS);
    Card led_card2 = Card(KING, DIAMONDS);
    Card jack_hearts = Card(JACK, HEARTS);
    Card jack_spades = Card(JACK, SPADES);
    Card nine_hearts = Card(NINE, HEARTS);
    Card nine_diamonds = Card(NINE, DIAMONDS);
    Card jack_diamonds = Card(JACK, DIAMONDS);
    Card ten_spades = Card(TEN, SPADES);
    Card ten_hearts = Card(TEN, HEARTS);
    Card ten_diamonds = Card(TEN, DIAMONDS);
    Card queen_diamonds = Card(QUEEN, DIAMONDS);
    ASSERT_FALSE(Card_less(jack_hearts, jack_diamonds, led_card, trump));
    ASSERT_TRUE(Card_less(jack_diamonds, jack_hearts, led_card, trump));
    ASSERT_FALSE(Card_less(ten_hearts, ten_spades, led_card, trump));
    ASSERT_TRUE(Card_less(ten_spades, ten_hearts, led_card, trump));
    ASSERT_TRUE(Card_less(ten_diamonds, ten_hearts, led_card, trump));
    ASSERT_TRUE(Card_less(jack_spades, ten_hearts, led_card, trump));

    ASSERT_TRUE(Card_less(queen_diamonds, jack_hearts, DIAMONDS));
    Card ace_clubs = Card(ACE, CLUBS);
    Card ace_spades = Card(ACE, SPADES);
    //Spades is lower than clubs
    ASSERT_TRUE(Card_less(ace_spades, ace_clubs, HEARTS));
    //new case
    ASSERT_EQUAL(jack_diamonds.get_suit(HEARTS), HEARTS);
    //

    //new case
    //
    ASSERT_TRUE(Card_less(nine_diamonds, nine_hearts, led_card2, trump));
    //

    ASSERT_TRUE(Card_less(ten_spades, ten_hearts, trump));
    ASSERT_TRUE(Card_less(ten_diamonds, ten_hearts, trump));
    ASSERT_FALSE(Card_less(jack_diamonds, ten_hearts, trump));
    ASSERT_TRUE(Card_less(jack_diamonds, jack_hearts, trump));
}

TEST(Card_less_with_bower){
    Suit trump = static_cast<Suit>(1);
    // Bob plays
    const Card card_led = Card(TEN, SPADES);
    ASSERT_FALSE(Card_less(Card(JACK, HEARTS), Card(ACE, HEARTS), card_led, trump ))
}
// Add more test cases here

TEST_MAIN()
