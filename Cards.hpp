#pragma once

#include<iostream>
#include<SFML/Graphics.hpp>

class Card{
    private:
        int suit;
        int rank;
       
    public:
        sf::Sprite sprite;
        bool playable;
        Card(int s,int r);
        void loadTexture(sf::Texture & texture);
        bool isGtrThan(Card c1);

};