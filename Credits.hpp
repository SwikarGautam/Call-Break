//	Credits.hpp
//	Header file for Credits.cpp


#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.hpp"



class Credits
{
	public:
		//	Credits animation
		//	Constructor
		Credits();
		void renderCredits(sf::RenderWindow& window);
		void openCreditsWindow();


	private:
		sf::Font font;
		sf::Text creditsText;
		sf::Text escapeText;
		//	Credits text to be displayed
		std::string credits_Info ="Developed By \n Sujan Koirala\nSwikar Gautam";
		std::string escLetter  = "ESC\n";
};
