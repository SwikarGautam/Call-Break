//	Credits.cpp


#include "Credits.hpp"

Credits::Credits(float width)
{
	//	Specify positions for info-text
	float credits_X = 800/2 - 80;	//	Manually set 800

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
	creditsText.setFillColor(sf::Color::Black);
	creditsText.setString(credits_Info);

	// //	Specify position for label dynamically
	creditsText.setPosition(sf::Vector2f(credits_X, 0));

}


void Credits::renderCredits(sf::RenderWindow& window){
	//	Draw text into window
	window.draw(creditsText);

	//	Credits Text motion Setting
	creditsText.move(0, 0.7f);
	if (creditsText.getPosition().y > (600))	//	Manually assigned 600
	{
		creditsText.setPosition(800 / 2 - 80, 0);	//	Manually assigned 800
	}

}






