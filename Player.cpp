// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include <algorithm>

using namespace std;

class SimplePlayer : public Player{
    private:
        string name;
        vector <Card> hand;

    public:
        SimplePlayer(const string &name_in)
        : name(name_in){}
        virtual const string & get_name() const{
            return name;
        }
        virtual void add_card(const Card &c){
            hand.push_back(c);
        }
        virtual bool make_trump(const Card &upcard, bool is_dealer,
                        int round, Suit &order_up_suit) const{
            int fass = 0;
            //us = upcard suit
            Suit us = upcard.get_suit();
            Suit usAlt = Suit_next(us);
            
            if (round == 1){
                for (int i = 0; i < 5; ++i){
                    if (((hand[i].is_face_or_ace() == 1) && 
                        (hand[i].get_suit() == us)) || 
                        hand[i].is_left_bower(us)){
                        fass++;
                    }
                    if (fass >= 2){
                        order_up_suit = us;
                        return 1;
                    }
                }
            }
            if (round == 2){
                if (is_dealer == 1){
                    order_up_suit = usAlt;
                    return 1;
                }
                for (int i = 0; i < 5; i++){
                    if (((hand[i].is_face_or_ace() == 1) && 
                        (hand[i].get_suit() == usAlt)) ||
                        hand[i].is_left_bower(usAlt)){
                        fass++;
                    }
                    if (fass > 0){
                        order_up_suit = usAlt;
                        return 1;
                    }
                }
            }
            return 0;
        }
        virtual void add_and_discard(const Card &upcard){
            int indLow = 0;
            add_card(upcard);
            //cout << upcard << endl;
            for (int i = 1; i < 6; ++i){
                if (Card_less(hand[indLow], hand[i], upcard.get_suit()) == 0){
                    indLow = i;
                }
            }
            hand.erase(hand.begin() + indLow);
        }

        virtual Card lead_card(Suit trump){
            //print_hand();
            int ttally = 0;
            Card curLead = hand[0];
            for (size_t i = 0; i < hand.size(); i++){
                if (hand[i].is_trump(trump)){
                    ttally++;
                }
                if (!hand[i].is_trump(trump)){
                    curLead = hand[i];
                }
            }
            if ((int)hand.size() == ttally){
                for (size_t i = 0; i < hand.size(); i++){
                    if (Card_less(curLead, hand[i], trump)){
                        curLead = hand[i];
                    }
                }
            }
            else if(ttally < (int)hand.size()){
                for (size_t i = 0; i < hand.size(); i++){
                    if (!hand[i].is_trump(trump) && hand[i] > curLead ){
                        curLead = hand[i];
                    }
                }
            }
            int indT = 0;
            for (size_t i = 0; i < hand.size(); i++){
                if(hand[i] == curLead){
                    indT = i;
                }
            }
            hand.erase(hand.begin() + indT);
            return curLead;
        }

        virtual Card play_card(const Card &led_card, Suit trump){
           //print_hand();
            int ltally = 0;
            Suit led = led_card.get_suit();
            Card curLead = hand[0];
            for (size_t i = 0; i < hand.size(); i++){
                if (hand[i].is_trump(led) && !hand[i].is_left_bower(led)){
                    ltally++;
                }
            }
            if (ltally > 0){
                for (size_t i = 0; i < hand.size(); i++){
                    if (hand[i].get_suit() == led && Card_less(curLead, hand[i], led)
                        && !hand[i].is_left_bower(led)){
                        curLead = hand[i];
                    }
                }
            }
            else{
                for (size_t i = 0; i < hand.size(); i++){
                    if (Card_less(hand[i], curLead, led_card, trump)){
                        curLead = hand[i];
                    }
                }
            }
            int indT = 0;
            for (size_t i = 0; i < hand.size(); i++){
                if(hand[i] == curLead){
                    indT = i;
                }
            }
            hand.erase(hand.begin() + indT);
            return curLead;
        }

        virtual void print_hand() const {
            for (size_t i = 0; i < (hand.size()); i++){
                cout << "Simple player " << name << "'s hand: [" << i << 
                "] " << hand[i] << endl;
            }
        }
};

class HumanPlayer : public Player{
    private:
        string name;
        vector <Card> hand;

    public:
        HumanPlayer(const string &name_in)
        : name(name_in){}

        virtual const string & get_name() const{
            return name;
        }
        virtual void add_card(const Card &c){
            hand.push_back(c);
        }
        virtual void print_hand() const {
            for (size_t i = 0; i < (hand.size()); i++){
                cout << "Human player " << name << "'s hand: [" << i << 
                "] " << hand[i] << endl;
            }
        }
        virtual bool make_trump(const Card &upcard, bool is_dealer,
                        int round, Suit &order_up_suit) const{
            print_hand();
            // assert(round == 1 || 2);
            cout << "Human player " << name <<
             ", please enter a suit, or \"pass\":\n";
            string in;
            cin >> in;
            if(in == "pass"){
                return false;
            }
            else{
                //order_up_suit = string_to_suit(in);
                return true;
            }
        }

        //look at this more
        virtual void add_and_discard(const Card &upcard){
            print_hand();
            int in;
            cout << "Discard upcard: [-1]\n";
            cout << "Human player " << name <<
             ", please select a card to discard:\n";
            cin >> in;
            assert(in == -1 || 0 || 1 || 2 || 3 || 4);
            //fix potentially
            if (in == -1){
                return;
            }
            //fix potentially
            else{
                hand.erase(hand.begin() + in);
                hand.push_back(upcard);
                sort(hand.begin(), hand.end());
            }
        }

        virtual Card lead_card(Suit trump){
            print_hand();
            int in;
            cout << "Human player " << name << ", please select a card:\n";
            cin >> in;
            assert(in == 0 || 1 || 2 || 3 || 4);
            Card temp = hand[in];
            hand.erase(hand.begin() + in - 1);
            sort(hand.begin(), hand.end());
            return temp;
        }

        virtual Card play_card(const Card &led_card, Suit trump){
            return lead_card(trump);
        }
};

Player * Player_factory(const string &name, const string &strategy){
//   We need to check the value of strategy and return 
//   the corresponding player type.
    if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.*
        return new SimplePlayer(name);
    }
    if (strategy == "Human") {
    // The "new" keyword dynamically allocates an object.
        return new HumanPlayer(name);
    }
    return nullptr;
}



ostream & operator<<(ostream &os, const Player &p){
    os << p.get_name();
    return os;
}