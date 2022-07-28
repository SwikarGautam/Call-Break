#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Cards.hpp"
#include "Player.hpp"

class Play{
    private:
        int GAME_WIDTH = 800;
        int GAME_HEIGHT = 600; 
    public:

    void playGame();
    sf::Sprite getCardBackSprite(sf::Texture & texture, int X_POS, int Y_POS, bool rotateFlag);

};