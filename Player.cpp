#include"Player.hpp"
#include<vector>
#include"Cards.hpp"

Player::Player(std::vector<Card> vect, bool user){
     cards = vect;
     isUser = user;
     
}

int Player::getCardIndex(const std::vector<Card>){
     for(int i=0; i<cards.size();i++){
          if (cards[i].playable){
               return i;
          }
     }
     return -1;
}

void Player::setBid(int round){
     if (!isUser){
          bids[round] = 3;
     }
}