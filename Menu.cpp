//	Menu.cpp


#include "Menu.hpp"
#include <iostream>

Menu::Menu(float width, float height)
{
	//	Specify positions for labels
	float labelWidth = width / 8 - 50;

	if (!font.loadFromFile("src/Font/StreamerDemo.otf"))
	{
		//	Error handling
		std::cout << "Error loading font." << std::endl;
	}
	//	Label : PLAY
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("PLAY");
	//	Specify postion for label dynamically
	menu[0].setPosition(sf::Vector2f(labelWidth, height / (MAX_NUMBER_OF_LABELS + 1) * 1));

	//	Label : OPTIONS
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("CREDITS");
	//	Specify postion for label dynamically
	menu[1].setPosition(sf::Vector2f(labelWidth , height / (MAX_NUMBER_OF_LABELS + 1) * 2));

	//	Label : QUIT
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("QUIT");
	//	Specify postion for label
	menu[2].setPosition(sf::Vector2f(labelWidth, height / (MAX_NUMBER_OF_LABELS + 1) * 3));
	selectedLabelIndex = 0;
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_LABELS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::moveUp(){
	if (selectedLabelIndex - 1 >= 0)
	{
		menu[selectedLabelIndex].setFillColor(sf::Color::White);
		selectedLabelIndex--;
		menu[selectedLabelIndex].setFillColor(sf::Color::Red);

	}
}

void Menu::moveDown(){
	if (selectedLabelIndex + 1 <= MAX_NUMBER_OF_LABELS -1)
	{
		menu[selectedLabelIndex].setFillColor(sf::Color::White);
		selectedLabelIndex++;
		menu[selectedLabelIndex].setFillColor(sf::Color::Red);

	}
}

int Menu::getPressedLabel(){
	return selectedLabelIndex;
}

