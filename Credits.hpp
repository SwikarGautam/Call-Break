//	Credits.hpp
//	Header file for Credits.cpp


#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

enum MENU_OPTIONS{
	PLAY,
	CREDITS,
	QUIT
};

class Credits
{
	public:
		//	Credits animation
		//	Constructor
		Credits(float width);
		void renderCredits(sf::RenderWindow& window);

	private:
		sf::Font font;
		sf::Text creditsText;
		sf::Text escapeText;
		//	Credits text to be displayed
		std::string credits_Info ="Developed By \n Sujan Koirala\nSwikar Gautam";
		std::string escLetter  = "ESC\n<";
};
