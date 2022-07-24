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
	//	Draw text into window
	window.draw(creditsText);

	//	Draw ESC at top into window
	window.draw(escapeText);
	

	//	Credits Text motion Setting
	creditsText.move(0, 0.6f);
	if (creditsText.getPosition().y > (600))	//	Manually assigned 600
	{
		creditsText.setPosition(800 / 2 - 80, 0);	//	Manually assigned 800
	}

}



