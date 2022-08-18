//	Menu.hpp
//	Header file for Menu.cpp

#pragma once

#include "Menu.hpp"
#include "Credits.hpp"
#include "Play.hpp"
#include <SFML/Graphics.hpp>
#define MAX_NUMBER_OF_LABELS 3


enum MENU_OPTIONS{
	PLAY,
	CREDITS,
	QUIT
};

class Menu
{
	public:
		// Constructor
		Menu();

		void draw(sf::RenderWindow &window);
		void moveUp();
		void moveDown();
		int getPressedLabel();
		void openMainMenuWindow();
		void closeMainMenuWindow();
		void trackMousePosition(sf::Vector2i mouseCLickPos);
		int clickedMenuValue(sf::Vector2i mouseClickPos);


	private:
		//	Menu window	
		sf::RenderWindow MENU_WINDOW;
		int MENU_WIDTH = 950;
		int MENU_HEIGHT = 600;
		int selectedLabelIndex;
		sf::Font font;
		//	Array of menu elements declared
		sf::Text menu[MAX_NUMBER_OF_LABELS];
};
