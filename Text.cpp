//	Text.cpp


#include "Text.hpp"
#include "Menu.hpp"

void Text::loadText(std::string score, float x, float y)
{
    text_Info = score;
	//	Specify positions for info-text
	float credits_X = 800/2 - 80;	//	Manually set 800

	//	Load
	if (!font.loadFromFile("src/Font/FreeSansBold.ttf"))
	{
		//	Error handling
		std::cout << "Error loading font." << std::endl;
	}

	//	Loading credits Text 
	//	You can set credit texts attributes here
	anyText.setFont(font);
	anyText.setCharacterSize(18);
	anyText.setFillColor(sf::Color::White);
	anyText.setString(text_Info);


	// //	Specify position for label dynamically
	anyText.setPosition(sf::Vector2f(x, y));

}


void Text::renderText(sf::RenderWindow& window){
	//	Draw text into window
	window.draw(anyText);

}

void Text::setText(std::string str){
	anyText.setString(str);
}