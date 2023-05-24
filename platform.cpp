#include "platform.h"

 platform::platform(sf::Vector2f size , sf::Vector2f position) : sf::RectangleShape(size)
{
    setPosition(position);
    //setFillColor(sf::Color::Red);
    
        if (!tekstura.loadFromFile("assets/cloud-platform.png")) // tekstura pozioma
        {
            std::cout << "nie mozna zaladowac platformy" << std::endl; 
        }
        else
            std::cout << "Tworze Platforme" << std::endl;
        sprite.setTexture(tekstura);
        sprite.setTextureRect(sf::IntRect(200, 200, 300, 200));
        setTextureRect(sf::IntRect(0, 0, tekstura.getSize().x / 5, tekstura.getSize().y / 10));
        setTexture(&tekstura, true);
        setTextureRect(sf::IntRect(0, 0, size.x * 2, size.y * 2));
       // setFillColor(sf::Color::Red);

}

 void platform::update()
 {
 }

 sf::Vector2f platform::return_speed()
 {
     return sf::Vector2f(0, 0); 
 }

 void platform::rusz(sf::Vector2f speed)
 {
     move(speed); 
 }

 platform::~platform()
 {
     std::cout << "usuwam obiekt" << std::endl; 
 }



