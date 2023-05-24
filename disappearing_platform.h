#pragma once
#include "platform.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class disappearing_platform : public platform
{
public:
	disappearing_platform(sf::Vector2f switch_speed2 ,sf::Vector2f size, sf::Vector2f position);
	~disappearing_platform(); 
	virtual void update(); 
private:

private:
	sf::Vector2f switch_speed; 
	sf::Clock clock; 
	sf::Time czas; 
	sf::Vector2f pozycja; 
	float offset; 

};

