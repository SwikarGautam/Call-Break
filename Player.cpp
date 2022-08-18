#include"Player.hpp"
#include<vector>
#include"Cards.hpp"

Player::Player(std::vector<Card> vect, bool user){
     cards = vect;
     isUser = user;
     
}

 int Player::getCardIndex(const std::vector<Card>){
     int ind = 0;
     for(int i=0; i<cards.size();i++){
          if (cards[i].playable){
               ind = i;
          }
     }
     return ind;
}

void Player::setBid(int round){
     if (!isUser){
          bids[round] = 3;
     }
}