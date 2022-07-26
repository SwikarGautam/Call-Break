#pragma once

#include<vector>
#include"Cards.hpp"

class Player{
    public:
        std::vector<Card> cards;
        bool isUser;
        Player(std::vector<Card> & vect, bool user);
        
};