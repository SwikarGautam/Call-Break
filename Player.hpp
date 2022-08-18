#pragma once

#include<vector>
#include"Cards.hpp"

class Player{
    public:
        bool bidWindowShown = true;
        Player(std::vector<Card>  vect, bool user);
        std::vector<Card> cards;
        int getCardIndex(const std::vector<Card> gameCards);
        bool isUser;
        int bids[5] = {0,0,0,0,0};
        int round_score = 0;
        float scores[5] = {-99,-99,-99,-99,-99};
        int setUserSelectedCard();
        int selectedCardIndex;
        bool hasSelected = false;
        void setBid(int round);
        
};
