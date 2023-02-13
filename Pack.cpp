// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Pack.h"

Pack::Pack()
:next(0){
    int i = 0;
    for (int s = 0; s < 4; s++){
        for (int r = 7; r < 13; r ++){
            Rank rank = static_cast<Rank>(r);
            Suit suit = static_cast<Suit>(s);
            cards[i] = Card(rank, suit);
            i++;
        }
    }
}

Pack::Pack(std::istream& pack_input)
:next(0){
int i = 0;
    for (int r = 0; r < 24; r ++){
        std::string rank_temp;
        std::string suit_temp;
        std::string of;
        pack_input >> rank_temp >> of >> suit_temp;
        Rank rank = string_to_rank(rank_temp);
        Suit suit = string_to_suit(suit_temp);
        cards[i] = Card(rank, suit);
        i++;
    }
}
Card Pack::deal_one(){
    next++;
    return cards[next - 1];
}

void Pack::reset(){
    next = 0;
}

void Pack::shuffle(){
    for (int shuf = 0; shuf < 7; ++shuf){
         std::array<Card, 12> t_half;
         std::array<Card, 12> b_half;
        for (int i = 0; i < 12; ++i){
            t_half[i] = cards[i];
            b_half[i] = cards[i + 12];
        }
        for (int x = 0; x < 12; ++x){
            cards[x * 2] = b_half[x];
            cards [(x * 2) + 1] = t_half[x];
        }
    }
}

bool Pack::empty() const {
    if (next > 23){
        return 1;
    }
    else {
        return 0;
    }
}