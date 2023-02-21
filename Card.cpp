// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <array>
#include "Card.h"

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const RANK_NAMES[] = {
  "Two",   // TWO
  "Three", // THREE
  "Four",  // FOUR
  "Five",  // FIVE
  "Six",   // SIX
  "Seven", // SEVEN
  "Eight", // EIGHT
  "Nine",  // NINE
  "Ten",   // TEN
  "Jack",  // JACK
  "Queen", // QUEEN
  "King",  // KING
  "Ace"    // ACE
};

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
Rank string_to_rank(const std::string &str) {
  for(int r = TWO; r <= ACE; ++r) {
    if (str == RANK_NAMES[r]) {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank) {
  os << RANK_NAMES[rank];
  return os;
}

//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank) {
  string str;
  is >> str;
  rank = string_to_rank(str);
  return is;
}



/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
Suit string_to_suit(const std::string &str) {
  for(int s = SPADES; s <= DIAMONDS; ++s) {
    if (str == SUIT_NAMES[s]) {
      return static_cast<Suit>(s);
    }
  }
  assert(false); // Input string didn't match any suit
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit) {
  os << SUIT_NAMES[suit];
  return os;
}

//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit) {
  string str;
  is >> str;
  suit = string_to_suit(str);
  return is;
}


/////////////// Write your implementation for Card below ///////////////

  //EFFECTS Initializes Card to the Two of Spades
  Card::Card() 
  : rank(TWO), suit(SPADES){}

  //EFFECTS Initializes Card to specified rank and suit
  Card::Card(Rank rank_in, Suit suit_in)
  : rank(rank_in), suit(suit_in){}

  //EFFECTS Returns the rank
  Rank Card::get_rank() const{
    return rank;
  }

  //EFFECTS Returns the suit.  Does not consider trump.
  Suit Card::get_suit() const{
     return suit;
  }

  //EFFECTS Returns the suit
  //HINT: the left bower is the trump suit!
  Suit Card::get_suit(Suit trump) const{
    if(is_left_bower(trump)){
      return trump;
    }
    else{
      return suit;
    }
  }

  //EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
  bool Card::is_face_or_ace() const{
    if (rank == JACK || rank == QUEEN || rank == KING || rank == ACE){
        return 1;
    }
    else{
        return 0;
    }
  }

  //EFFECTS Returns true if card is the Jack of the trump suit
  bool Card::is_right_bower(Suit trump) const{
    if (rank == JACK && suit == trump){
      return 1;
    }
    else{
        return 0;
    }
  }

  //EFFECTS Returns true if card is the Jack of the next suit
  bool Card::is_left_bower(Suit trump) const{
    if (rank == JACK){
      if ((trump == CLUBS && suit == SPADES) || 
      (trump == SPADES && suit == CLUBS)
      || (trump == DIAMONDS && suit == HEARTS) || 
      (trump == HEARTS && suit == DIAMONDS)){
          return 1;
      }
    }
    return 0;
  }

  //EFFECTS Returns true if the card is a trump card.  All cards of the trump
  // suit are trump cards.  The left bower is also a trump card.
  bool Card::is_trump(Suit trump) const{
    if (suit == trump || is_left_bower(trump) == true){
      return 1;
    }
    else{
      return 0;
    }
  }

  bool operator<(const Card &lhs, const Card &rhs) { 
    if (lhs.get_rank() < rhs.get_rank()){
      return 1;
    }
    else{
      return 0;
    }
  }

  bool operator==(const Card &lhs, const Card &rhs){
      if (rhs.get_rank() == lhs.get_rank()){
          return 1;
      }
      return 0;
  }

  bool operator<=(const Card &lhs, const Card &rhs){
      return (lhs < rhs || lhs == rhs);
  }

  bool operator>(const Card &lhs, const Card &rhs){
      return !(lhs <= rhs);
  }

  bool operator>=(const Card &lhs, const Card &rhs){
      return !(lhs < rhs);
  }

  bool operator!=(const Card &lhs, const Card &rhs){
    return !(rhs == lhs);
  }

//EFFECTS Prints Card to stream, for example "Two of Spades"
ostream & operator<<(std::ostream &os, const Card &card){
  os << card.get_rank() << " of " << card.get_suit();
  return os;
}

//EFFECTS Reads a Card from a stream in the format "Two of Spades"
//NOTE The Card class declares this operator>> "friend" function,
//     which means it is allowed to access card.rank and card.suit.
std::istream & operator>>(std::istream &is, Card &card){
  string junk;
  string r;
  string s;
  is >> r;
  card.rank = string_to_rank(r);
  is >> junk;
  is >> s;
  card.suit = string_to_suit(s);
  return is;
}

//EFFECTS returns the next suit, which is the suit of the same color
Suit Suit_next(Suit suit){
  if (suit == SPADES){
    return CLUBS;
  }
  else if (suit == CLUBS){
    return SPADES;
  }
  else if (suit == HEARTS){
    return DIAMONDS;
  }
  else if (suit == DIAMONDS){
    return HEARTS;
  }
  else {
    return HEARTS;
  }
}

bool Card_less(const Card &a, const Card &b, Suit trump){
  if (a.is_trump(trump) > b.is_trump(trump)){
    return 0;
  }
  else if (a.is_trump(trump) < b.is_trump(trump)){
    return 1;
  }
  else{
    if (a.is_right_bower(trump)){
      return 0;
    }
    else if (b.is_right_bower(trump)){
      return 1;
    }
    else if (a.is_left_bower(trump)){
      return 0;
    }
    else if (b.is_left_bower(trump)){
      return 1;
    }
    else if (a < b){
      return 1;
    }
    else{
      return 0;
    }
  }
  return 0;
}

bool Card_less(const Card &a, const Card &b, const Card &led_card,
               Suit trump){
  Suit led = led_card.get_suit();
  Suit A = a.get_suit();
  Suit B = b.get_suit();
  //if trump is led this will act exactly like 
  //Card_less(const Card &a, const Card &b, const std::string &trump)
  //if a and b are both the led card or both not the led this will act exactly like 
  //Card_less(const Card &a, const Card &b, const std::string &trump)
  if(led_card.get_suit() == trump || 
      (A != led &&
      B != led) ||
      (A == led && 
      B == led)){
    return Card_less(a, b, trump);
  }
  else if (A != led && B == led){
    return true;
  }
  else if (A == led && B != led){
    return false;
  }
  else{
    cout << "error" << endl;
    return false;
  }
}