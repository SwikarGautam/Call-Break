#include "Play.hpp"
#include "Menu.hpp"
#include "Text.hpp"
#include <bits/stdc++.h>
#include <sstream>

// Used for sorting Cards
bool compare(Card & c1, Card & c2){
    return c1.getN() > c2.getN();
}

Play::Play():playerInd(0){
    distCards(true);
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

    // loadPlayerCard(players[playerInd].cards,cardFrontTexture);


    sf::RenderWindow GAME_WINDOW;
    GAME_WINDOW.create(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), "Play Call Break");
    GAME_WINDOW.setFramerateLimit(60);

    const sf::Time turnDelay = sf::seconds(1.f/5.f);
    sf::Clock clock;
    sf::Time timeElapsed = sf::Time::Zero;

    Text text[4];
    
        text[0].loadText("0/0", GAME_WIDTH/2, GAME_HEIGHT - 200);
        text[1].loadText("0/0", 41, GAME_HEIGHT/2 - 20);
        text[2].loadText("0/0", GAME_WIDTH/2,  100);
        text[3].loadText("0/0", GAME_WIDTH - 70, GAME_HEIGHT/2 - 20);
    std::ostringstream ss;

    turnInd = rand()%4;
    int roundState = 0;
    int round = 0;
    int roundNum = 0;
    int bid, winInd = turnInd;
    while (GAME_WINDOW.isOpen())
    {
        //  Load Bot Cards
        loadPlayerCard(gameCards,cardFrontTexture);
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
        GAME_WINDOW.clear();
        
        GAME_WINDOW.draw(tableBackground);
        setPlayerCardsPos(players[playerInd].cards, turnInd == playerInd);
        // Enters here if bidding is complete and players are throwing cards
        if (roundState == 1){

            timeElapsed += clock.restart();
            
            if (timeElapsed > turnDelay){
                timeElapsed -= turnDelay;
                if (gameCards.size() >= 4){
                    winInd = (getWinner() + winInd)%4;
                    players[winInd].round_score += 1;
                    turnInd = winInd;
                    gameCards.clear();
                    roundNum += 1;
                }
                if (roundNum > 12){
                    roundState = 2;
                    roundNum = 0;
                    continue;
                }

                if (turnInd == playerInd){
                    selectLegalCards(players[turnInd].cards, gameCards);
                    for (auto i=players[playerInd].cards.begin(); i<players[playerInd].cards.end(); ++i){
                        
                        if (checkForMouseTrigger(i->sprite, GAME_WINDOW) && i->playable){
                            gameCards.push_back(*i);
                            players[playerInd].cards.erase(i);
                            turnInd = (turnInd+1)%4;
                            loadPlayerCard(players[playerInd].cards, cardFrontTexture);
                            break;
                        }
                    }
                }
                
                else{
                    selectLegalCards(players[turnInd].cards,gameCards);
                    int indx = players[turnInd].getCardIndex(gameCards);
                    gameCards.push_back(players[turnInd].cards[indx]);
                    players[turnInd].cards.erase(players[turnInd].cards.begin() + indx);
                    turnInd = (turnInd+1)%4;
                }
                    
                loadPlayerCard(gameCards,cardFrontTexture);
                
            }
        } 
        // Enters here if bidding hasn't compoleted
        else if(roundState == 0){
            
            if (turnInd == playerInd){
                bid = showBidWindow();
                if (bid != -1){
                    players[playerInd].bids[round] = bid;
                    turnInd = (turnInd+1)%4;}}
            else{
                players[turnInd].setBid(round);
                turnInd = (turnInd+1)%4;
                }

            if(turnInd == winInd){
                roundState = 1;
            }
        }

        // Enters here after each 13 rounds are completed
        else if(roundState == 2){
            for(int i=0;i<4;i++){
                players[i].calcScore(round);
                std::cout<<"Player "<<i<<" score: "<<players[i].scores[round]<<std::endl;
            }
            std::cout<<"\n";
            distCards(false);
            round += 1;
            roundState = 0;
            turnInd = rand()%4;
            winInd = turnInd;
            if(round>=5){
                roundState = 3;
            }
        }
        GAME_WINDOW.clear();
        
        setPlayerCardsPos(players[playerInd].cards, turnInd==playerInd);
        setGameCards(winInd);
        //  Set bot card position
        
        GAME_WINDOW.draw(tableBackground);

        //  Bot cards show
        drawCards(GAME_WINDOW, gameCards);

        //  Player cards show
        drawCards(GAME_WINDOW, players[playerInd].cards );


        GAME_WINDOW.draw(cardBack[0]);
        GAME_WINDOW.draw(cardBack[1]);
        GAME_WINDOW.draw(cardBack[2]);

        ss.str("");
        ss<<players[0].round_score<<"/"<<players[0].bids[round];
        text[0].setText(ss.str());
        ss.str("");
        ss<<players[1].round_score<<"/"<<players[1].bids[round];
        text[1].setText(ss.str());
        ss.str("");
        ss<<players[2].round_score<<"/"<<players[2].bids[round];
        text[2].setText(ss.str());
        ss.str("");
        ss<<players[3].round_score<<"/"<<players[3].bids[round];
        text[3].setText(ss.str());

        for (int i=0 ; i<4; i++)
        {
            text[i].renderText(GAME_WINDOW);
        }
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

    backSprite.setTextureRect(sf::IntRect(0,0,140,190)); 

    //  Scale card back img    
    backSprite.scale(sf::Vector2f(0.5, 0.5));
    return backSprite;
}

void Play::showCardBacks()
{
        //  Get Sprite with specified arguments
    cardBack[0] = getCardBackSprite(cardBackTexture, GAME_WIDTH/2 - 20, 0, false);
    cardBack[1] = getCardBackSprite(cardBackTexture, 100, GAME_HEIGHT/2 - Card::eachCardHeight/2, true);
    cardBack[2] = getCardBackSprite(cardBackTexture, GAME_WIDTH-5, GAME_HEIGHT/2 - Card::eachCardHeight/2, true);

}

void Play::loadPlayerCard(std::vector<Card>& card, sf::Texture& texture)
{
    //load texture for the 13 cards
    for(auto i=card.begin();i!=card.end();++i){
            i->loadTexture(texture);
        }
}

//  Set Bot Card Position
void Play::setGameCards(int startInd)
{
    // loadPlayerCard(b_card, texture);
    
    // std::cout<<startInd;
    for (auto i = gameCards.begin(); i != gameCards.end(); ++i)
    {   
        if (startInd == 0){
            i->sprite.setPosition(sf::Vector2f(GAME_WIDTH/2 - 50 , GAME_HEIGHT/2 - 50));
        }

        else if (startInd == 1)
        {   
            i->sprite.setRotation(90);
            i->sprite.setPosition(sf::Vector2f(GAME_WIDTH/2 , GAME_HEIGHT/2 - Card::eachCardHeight/2));
        }
        else if ( startInd == 2)
        {
            i->sprite.setRotation(-180);
            i->sprite.setPosition(sf::Vector2f(GAME_WIDTH/2 + 75 , GAME_HEIGHT/2 - 25));
        }
        else if ( startInd == 3)
        {
            i->sprite.setRotation(-90);
            i->sprite.setPosition(sf::Vector2f(GAME_WIDTH/2 , GAME_HEIGHT/2 ));
        }
        startInd = (startInd+1)%4;
    }

}

//  Show player cards
void Play::setPlayerCardsPos( std::vector<Card> &pCards, bool playerTurn){
    int size = pCards.size();
    for(auto i=pCards.begin();i!=pCards.end();++i)
    {
        //  define postion for player cards
        if (i->playable && playerTurn)
            i->sprite.setPosition(sf::Vector2f(GAME_WIDTH/2-((size-1)*55+112)/2 + 55*(i-pCards.begin()), GAME_HEIGHT-180));
        else
            i->sprite.setPosition(sf::Vector2f(GAME_WIDTH/2-((size-1)*55+112)/2 + 55*(i-pCards.begin()), GAME_HEIGHT-150));
    }
}

void Play::drawCards(sf::RenderWindow &window, std::vector<Card> &pCards){
    
    for(auto i=pCards.begin();i<pCards.end();++i)
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

    BID_WINDOW.create(sf::VideoMode(430, 210), "Call Your Bid", sf::Style::None);
    BID_WINDOW.setFramerateLimit(30);

    	//	Load texture for background image and load img
	sf::Texture texture;
	if (!texture.loadFromFile("src/Images/bidWindowBackground.jpg"))
	{
		std::cout << "Error loading bid window background image.";
	}
	sf::Sprite bidWinBackground(texture);
	bidWinBackground.scale(sf::Vector2f(0.8, 0.8));


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
                        std::cout << "Bid entered = " << num<<"\n";   //  This is the user input bid no
                        //  Close bid window only for bid range 1 - 8
                        BID_WINDOW.close();
                        return num;
                    }
                }
        }
        BID_WINDOW.clear();
        BID_WINDOW.draw(bidWinBackground);
        BID_WINDOW.display();
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

void Play::distCards(bool createPlayer){
    std::vector<Card> allCards; //It is a vector for all 52 cards
    std::vector<Card> cardn;
//     std::vector<Card>::iterator f;

    // Initializing all the cards and adding to allCards
    for(int i=0;i<4;i++){
        for(int j = 0;j<13;j++){
            allCards.push_back(Card(i,j));
        }
    }

    std::random_shuffle(allCards.begin(),allCards.end());
    
	if (!cardFrontTexture.loadFromFile("src\\Images\\Cards\\cardFront\\all_cards.png"))
	{
		std::cout << "Error loading card image.";
	}
    srand(time(0));
    if (createPlayer){
        players.clear();}
    for(int i=0;i<4;i++){
        cardn.assign(allCards.begin()+13*i,allCards.begin()+13*(i+1));
        sort(cardn.begin(),cardn.end(),compare);
        if (createPlayer){
            players.push_back(Player(cardn,i==playerInd));}
        else{
            players[i].cards.assign(cardn.begin(),cardn.end());
            }
        players[i].round_score = 0;
    }
    loadPlayerCard(players[playerInd].cards,cardFrontTexture);
}
