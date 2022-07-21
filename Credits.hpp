//	Credits.hpp
//	Header file for Credits.cpp


#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

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
		//	Credits text to be displayed
		std::string credits_Info ="Developed By \n Sujan Koirala\nSwikar Gautam";
};
