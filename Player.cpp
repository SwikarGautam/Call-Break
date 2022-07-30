#include"Player.hpp"
#include<vector>
#include"Cards.hpp"

Player::Player(std::vector<Card> & vect, bool user){
     cards = vect;
     isUser = user;
     
}

int Player::getCardIndex(const std::vector<Card>){
     if (isUser){
          if(hasSelected){
               hasSelected = false;
               return selectedCardIndex;
          }
          else{
               return -1;}
     }
     else{
          return 0;
     }
}