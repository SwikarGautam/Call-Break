#include "Cards.hpp"



bool Card::isSmlThan(const Card &c1){

    if (c1.suit == suit)
        return rank < c1.rank;
    
    else if (c1.suit == 3)
        return true;

    else 
        return false;
    
}


Card::Card(int s, int r){
    suit = s;
    rank = r;
}

void Card::loadTexture(sf::Texture & texture){
    sprite.setTexture(texture);
    
    int n = suit*13 + rank;
    int x = n % 9;
    int y = n / 9;
    sprite.setTextureRect(sf::IntRect(140*x,190*y,140,190)); 
}

int Card::getSuit(){
    return suit;
}

void Card:: operator=(const Card & c1){
    suit = c1.suit;
    rank = c1.rank;
}

void Card::display(){
    std::cout<<"suit: "<<suit<<" rank: "<<rank<<std::endl;
}
