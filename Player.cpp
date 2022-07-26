#include"Player.hpp"
#include<vector>
#include"Cards.hpp"

Player::Player(std::vector<Card> & vect, bool user){
     cards = vect;
     isUser = user;
     
}