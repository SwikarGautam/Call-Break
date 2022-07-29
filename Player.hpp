#pragma once

#include<vector>
#include"Cards.hpp"

class Player{
    public:
        Player(std::vector<Card> & vect, bool user);
        std::vector<Card> cards;
        bool isUser;
        int bid;
        int round_score;
        int score;
        
};
