#include "Cards.hpp"


bool Card::isSmlThan(const Card &c1){

    if (c1.suit == suit)
        return rank < c1.rank;
    
    else if (c1.suit == 3)
        return true;

    else 
        return false;
    
}


Card::Card(int s, int r):suit(s), rank(r){
    sprite.setSize(sf::Vector2f(140.f,190.f));
    sprite.scale(sf::Vector2f(0.7, 0.7));
}

Card::Card(const Card & c1):suit(c1.suit), rank(c1.rank){
    sprite = c1.sprite;
}

void Card::loadTexture(const sf::Texture & texture){
    sprite.setTexture(&texture);
    
    int n = suit*13 + rank;
    int x = n % 9;
    int y = n / 9;
    sprite.setTextureRect(sf::IntRect(eachCardWidth*x,eachCardHeight*y, eachCardWidth, eachCardHeight)); 
    sprite.setPosition(sf::Vector2f(300, 400));
}


int Card::getSuit(){
    return suit;
}


void Card::display(){
    std::cout<<"suit: "<<suit<<" rank: "<<rank<<std::endl;
}

int Card::getN(){
    return suit*13 + rank;
}

void Card::operator=(const Card & c1){
    suit = c1.suit;
    rank = c1.rank;
}

