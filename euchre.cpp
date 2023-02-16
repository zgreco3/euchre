// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "Pack.h"
#include <fstream>

class Game {
    public:
    Game(std::vector <Player *> pvec, std::istream& pack_input, bool shuff, int ptw)
        : players(pvec), pack(pack_input), ptw(ptw), shuff(shuff){}
    
    void play(){
        
        int dealerNum = 0;
        int hcounter = 0;
        while ((t1pts || t2pts) < ptw){
            if (shuff){
                pack.shuffle();
            }
            if (!shuff){
                pack.reset();
            }
            deal(dealerNum);
            const Card &upcard = pack.deal_one();
            Suit order_up_suit = upcard.get_suit();
            int indMP = 0;
            std::cout << "Hand " << hcounter << std::endl;
            ++hcounter;
            std::cout << players[dealerNum]->get_name() << " deals" << std::endl;
            std::cout << upcard << " turned up" << std::endl;
            make_trump(dealerNum, upcard, order_up_suit, indMP);
            dealOrdRes(dealerNum);
            play_hand(order_up_suit, dealerNum, indMP);

            if (t1pts >= ptw){
                break;
            }
            if (t2pts >= ptw){
                break;
            }
        }
        if (t1pts > t2pts){
            std::cout << players[0]->get_name() << " and " 
            << players[2]->get_name() << " win!";
        }
        if (t1pts < t2pts){
            std::cout << players[1]->get_name() << " and " 
            << players[3]->get_name() << " win!";
        }
        for (size_t i = 0; i < players.size(); ++i) {
            delete players[i];  
        }
    }
    
    private: 
    std::vector <Player *> players;
    Pack pack;
    int t1pts = 0;
    int t2pts = 0;
    int ptw;
    bool shuff;

    void shuffle(){
        pack.shuffle();
    }

    void deal2(int dnum){
        players[dnum]->add_card(pack.deal_one());
        players[dnum]->add_card(pack.deal_one());
    }
    void deal3(int dnum){
        players[dnum]->add_card(pack.deal_one());
        players[dnum]->add_card(pack.deal_one());
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

    void make_trump(int dealerNum, const Card &upcard, 
    Suit order_up_suit, int &indMP){
        int oldDnum = dealerNum;
        dealOrdRes(dealerNum);
        for (int i = 0; i < 4; i++){
            bool id = is_deal(oldDnum, dealerNum);
            if (players[dealerNum]->make_trump(upcard, id,
            1, order_up_suit) == 0){
                std::cout << players[dealerNum]->get_name() 
                << " passes"<< std::endl;
                dealOrdRes(dealerNum);
            }
            else if (players[dealerNum]->make_trump(upcard, id,
            1, order_up_suit) == 1){
                players[oldDnum]->add_and_discard(upcard);
                std::cout << players[dealerNum]->get_name() 
                << " orders up "<< order_up_suit << std::endl;
                indMP = dealerNum;
                dealOrdRes(dealerNum);
                std::cout << std::endl;
                break;
            }
        }
        for (int i = 0; i < 4; i++){
            bool id = is_deal(oldDnum, dealerNum);
            if (players[dealerNum]->make_trump(upcard, id,
            2, order_up_suit) == 0){
                std::cout << players[dealerNum]->get_name() 
                << " passes"<< std::endl;
                dealOrdRes(dealerNum);
            }
            else if (players[dealerNum]->make_trump(upcard, id,
            2, order_up_suit) == 1){
                players[oldDnum]->add_and_discard(upcard);
                std::cout << players[dealerNum]->get_name() 
                << " orders up "<< order_up_suit << std::endl;
                std::cout << std::endl;
                indMP = dealerNum;
                dealOrdRes(dealerNum);
                break;
            }
        }
    }

    void play_first_round(Suit order_up_suit, int &dealerNum,
     int &ttally1, int &ttally2){
        std::vector <Card> pile;
        Card lead_card = players[dealerNum]->lead_card(order_up_suit);
        
        pile.push_back(lead_card);
        std::cout << lead_card << " led by " 
        << players[dealerNum]->get_name() << std::endl;

        int playerStart = dealerNum;
        int winnerInd;
        for (int i = 0; i < 3; ++i){
            dealOrdRes(dealerNum);
            pile.push_back(players[dealerNum]->play_card(lead_card, order_up_suit));
            std::cout << pile[i + 1] << " played by " 
            << players[dealerNum]->get_name() << std::endl;
        }

        
        for (int i = 0; i < 4; ++i){
            //int one = playerStart;
            
            int one = playerStart;
            Card pmax = pile[0];
            if (!Card_less(pile[i], pmax, lead_card, order_up_suit)){
                winnerInd = one;
                pmax = pile[i];
            }
             dealOrdRes(playerStart);
        }
        if (winnerInd == 0 || winnerInd == 2){
            ++ttally1;
        }
        if (winnerInd == 1 || winnerInd == 3){
            ++ttally2;
        }
        std::cout << players[winnerInd]->get_name() << " takes the trick" <<  std::endl;
        dealerNum = winnerInd;
        std::cout << std::endl;
    }

    void play_hand(Suit order_up_suit, int &dealerNum, int &indMP){
        int indtemp = indMP;
        dealOrdRes(indtemp);
        int indEP = indtemp;
        int ttally1 = 0;
        int ttally2 = 0;
        
        for (int i = 0; i < 5; ++i){
            play_first_round(order_up_suit, dealerNum, ttally1, ttally2);
        }


        if (ttally1 > ttally2){
            std::cout << players[0]->get_name() << " and " <<  players[2]->get_name() 
            << " win the hand" <<  std::endl;
                if (indMP == 0 || indMP == 2){
                    t1pts += 1;
                }
                if (indEP == 0 || indEP == 2){
                    t1pts += 2;
                }
            if (ttally1 == 5){
                if (indMP == 0 || indMP == 2){
                    std::cout << "march!" <<  std::endl;
                    t1pts +=1;
                }
                return;
                if (indEP == 0 || indEP == 2){
                    std::cout << "euchre!" <<  std::endl;
                }
            }
        }
        if (ttally1 < ttally2){
            std::cout << players[1]->get_name() << " and " <<  players[3]->get_name() 
            << " win the hand" <<  std::endl;
                if (indMP == 1 || indMP == 3){
                    t2pts += 1;
                }
                if (indEP == 1 || indEP == 3){
                    t2pts += 2;
                }
        
            if (ttally2 == 5){
                if (indMP == 1 || indMP == 3){
                    std::cout << "march!" <<  std::endl;
                    t2pts += 1;
                }
                if (indEP == 1 || indEP == 3){
                    std::cout << "euchre!" <<  std::endl;
                }
            }
        }
        
        std::cout << players[0]->get_name() << " and " <<  players[2]->get_name() 
            << " have " <<  t1pts << "points" << std::endl; 
        std::cout << players[1]->get_name() << " and " <<  players[3]->get_name() 
            << " have " <<  t1pts << "points" << std::endl; 
    }

};
int main(int argc, char *argv[]){
    std::string isshuf = argv[2];

    
    if (argc != 12 || ((isshuf != "shuffle") && (isshuf != "noshuffle")) 
    || ((std::stoi(argv[3]) < 1) && (std::stoi(argv[3]) > 100))){
        std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << std::endl;
        return 1;
    }
    /*
    for (int i = 5; i < 12; i +=2){
        if ((strcmp(argv[i], "Simple") && (strcmp(argv[i], "Human")) != 0)){
            std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << std::endl;
            return 1;
        }
    }*/

    std::ifstream rand;
    std::string pack_filename = argv[1];
    rand.open(pack_filename);

    if (rand.fail()){
        std::cout << "Error opening " << pack_filename << std::endl;
        return 69;
    }

    std::vector <Player *> pvec;
    for (int i = 4; i < 11; i += 2){
        std::string ntemp = argv[i];
        std::string sorhtemp = argv[i + 1];
        pvec.push_back(Player_factory(ntemp, sorhtemp));
    }
    bool shuff;
    std::string sons = argv[2];
    if (sons == "shuffle"){
        shuff = true;
    }
    else{
        shuff = false;
    }
    for (int i = 0; i < 12; ++i){
        std::cout << argv[i] << " ";
    }
    std::cout << std::endl;
    Game euchre(pvec, rand, shuff, std::stoi(argv[3]));
    euchre.play();
}