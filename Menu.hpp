#pragma once

#include <SFML/Graphics.hpp>
#define MAX_NUMBER_OF_LABELS 3

class Menu
{
	public:
		// Constructor
		Menu(float width, float height);
		//	Destructor
		~Menu();

		void draw(sf::RenderWindow &window);
		void moveUp();
		void moveDown();
		int getPressedLabel();

	private:
		int selectedLabelIndex;
		sf::Font font;
		sf::Text menu[MAX_NUMBER_OF_LABELS];
};
