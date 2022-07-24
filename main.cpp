#include "Menu.hpp"
#include "Credits.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	//	Create window
	sf::RenderWindow MENU_WINDOW, CREDITS_WINDOW;

	//	Main Menu window stuff
	MENU_WINDOW.create(sf::VideoMode(800, 600), "Call Break");
	Menu menu(MENU_WINDOW.getSize().x, MENU_WINDOW.getSize().y);

	//	Credits window stuff
	Credits creditsObj(MENU_WINDOW.getSize().x);

	//	Load texture for background image and load img
	sf::Texture texture;
	if (!texture.loadFromFile("src/Images/card_background_menu.jpg"))
	{
		std::cout << "Error loading menu background image.";
	}
	sf::Sprite menuBackground(texture);

	//	Game loop
	while (MENU_WINDOW.isOpen())
	{
		sf::Event event;
		while (MENU_WINDOW.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				MENU_WINDOW.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				//	Up arrow key pressed
				if (event.key.code == sf::Keyboard::Up)
				{
					//	Shift selected label to down
					menu.moveUp();
				}
				//	Down arrow key pressed
				if (event.key.code == sf::Keyboard::Down)
				{
					//	Shift selected label to down
					menu.moveDown();
				}

				//	Enter key pressed

				if (event.key.code == sf::Keyboard::Return)
				{
					if (menu.getPressedLabel() == 0)
					{
						//	Main Game loop here
						std::cout << "Play pressed";
					}
					if (menu.getPressedLabel() == 1)
					{
						//	Show credits when 'Enter' pressed in Credits


						//	Create new Credits window
						CREDITS_WINDOW.create(sf::VideoMode(800, 600), "Credits");

						//	Load texture for credits background
						sf::Texture texture;
						if (!texture.loadFromFile("src/Images/creditsBackground.jpg"))
						{
							std::cout << "Error loading menu background image.";
						}
						sf::Sprite creditsBackground(texture);

						//	Game loop
						while (CREDITS_WINDOW.isOpen())
						{
							sf::Event event;
							while (CREDITS_WINDOW.pollEvent(event))
							{
								if (event.type == sf::Event::Closed)
								{
									CREDITS_WINDOW.close();
								}
								if (event.type == sf::Event::KeyPressed)
								{
									//	Esc  key pressed
									if (event.key.code == sf::Keyboard::Escape)
									{
										//	Escape key pressed closes credits window
										CREDITS_WINDOW.close();
									}
								}
							}

							CREDITS_WINDOW.draw(creditsBackground);

							//	Render text
							creditsObj.renderCredits(CREDITS_WINDOW);

							//	end of current frame
							CREDITS_WINDOW.display();
						}
					}
					if (menu.getPressedLabel() == 2)
					{
						MENU_WINDOW.close();
						// std::cout << "Quit pressed"<<std::endl;
					}
				}
			}
		}

		MENU_WINDOW.clear();

		//	Draw menu background
		MENU_WINDOW.draw(menuBackground);
		
		//	Member function of menu obj to draw menu
		menu.draw(MENU_WINDOW);

		//	end of current frame

		MENU_WINDOW.display();
	}
	return 0;
}