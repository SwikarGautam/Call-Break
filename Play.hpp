#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Cards.hpp"
#include "Player.hpp"

class Play{
    private:
        sf::Sprite cardBack[3];
        sf::Texture cardBackTexture;
        int GAME_WIDTH = 900;
        int GAME_HEIGHT = 600; 
        
    public:
    bool bidWindowShown = true;
    void playGame();
    sf::Sprite getCardBackSprite(sf::Texture & texture, int X_POS, int Y_POS, bool rotateFlag);
    void showCardBacks();
    void loadPlayerCard(std::vector<Card>& card1, sf::Texture& texture);

    //  Display Player Cards at bottom
    void displayPlayerCards(sf::RenderWindow &window, Player &p_1);
    int getWinner(std::vector<Card> & gameCards);
    void selectLegalCards (std::vector<Card> & playerCards, std::vector<Card> & gameCards);

    //  Show bid window
    void showBidWindow(bool &bidWinShown);

    //  Returns true for player card clicked
    bool checkForMouseTrigger(sf::Sprite &av_Sprite, sf::RenderWindow &av_Window);

    //  Decide to move player card forward
    void checkToMoveCardForward(sf::Sprite &card_sprite, sf::RenderWindow &window);


};

