#include "Cards.hpp"



bool Card::isGtrThan(Card c1){

    if (c1.suit == suit)
        return rank > c1.rank;
    
    else if (c1.suit == 3)
        return false;

    else 
        return true;
    
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


