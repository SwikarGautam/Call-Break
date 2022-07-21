#include "Menu.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	//	Create window
	sf::RenderWindow window;
	window.create(sf::VideoMode(800, 600), "Call Break");

	//	Menu stuff
	Menu menu(window.getSize().x, window.getSize().y);
	
	//	Loaded texture 
	sf::Texture texture;
	if (!texture.loadFromFile("src/Images/card_background_menu.jpg"))
	{
		std::cout << "Error loading menu background image.";
	}
	sf::Sprite menuBackground(texture);

	//	Game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
				if (event.type == sf::Event::Closed)
				{
					window.close();
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
					switch (menu.getPressedLabel()){
						case 0:
							//	Main Game loop here
							std::cout << "Play pressed";
							break;
						case 1:
							//	Show credits
							std::cout << "Credits pressed";
							break;
						case 2:
							//	Exit from game
							window.close();
							break;
						default:
							std::cout << "Not valid";
							break;
					}
				}

		}
		}
		
		window.clear();
		window.draw(menuBackground);
		//	Draw menu
		menu.draw(window);

		//	end of current frame
		
		window.display();

	}
	return 0;
}