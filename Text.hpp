//	Text.hpp
//	Header file for Text.cpp


#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.hpp"



class Text
{
	public:

        void loadText(std::string score, float x, float y);
		void renderText(sf::RenderWindow& window);
		void setText(std::string);
        

	private:
		sf::Font font;
		sf::Text anyText;
		std::string text_Info ;
};
