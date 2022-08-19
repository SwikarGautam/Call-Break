//	Credits.cpp


#include "Credits.hpp"
#include "Menu.hpp"

Credits::Credits()
{
	//	Specify positions for info-text
	float credits_X = 950/2 - 80;	//	Manually set 800

	//	Load
	if (!font.loadFromFile("src/Font/StreamerDemo.otf"))
	{
		//	Error handling
		std::cout << "Error loading font." << std::endl;
	}

	//	Loading credits Text 
	//	You can set credit texts attributes here
	creditsText.setFont(font);
	creditsText.setCharacterSize(24);
	creditsText.setFillColor(sf::Color::White);
	creditsText.setString(credits_Info);

		//	Loading Escape Text 
	escapeText.setFont(font);
	escapeText.setCharacterSize(24);
	escapeText.setFillColor(sf::Color::White);
	escapeText.setString(escLetter);

	// //	Specify position for label dynamically
	creditsText.setPosition(sf::Vector2f(credits_X, 0));

	// Postion for esc
	escapeText.setPosition(sf::Vector2f(0, 0));

}


void Credits::renderCredits(sf::RenderWindow& window){

	//	Credits Text motion Setting
	creditsText.move(0, 0.3f);
	if (creditsText.getPosition().y > (600))	//	Manually assigned 600
	{
		creditsText.setPosition(950 / 2 - 80, 0);	//	Manually assigned 800
	}

}

void Credits::openCreditsWindow(sf::RenderWindow & CREDITS_WINDOW){
		//	Show credits when 'Enter' pressed in Credits

	// sf::RenderWindow CREDITS_WINDOW;

	//	Create new Credits window
	// CREDITS_WINDOW.create(sf::VideoMode(950, 600), "Credits");
	// CREDITS_WINDOW.setFramerateLimit(60);
	//	Load texture for credits background
	sf::Texture texture;
	if (!texture.loadFromFile("src/Images/creditsBackground.jpg"))
	{
		std::cout << "Error loading menu background image.";
	}
	sf::Sprite creditsBackground(texture);

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time TimeConstant = sf::seconds(1.f/60.f);

	//	Game loop
	while (CREDITS_WINDOW.isOpen())
	{
		sf::Event event;
		while (CREDITS_WINDOW.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				CREDITS_WINDOW.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				//	Esc  key pressed
				if (event.key.code == sf::Keyboard::Escape)
				{
					//	Escape key pressed closes credits window
					// CREDITS_WINDOW.close();
					// Menu menu;
					// menu.openMainMenuWindow();
					return ;
				}
			}
		}

		CREDITS_WINDOW.draw(creditsBackground);
		CREDITS_WINDOW.draw(creditsText);
		CREDITS_WINDOW.draw(escapeText);

		//	Render text
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimeConstant){
			timeSinceLastUpdate -= TimeConstant;
			renderCredits(CREDITS_WINDOW);}

		//	end of current frame
		CREDITS_WINDOW.display();
	}
}



