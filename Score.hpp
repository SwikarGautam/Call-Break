#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.hpp"
#include "Text.hpp"

class Score
{
    private:
        int SCORE_WIDTH = 500;
        int SCORE_HEIGHT = 333;
    public:
        int showScoreWin(sf::RenderWindow & SCORE_WINDOW, std::vector<Player> players,int currentRound );
};