#include "Play.hpp"


void Play::playGame(){ 

    //  All the rough game code remains here

    std::vector<Card> allCards; //It is a vector for all 52 cards
    std::vector<Card> card1;
    std::vector<Card>::iterator f;

    // Initializing all the cards and adding to allCards(which is an array or collection)
    for(int i =0;i<4;i++){
        for(int j = 0;j<13;j++){
            allCards.push_back(Card(i,j));
        }
    }
    // shuffling cards (doesn't work) currently
    std::random_shuffle(allCards.begin(),allCards.end());
    
    
    sf::Texture texture;
	if (!texture.loadFromFile("src\\Images\\Cards\\cardFront\\all_cards.png"))
	{
		std::cout << "Error loading card image.";
	}

    //  Load texture for card back
	if (!cardBackTexture.loadFromFile("src\\Images\\Cards\\cardBack\\cardBack_red1.png"))
	{
		std::cout << "Error loading cardBack image.";
	}

    //  Array with 3 elements containing cardBack at 3 positions

    showCardBacks();

    // seperate first 13 cards
    card1.assign(allCards.begin(),allCards.begin()+13);
    
    //load texture for the 13 cards
    for(auto i=card1.begin();i!=card1.end();++i){
            i->loadTexture(texture);
        }
    
    //create a player using those cards
    Player p1(card1, true);

    //display players first card
    sf::RenderWindow GAME_WINDOW;;
    GAME_WINDOW.create(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), "Play Call Break");
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
						}
                    }
        }

        GAME_WINDOW.clear();
        // window.draw(p1.cards[0].sprite); 
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

    return backSprite;
}

void Play::showCardBacks()
{
        //  Get Sprite with specified arguments
    cardBack[0] = getCardBackSprite(cardBackTexture, GAME_WIDTH/2 - 140/2, 0, false);
    cardBack[1] = getCardBackSprite(cardBackTexture, 190, GAME_HEIGHT/2 - 190/2, true);
    cardBack[2] = getCardBackSprite(cardBackTexture, GAME_WIDTH, GAME_HEIGHT/2 - 190/2, true);


}