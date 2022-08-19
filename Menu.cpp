//	Menu.cpp


#include "Menu.hpp"
#include <iostream>

Menu::Menu()
{
	//	Specify positions for labels
	float labelWidth = MENU_WIDTH / 8 - 50;

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
	menu[0].setPosition(sf::Vector2f(labelWidth, MENU_HEIGHT / (MAX_NUMBER_OF_LABELS + 1) * 1));

	//	Label : OPTIONS
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("CREDITS");
	//	Specify postion for label dynamically
	menu[1].setPosition(sf::Vector2f(labelWidth , MENU_HEIGHT / (MAX_NUMBER_OF_LABELS + 1) * 2));

	//	Label : QUIT
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("QUIT");
	//	Specify postion for label
	menu[2].setPosition(sf::Vector2f(labelWidth, MENU_HEIGHT / (MAX_NUMBER_OF_LABELS + 1) * 3));
	selectedLabelIndex = 0;
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

void Menu::openMainMenuWindow(){
    	//	Create window


	//	Main Menu window stuff
	MENU_WINDOW.create(sf::VideoMode(MENU_WIDTH, MENU_HEIGHT), "Call Break");
	MENU_WINDOW.setFramerateLimit(60);


	//	Load texture for background image and load img
	sf::Texture texture;
	if (!texture.loadFromFile("src/Images/card_background_menu.jpg"))
	{
		std::cout << "Error loading menu background image.";
	}
	sf::Sprite menuBackground(texture);
	menuBackground.scale(sf::Vector2f(1.1, 1.1));

	//	Game loop
	while (MENU_WINDOW.isOpen())
	{
		sf::Event event;
		sf::Vector2i mouseClkPosition = sf::Mouse::getPosition(MENU_WINDOW);
        trackMousePosition(mouseClkPosition);

		while (MENU_WINDOW.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				MENU_WINDOW.close();
			}
			if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
			{
				//	Up arrow key pressed
				if (event.key.code == sf::Keyboard::Up)
				{
					//	Shift selected label to down
					moveUp();
				}
				//	Down arrow key pressed
				if (event.key.code == sf::Keyboard::Down)
				{
					//	Shift selected label to down
					moveDown();
				}

				//	Enter key pressed
				
				sf::Vector2i mouseClickPos = sf::Mouse::getPosition(MENU_WINDOW);
				

				if (event.key.code == sf::Keyboard::Return || sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (getPressedLabel() == PLAY || clickedMenuValue(mouseClickPos) == PLAY)	//	PLAY -> 0 from enum MENU_OPTIONS
					{

						//	Main Game
						//	First close Main Menu
						// closeMainMenuWindow();
						Play play;
						play.playGame(MENU_WINDOW);
					}
					if (getPressedLabel() == CREDITS || clickedMenuValue(mouseClickPos) == CREDITS)	//	CREDITS -> 1
					{
						//	Show credits when 'Enter' pressed in Credits
						//	First close Main Menu
						// closeMainMenuWindow();
						Credits credits;
						credits.openCreditsWindow(MENU_WINDOW);
					}
					if (getPressedLabel() == QUIT || clickedMenuValue(mouseClickPos) == QUIT)
					{
						MENU_WINDOW.close();
					}
				}
			}
		}

		MENU_WINDOW.clear();

		//	Draw menu background
		MENU_WINDOW.draw(menuBackground);
		
		//	Member function of menu obj to draw menu
		draw(MENU_WINDOW);

		//	end of current frame

		MENU_WINDOW.display();
	}
}

void Menu::closeMainMenuWindow(){
	MENU_WINDOW.close();
}

void Menu::trackMousePosition(sf::Vector2i mouseClickPos) {


	//For Play
	if (mouseClickPos.x <= menu[0].getPosition().x + 100 && mouseClickPos.x >= menu[0].getPosition().x && mouseClickPos.y <= menu[0].getPosition().y + 30 && mouseClickPos.y >= menu[0].getPosition().y) {
		//menu[selectedLabelIndex].setFillColor(sf::Color::White);
		menu[1].setFillColor(sf::Color::White);
		menu[2].setFillColor(sf::Color::White);
		selectedLabelIndex = 0;
		menu[0].setFillColor(sf::Color::Red);
	}

	//For credits
	if (mouseClickPos.x <= menu[1].getPosition().x + 200 && mouseClickPos.x >= menu[1].getPosition().x && mouseClickPos.y <= menu[1].getPosition().y + 50 && mouseClickPos.y >= menu[1].getPosition().y) {
		menu[0].setFillColor(sf::Color::White);
		menu[2].setFillColor(sf::Color::White);
		selectedLabelIndex = 1;
		menu[1].setFillColor(sf::Color::Red);
	}

	//For exit
	if (mouseClickPos.x <= menu[2].getPosition().x + 120 && mouseClickPos.x >= menu[2].getPosition().x && mouseClickPos.y <= menu[2].getPosition().y + 30 && mouseClickPos.y >= menu[2].getPosition().y) {
		//menu[selectedLabelIndex].setFillColor(sf::Color::White);
		menu[0].setFillColor(sf::Color::White);
		menu[1].setFillColor(sf::Color::White);
		selectedLabelIndex = 2;
		menu[2].setFillColor(sf::Color::Red);
	}
}

int Menu::clickedMenuValue(sf::Vector2i mouseClickPos) {

	if (mouseClickPos.x <= menu[0].getPosition().x + 50 && mouseClickPos.x >= menu[0].getPosition().x && mouseClickPos.y <= menu[0].getPosition().y + 30 && mouseClickPos.y >= menu[0].getPosition().y) {
		return 0;
	}
		
	else if (mouseClickPos.x <= menu[1].getPosition().x + 80 && mouseClickPos.x >= menu[1].getPosition().x && mouseClickPos.y <= menu[1].getPosition().y + 50 && mouseClickPos.y >= menu[1].getPosition().y) {
		return 1;
	}
	else if (mouseClickPos.x <= menu[2].getPosition().x + 50 && mouseClickPos.x >= menu[2].getPosition().x && mouseClickPos.y <= menu[2].getPosition().y + 30 && mouseClickPos.y >= menu[2].getPosition().y) {
		return 2;
	}
	else {
		return 100;
	}
	
}