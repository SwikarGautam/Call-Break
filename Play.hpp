#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Cards.hpp"
#include  "Text.hpp"
#include "Player.hpp"

class Play{
    private:
        sf::RectangleShape cardBack[3];
        sf::Texture cardBackTexture;
        int GAME_WIDTH = 950;
        int GAME_HEIGHT = 600;
        const int playerInd;
        int turnInd=0;
        std::vector<Player> players;
        std::vector<Card> gameCards;
        
    public:
        Play();
        sf::Texture cardFrontTexture;
        bool bidWindowShown = true;
        void playGame(sf::RenderWindow & GAME_WINDOW);
        sf::RectangleShape getCardBackSprite(const sf::Texture & texture, int X_POS, int Y_POS, bool rotateFlag);
        void showCardBacks();
        void loadPlayerCard(std::vector<Card>& card1, sf::Texture& texture);

        //  Display Player Cards at bottom
        void setPlayerCardsPos( std::vector<Card> &pCards, bool playerTurn);
        void drawCards(sf::RenderWindow &window, std::vector<Card> &pCards);
        int getWinner();
        void selectLegalCards (std::vector<Card> & playerCards, std::vector<Card> & gameCards);

        //  Show bid window
        int showBidWindow();

        //  Returns true for player card clicked
        bool checkForMouseTrigger(sf::RectangleShape &av_Sprite, sf::RenderWindow &av_Window);

        //  Decide to move player card forward
        void checkToMoveCardForward(sf::RectangleShape &card_sprite, sf::RenderWindow &window);

        void setGameCards(int startInd);  

        void distCards(bool createPlayer); 

};

