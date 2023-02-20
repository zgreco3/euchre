// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_player_insertion) {
  // Create a Human player
  Player * human = Player_factory("NotRobot", "Human");

  // Print the player using the stream insertion operator
  ostringstream oss1;
  oss1 << * human;

  // Verify that the output is the player's name
  ASSERT_EQUAL(oss1.str(), "NotRobot");

  // Create a Simple player
  Player * alice = Player_factory("Alice", "Simple");

  // Print the player using the stream insertion operator
  ostringstream oss2;
  oss2 << *alice;
  ASSERT_EQUAL(oss2.str(), "Alice");

  // Clean up players that were created using Player_factory()
  delete human;
  delete alice;
}

TEST(test_all_trump_player_lead_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(QUEEN, SPADES));


  // Bob leads
  Card card_led = bob->lead_card(SPADES);

  // Verify the card Bob selected to lead
  Card ACE_spades(ACE, SPADES);
  ASSERT_EQUAL(card_led, ACE_spades); //check led card

  delete bob;
}

TEST(test_all_trump_last_not_player_lead_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(TEN, HEARTS));


  // Bob leads
  Card card_led = bob->lead_card(SPADES);

  // Verify the card Bob selected to lead
  Card ace_spades(TEN, HEARTS);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete bob;
}

TEST(test_simple_player_add_discard) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, HEARTS));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Card jack_spades(JACK, SPADES);
  string trump;
  bob->add_and_discard(nine_spades);
  // Verify Bob's order up and trump suit

  delete bob;
}


TEST(test_simple_player_make_trump) {
  // Bob's hand
  // 
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump,SPADES);

  delete bob;
}

TEST(test_simple_player_make_trump_round_2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, HEARTS));
  bob->add_card(Card(TEN, CLUBS));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, HEARTS));

  // Bob makes tump
  Card nine_spades(NINE, CLUBS);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    false,           // Bob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);

  delete bob;
}
TEST(test_simple_player_make_trump_round_12_edge) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, HEARTS));
  bob->add_card(Card(TEN, CLUBS));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(ACE, HEARTS));

  // Bob makes tump
  Card nine_spades(NINE, CLUBS);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    false,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup);

  delete bob;
}
// 
    // extra trump tests 
//


TEST(test_simple_player_make_trump_fail) {
  // Bob's hand
  // 
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(ACE, HEARTS));
  bob->add_card(Card(QUEEN, HEARTS));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup);

  delete bob;
}

TEST(test_simple_player_make_trump_edge_r1) {
  // Bob's hand
  // 
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(ACE, HEARTS));
  bob->add_card(Card(QUEEN, HEARTS));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);

  delete bob;
}


TEST(test_all_player_lead_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));


  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(NINE, HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades(ACE, SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete bob;
}


// my tests

TEST(test_play_card_one) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, HEARTS));

  Suit trump = static_cast<Suit>(0);
  // Bob plays
  const Card card_led = Card(TEN, SPADES);
  Card card_played = bob->play_card(card_led, trump);

  // Verify the card Bob selected right card to play
  Card king_spades(KING, SPADES);
  ASSERT_EQUAL(card_played, king_spades); //check card played

  delete bob;
}


TEST(test_play_card_no_led) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(ACE, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, HEARTS));

  Suit trump = static_cast<Suit>(1);
  // Bob plays
  const Card card_led = Card(TEN, CLUBS);
  Card card_played = bob->play_card(card_led, trump);

  // Verify the card Bob selected right card to play
  Card queen_spades(QUEEN, SPADES);
  ASSERT_EQUAL(card_played, queen_spades); //check card played

  delete bob;
}

TEST(test_play_card_all_trump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(ACE, SPADES));
  bob->add_card(Card(KING, SPADES));


  Suit trump = static_cast<Suit>(0);
  // Bob plays
  const Card card_led = Card(ACE, SPADES);
  Card card_played = bob->play_card(card_led, trump);

  // Verify the card Bob selected right card to play
  Card ace_spades(ACE, SPADES);
  ASSERT_EQUAL(card_played, ace_spades); //check card played

  delete bob;
}

TEST(test_play_card_one_led) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(ACE, SPADES));
  bob->add_card(Card(KING, SPADES));


  Suit trump = static_cast<Suit>(3);
  // Bob plays
  const Card card_led = Card(ACE, HEARTS);
  Card card_played = bob->play_card(card_led, trump);

  // Verify the card Bob selected right card to play
  Card ten_hearts(TEN, HEARTS);
  ASSERT_EQUAL(card_played, ten_hearts); //check card played

  delete bob;
}
TEST(test_play_card_three_trump_one_no_led) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(ACE, SPADES));
  bob->add_card(Card(KING, SPADES));


  Suit trump = static_cast<Suit>(0);
  // Bob plays
  const Card card_led = Card(ACE, DIAMONDS);
  Card card_played = bob->play_card(card_led, trump);

  // Verify the card Bob selected right card to play
  Card ten_hearts(TEN, HEARTS);
  ASSERT_EQUAL(card_played, ten_hearts); //check card played

  delete bob;
}
//
  // we need more make trump
//


// Add more tests here

TEST_MAIN()