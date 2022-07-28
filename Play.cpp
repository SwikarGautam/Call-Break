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
		std::cout << "Error loading menu background image.";
	}

    // seperate first 13 cards
    card1.assign(allCards.begin(),allCards.begin()+13);
    
    //load texture for the 13 cards
    for(auto i=card1.begin();i!=card1.end();++i){
            i->loadTexture(texture);
        }
    
    //create a player using those cards
    Player p1(card1, true);

    //display players first card
    sf::RenderWindow window;
    window.create(sf::VideoMode(800,600), "call");
    while (window.isOpen())
    {
		sf::Event event;
		while (window.pollEvent(event))
		{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
        }

        window.clear();
        window.draw(p1.cards[0].sprite); 
        window.display();     
    }

}

