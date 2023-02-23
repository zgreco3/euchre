// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "Pack.h"
#include <fstream>

using namespace std;

class Game {
    public:
    Game(vector <Player *> pvec, istream& pack_input, bool shuff, int ptw)
        : players(pvec), pack(pack_input), ptw(ptw), shuff(shuff){}
    
    void play(){
        int dealerNum = 0;
        int hcounter = 0;
        //int loop_counter = 0;
        //bool opposite = false;
        //while both teams dont have points to win shuffle deck depending on shuff bool
        while ((t1pts || t2pts) < ptw){
            pack.reset();
            if (shuff){
                pack.shuffle();
            }
            //runs all functions to go through an entire game
            // loop_counter++;
            // if (loop_counter > 1 ){
            //     dealOrdRes(dealerNum);
            // }

            //change
            
            deal(dealerNum);
            // we had & upcard
            const Card upcard = pack.deal_one();
            Suit upcard_suit = upcard.get_suit();
            Suit opposite_upcard_suit = Suit_next(upcard_suit);
            int indMP = 0;
            cout << "Hand " << hcounter << endl;
            
            

            cout << players[dealerNum]->get_name() << " deals" << endl;
            cout << upcard << " turned up" << endl;

            
            Suit trump = upcard_suit;
            if(make_trump(dealerNum, upcard, upcard_suit, indMP)){
                //if(make_trump(dealerNum, upcard, opposite_upcard_suit, indMP)){
                    trump = opposite_upcard_suit;
                //}
            }
            //dealOrdRes(dealerNum);
            play_hand(trump, dealerNum, indMP);
            ++hcounter;
            if (t1pts >= ptw){
                break;
            }
            if (t2pts >= ptw){
                break;
            }
            dealOrdRes(dealerNum);
        }
        if (t1pts > t2pts){
            cout << players[0]->get_name() << " and " 
            << players[2]->get_name() << " win!" << endl;
        }
        if (t1pts < t2pts){
            cout << players[1]->get_name() << " and " 
            << players[3]->get_name() << " win!" << endl;
        }
        for (size_t i = 0; i < players.size(); ++i) {
            delete players[i];  
        }
        
    }
    void shuffle(){
        pack.shuffle();
    }

    void deal2(int dnum){
        //cout << "first card" << dnum << endl;
        players[dnum]->add_card(pack.deal_one());
        //cout << "second card" << dnum << endl;
        players[dnum]->add_card(pack.deal_one());
    }
    void deal3(int dnum){
        //cout << "fir card" << dnum << endl;
        players[dnum]->add_card(pack.deal_one());
        //cout << "sec card" << dnum << endl;
        players[dnum]->add_card(pack.deal_one());
        //cout << "thir card" << dnum << endl;
        players[dnum]->add_card(pack.deal_one());
    }

    void dealOrdRes(int &dealOrder){
        dealOrder++;
        if(dealOrder > 3){
            dealOrder = 0;
        }
    }

    void deal(int &dealerNum){
        int firstDeal = 0;
        if (dealerNum == 0){
            firstDeal = 1;
        }
        else if (dealerNum == 1){
            firstDeal = 2;
        }
        else if (dealerNum == 2){
            firstDeal = 3;
        }
       
        for (int i = 0; i < 2; i++){
            deal3(firstDeal);
            dealOrdRes(firstDeal);
            deal2(firstDeal);
            dealOrdRes(firstDeal);
        } 
        for (int i = 0; i < 2; i++){
            deal2(firstDeal);
            dealOrdRes(firstDeal);
            deal3(firstDeal);
            dealOrdRes(firstDeal);
        }
        
    }

    bool is_deal(int oldNum, int dealerNum){
        if (oldNum == dealerNum){
            return 1;
        }
        return 0;
    }

    bool make_trump(int dealerNum, const Card &upcard, 
            Suit &order_up_suit, int &indMP/*, bool &opposite*/){
        int oldDnum = dealerNum;
        dealOrdRes(dealerNum);
        for (int i = 0; i < 4; i++){
            bool id = is_deal(oldDnum, dealerNum);
            bool isOrderingtrump = players[dealerNum]->make_trump(upcard, id,
                                    1, order_up_suit);
            if (isOrderingtrump == 0){
                cout << players[dealerNum]->get_name() 
                << " passes"<< endl;
                dealOrdRes(dealerNum);
            }
            else if (isOrderingtrump == 1){
                cout << players[dealerNum]->get_name() 
                << " orders up "<< order_up_suit << endl;
                players[oldDnum]->add_and_discard(upcard);
                indMP = dealerNum;
                dealOrdRes(dealerNum);
                cout << endl;
                return false;
            }
        }
        for (int i = 0; i < 4; i++){
            ///
            order_up_suit = Suit_next(order_up_suit);
            //
            bool id = is_deal(oldDnum, dealerNum);
            bool isorderingtrump2 = players[dealerNum]->make_trump(upcard, id,
                                    2, order_up_suit);
            if (isorderingtrump2 == 0){
                cout << players[dealerNum]->get_name() 
                << " passes"<< endl;
                dealOrdRes(dealerNum);
            }
            else if (isorderingtrump2 == 1){
                cout << players[dealerNum]->get_name() 
                << " orders up "<< order_up_suit << endl;
                cout << endl;
                indMP = dealerNum;
                dealOrdRes(dealerNum);
                return true;
                //opposite = true;
                //break;
            }
        }
        return false;
    }

    void play_round(Suit order_up_suit, int &dealerNum,
     int &ttally1, int &ttally2){
        int indtemp = dealerNum;
        dealOrdRes(indtemp);
        vector <Card> pile;
        Card lead_card = players[indtemp]->lead_card(order_up_suit);
        
        pile.push_back(lead_card);
        //dealOrdRes(indtemp);
        cout << lead_card << " led by " 
        << players[indtemp]->get_name() << endl;
        
        int playerStart = dealerNum;
        //dealOrdRes(playerStart);
        for (int i = 1; i < 4; i++){
            dealOrdRes(indtemp);
            //check play_card
            pile.push_back(players[indtemp]->play_card(lead_card, order_up_suit));
            cout << pile[i] << " played by " 
            << players[indtemp]->get_name() << endl;
        }

        int winnerPerson = playerStart;
        int counter = 1;

        
        Card pmax = pile[1];
        // cout << "the lead card is " << lead_card << endl; 
        // cout << "the max card to start is " << pmax << endl; 
        for (int i = 2; i < 4; ++i){
            if (!Card_less(pile[i], pmax, lead_card, order_up_suit)){
                counter = i;
                pmax = pile[i];
                //cout << "the max card is now " << pmax << endl;
            }
            dealOrdRes(playerStart);
        }
        //Suit led = lead_card.get_suit(order_up_suit);
        if(Card_less(lead_card, pmax, lead_card, order_up_suit)){
            for(int i = 0; i < counter; i++){
                dealOrdRes(winnerPerson);
            }
        }
        dealOrdRes(winnerPerson);
        if (winnerPerson == 0 || winnerPerson == 2){
            ++ttally1;
        }
        else if (winnerPerson == 1 || winnerPerson == 3){
            ++ttally2;
        }
        
        cout << players[winnerPerson]->get_name() << " takes the trick" <<  endl;
        for(int i = 0; i < 3; i++){
            dealOrdRes(winnerPerson);
        }
        dealerNum = winnerPerson;
        cout << endl;
    }

    void play_hand(Suit order_up_suit, int &dealerNum, int &indMP){
        int nextHandDealerNum = dealerNum;
        int indtemp = indMP;
        dealOrdRes(indtemp);
        int indEP = indtemp;
        int ttally1 = 0;
        int ttally2 = 0;
        
        for (int i = 0; i < 5; i++){
            play_round(order_up_suit, dealerNum, ttally1, ttally2);
        }
        dealerNum = nextHandDealerNum;
        // for(int i = 0; i < 3; i++){
        //     dealOrdRes(dealerNum);
        // }

        if (ttally1 > ttally2){
            cout << players[0]->get_name() << " and " <<  players[2]->get_name() 
            << " win the hand" <<  endl;
            if (indMP == 0 || indMP == 2){
                if(ttally1 == 5){
                    cout << "march!" <<  endl;
                    t1pts +=2; 
                }
                else{
                    t1pts += 1;
                }
            }
            else if (indEP == 0 || indEP == 2){
                cout << "euchred!" <<  endl;
                t1pts += 2;
            }
        }
        else if (ttally2 > ttally1){
            cout << players[1]->get_name() << " and " <<  players[3]->get_name() 
            << " win the hand" <<  endl;
            if (indMP == 1 || indMP == 3){
                if(ttally2 == 5){
                    cout << "march!" <<  endl;
                    t2pts += 2; 
                }
            else{
                t2pts += 1;
                }
            }
            if (indEP == 1 || indEP == 3){
                cout << "euchred!" <<  endl;
                t2pts += 2;
            }
        }
        
        cout << players[0]->get_name() << " and " <<  players[2]->get_name() 
            << " have " <<  t1pts << " points" << endl; 
        cout << players[1]->get_name() << " and " <<  players[3]->get_name() 
            << " have " <<  t2pts << " points" << endl << endl; 
    }
        
    private: 
    vector <Player *> players;
    Pack pack;
    int t1pts = 0;
    int t2pts = 0;
    int ptw;
    bool shuff;
};
int main(int argc, char *argv[]){
    string isshuf = argv[2];

    
    if (argc != 12 || ((isshuf != "shuffle") && (isshuf != "noshuffle")) 
    || ((stoi(argv[3]) < 1) && (stoi(argv[3]) > 100))){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return 1;
    }
    /*
    for (int i = 5; i < 12; i +=2){
        if ((strcmp(argv[i], "Simple") && (strcmp(argv[i], "Human")) != 0)){
            cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
            return 1;
        }
    }*/

    ifstream rand;
    string pack_filename = argv[1];
    rand.open(pack_filename);

    if (rand.fail()){
        cout << "Error opening " << pack_filename << endl;
        return 69;
    }

    vector <Player *> pvec;
    for (int i = 4; i < 11; i += 2){
        string ntemp = argv[i];
        string sorhtemp = argv[i + 1];
        pvec.push_back(Player_factory(ntemp, sorhtemp));
    }
    bool shuff;
    string sons = argv[2];
    if (sons == "shuffle"){
        shuff = true;
    }
    else{
        shuff = false;
    }
    for (int i = 0; i < 12; ++i){
        cout << argv[i] << " ";
    }
    cout << endl;
    Game euchre(pvec, rand, shuff, stoi(argv[3]));
    euchre.play();
}