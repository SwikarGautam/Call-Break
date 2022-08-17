#include "Play.hpp"
#include "Menu.hpp"
#include <bits/stdc++.h>

// Used for sorting Cards
bool compare(Card & c1, Card & c2){
    return c1.getN() > c2.getN();
}

Play::Play(){
    std::vector<Card> allCards; //It is a vector for all 52 cards
    std::vector<Card> cardn;
//     std::vector<Card>::iterator f;

//     // Initializing all the cards and adding to allCards
    for(int i=0;i<4;i++){
        for(int j = 0;j<13;j++){
            allCards.push_back(Card(i,j));
        }
    }
//     // shuffling cards (doesn't work) currently
    std::random_shuffle(allCards.begin(),allCards.end());
    
	if (!cardFrontTexture.loadFromFile("src\\Images\\Cards\\cardFront\\all_cards.png"))
	{
		std::cout << "Error loading card image.";
	}
    srand(time(0));
    playerInd = rand()%4;
    // loadPlayerCard(allCards,texture);
    for(int i=0;i<4;i++){
        cardn.assign(allCards.begin()+13*i,allCards.begin()+13*(i+1));
        sort(cardn.begin(),cardn.end(),compare);
        players.push_back(Player(cardn,i==playerInd));
    }
    // loadPlayerCard(players[playerInd].cards,cardFrontTexture);
}


void Play::playGame(){ 

    //  Load texture for card back
	if (!cardBackTexture.loadFromFile("src\\Images\\Cards\\cardBack\\cardBack_red1.png"))
	{
		std::cout << "Error loading cardBack image.";
	}

    //  Array with 3 elements containing cardBack at 3 positions
    showCardBacks();
    
    //  Texture for table
    sf::Texture table_texture;
    if (!table_texture.loadFromFile("src/Images/table_back.jpg"))
    {
        std::cout << "Error loading table background image.";
    }
    sf::Sprite tableBackground(table_texture);

    loadPlayerCard(players[playerInd].cards,cardFrontTexture);

    sf::RenderWindow GAME_WINDOW;
    GAME_WINDOW.create(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), "Play Call Break");
    turnInd = rand()%4;
    bool roundStarted = false;
    int round = 0;
    int bid, winInd = turnInd;
    while (GAME_WINDOW.isOpen())
    {
		sf::Event event;
		while (GAME_WINDOW.pollEvent(event))
		{
				if (event.type == sf::Event::Closed)
				{   
					GAME_WINDOW.close();
				}
                if (event.type == sf::Event::KeyPressed)
					{
						//	Esc  key pressed
						if (event.key.code == sf::Keyboard::Escape)
                        {
							//	Escape key pressed closes credits window
							GAME_WINDOW.close();

                            Menu menu;
                            menu.openMainMenuWindow();
						}
                    }
        }
      
        //  Check for click of all 13 player cards
        
        setPlayerCardsPos(players[playerInd].cards);
        if (roundStarted){
            // std::cout<<gameCards.size()<<std::endl;
            if (turnInd == playerInd){
                selectLegalCards(players[turnInd].cards, gameCards);
                for (auto i=players[playerInd].cards.begin(); i<players[playerInd].cards.end(); ++i){
                    // i->display();
                    if (checkForMouseTrigger(i->sprite, GAME_WINDOW) && i->playable){
                        gameCards.push_back(*i);
                        players[playerInd].cards.erase(i);
                        turnInd = (turnInd+1)%4;
                        // i->display();
                    }
                }
                // std::cout<<std::endl;
            }
            
            else{
                selectLegalCards(players[turnInd].cards,gameCards);
                int indx = players[turnInd].getCardIndex(gameCards);
                gameCards.push_back(players[turnInd].cards[indx]);
                players[turnInd].cards.erase(players[turnInd].cards.begin() + indx);
                turnInd = (turnInd+1)%4;
            }

            if (gameCards.size() >= 4){
                winInd = (getWinner() + winInd)%4;
                players[winInd].round_score += 1;
                turnInd = winInd;
                // for(int i=0;i<4;i++){
                //     gameCards[i].display();}
                // std::cout<<winInd<<"\n";
                gameCards.clear();

            }
        } 

        else{
            
            if (turnInd == playerInd){
                bid = showBidWindow();
                if (bid != -1){
                    players[playerInd].bids[round] = bid;
                    roundStarted = true;
                    turnInd = (turnInd+1)%4;}}
            else{
                turnInd = (turnInd+1)%4;}
        }
        GAME_WINDOW.clear();
        
        // drawPlayersCards(GAME_WINDOW, players[playerInd].cards );
        int size =  players[playerInd].cards.size();
        // std::cout<<size<<std::endl;
        setPlayerCardsPos(players[playerInd].cards);
        GAME_WINDOW.draw(tableBackground);
        for(auto i=players[playerInd].cards.begin();i!=players[playerInd].cards.end();++i)
        {
            GAME_WINDOW.draw(i->sprite);
            // i->display();
        }

        GAME_WINDOW.draw(cardBack[0]);
        GAME_WINDOW.draw(cardBack[1]);
        GAME_WINDOW.draw(cardBack[2]);
        GAME_WINDOW.display(); 
    }
}

//  Function to return sprite for back of card sprite

sf::Sprite Play::getCardBackSprite(sf::Texture & texture, int X_POS, int Y_POS, bool rotateFlag){
    sf::Sprite backSprite(texture);

    //  Rotate sprite if flag set to true
    if (rotateFlag){
        backSprite.setRotation(90);
    }
    //  Specify position to blit on screen in vector form
    backSprite.setPosition(sf::Vector2f(X_POS , Y_POS));

    backSprite.setTextureRect(sf::IntRect(0, 0,140,190)); 

    //  Scale card back img    
    backSprite.scale(sf::Vector2f(0.6, 0.6));
    return backSprite;
}

void Play::showCardBacks()
{
        //  Get Sprite with specified arguments
    cardBack[0] = getCardBackSprite(cardBackTexture, GAME_WIDTH/2 - Card::eachCardWidth/2, 0, false);
    cardBack[1] = getCardBackSprite(cardBackTexture, 130, GAME_HEIGHT/2 - Card::eachCardHeight/2, true);
    cardBack[2] = getCardBackSprite(cardBackTexture, GAME_WIDTH, GAME_HEIGHT/2 - Card::eachCardHeight/2, true);

}

void Play::loadPlayerCard(std::vector<Card>& card, sf::Texture& texture)
{
    //load texture for the 13 cards
    // std::cout<<card.size()<<std::endl;
    for(auto i=card.begin();i!=card.end();++i){
            i->loadTexture(texture);
        }
}

//  Show player cards
void Play::setPlayerCardsPos( std::vector<Card> &pCards){
    int size = pCards.size();
    for(auto i=pCards.begin();i!=pCards.end();++i)
    {
        //  define postion for player cards
        if (i->playable)
            i->sprite.setPosition(sf::Vector2f(GAME_WIDTH/2-((size-1)*55+112)/2 + 55*(i-pCards.begin()), GAME_HEIGHT-180));
        else
            i->sprite.setPosition(sf::Vector2f(GAME_WIDTH/2-((size-1)*55+112)/2 + 55*(i-pCards.begin()), GAME_HEIGHT-150));
    }
}

void drawPlayersCards(sf::RenderWindow &window, std::vector<Card> &pCards){
    
    for(auto i=pCards.begin();i!=pCards.end();++i)
    {
        window.draw(i->sprite);
        
        }
}

//returns the index of winning card
int Play::getWinner(){
    int maxInd = 0;

    for(auto i = gameCards.begin();i<gameCards.end();++i ){
        if (gameCards[maxInd].isSmlThan(*i)){
            maxInd = i - gameCards.begin();
        }
    }
    return maxInd;
}


//sets playable member of legal cards to true and other cards to false
//legal cards are those cards which a player is allowed to throw given the gameCards
//gameCards is a vector of Cards that prior players have thrown
void Play::selectLegalCards (std::vector<Card> & playerCards, std::vector<Card> & gameCards){
    if (gameCards.size() == 0){
        for(auto i=playerCards.begin();i<playerCards.end();++i){
            i->playable = true;
        }
    }
    else {
        std::vector<Card>::iterator maxCard = gameCards.begin();
        int gameSuit = gameCards[0].getSuit();
        bool setFlag = false;
        bool containSpade = false;
        for(auto i = gameCards.begin();i<gameCards.end();++i ){
            i->playable = false;
            if (i->getSuit()==3 && gameSuit!=3){
                containSpade = true;
            }
            if (maxCard->isSmlThan(*i) && (i->getSuit()!=3|| gameSuit==3) ){
                maxCard = i;
            }
        }

        for(auto i=playerCards.begin();i<playerCards.end();++i){
            if(maxCard->isSmlThan(*i) && (i->getSuit()==gameSuit)){
                i->playable = true;
                setFlag = true;
            }
            else{
                i->playable = false;
            }
        }

        if (!setFlag || containSpade){
            for(auto i=playerCards.begin();i<playerCards.end();++i){
                if(i->getSuit()==gameSuit){
                    i->playable = true;
                    setFlag = true;
                }
            }
        }

        if (!setFlag && gameSuit!=3){
            for(auto i=playerCards.begin();i<playerCards.end();++i){
                if(i->getSuit()==3){
                    i->playable = true;
                    setFlag = true;
                }
            }
        }

        if (!setFlag){
            for(auto i=playerCards.begin();i<playerCards.end();++i){
                i->playable = true; 
                setFlag = true;
            }  
        }
    }
}

//  Check if sprite is clicked through mouse
bool Play::checkForMouseTrigger(sf::Sprite &av_Sprite, sf::RenderWindow &av_Window)
{

    int mouseX = sf::Mouse::getPosition().x;
    int mouseY = sf::Mouse::getPosition().y;
    sf::Vector2i windowPosition = av_Window.getPosition();
    // std::cout<<windowPosition.x<<" "<<windowPosition.y<<std::endl;

    if(mouseX > av_Sprite.getPosition().x + windowPosition.x && mouseX < ( av_Sprite.getPosition().x + av_Sprite.getGlobalBounds().width + windowPosition.x - 20)
        && mouseY > av_Sprite.getPosition().y + windowPosition.y + 30  && mouseY < ( av_Sprite.getPosition().y + av_Sprite.getGlobalBounds().height + windowPosition.y + 30) )
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            return true;
        }
        return false;
    }
    return false;
}

//  Small Bid window
int Play::showBidWindow(){
    sf::RenderWindow BID_WINDOW;

    BID_WINDOW.create(sf::VideoMode(200, 200), "Call Your Bid");
    while (BID_WINDOW.isOpen())
    {
		sf::Event event;
		while (BID_WINDOW.pollEvent(event))
		{
				if (event.type == sf::Event::Closed)
				{
					BID_WINDOW.close();
				}
                if (event.type == sf::Event::TextEntered)
                {
                    int num = event.text.unicode - 48;  // get ascii for digit entered and convert again to num
                    //  To open window just once in game loop
                    if (num>0 && num<=8){
                        std::cout << "Bid entered = " << num;   //  This is the user input bid no
                        //  Close bid window only for bid range 1 - 8
                        BID_WINDOW.close();
                        return num;
                    }
                }
        }
    }
    return -1;
}

//  Function to move sprite (but doesn't at the moment )
void Play::checkToMoveCardForward(sf::Sprite &card_sprite, sf::RenderWindow &window){
        bool mouseClick = checkForMouseTrigger(card_sprite, window);
        if(mouseClick)
        {
            std::cout << "Card clicked" <<std::endl;
            // card_sprite.move(sf::Vector2f(400, 400));
        }
}