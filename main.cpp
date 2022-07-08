#include <SFML/Graphics.hpp>
// #include <SFML/Window.hpp>
#include <iostream>

// class Player{
// private:
// int x;
// public:
    

// };


int main()
{
    
    sf::RenderWindow window(sf::VideoMode(1600,1080),"My window");

    sf::RectangleShape rect;
    sf::Vector2f rectPosition(600,350);

    rect.setPosition(rectPosition);
    rect.setSize(sf::Vector2f(100,100));

    sf::Texture texture;
    texture.loadFromFile("src/images/cards/cardFront/all_cards.png");
    texture.setSmooth(true);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    int x = 140;
    int y = 190;
    sprite.setTextureRect(sf::IntRect(x,y,140,190));
    window.setFramerateLimit(20);
    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){

            if (event.type == sf::Event::Closed){
                window.close();
            }
        
            if(event.type == sf::Event::MouseButtonPressed){
                rectPosition.x = event.mouseButton.x;
                rectPosition.y = event.mouseButton.y;
            }

        // rect.setPosition(rectPosition);
        
        sprite.setScale(4.f,2.f);
        sprite.setRotation(45.f);
        sprite.setPosition(rectPosition);
        window.clear(sf::Color(0,200,75));
        // window.draw(rect);
        window.draw(sprite);
        window.display();

        }
    }
    return 0;
}