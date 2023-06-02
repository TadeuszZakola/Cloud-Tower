#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "platform.h"
class moving_platform :public platform 
{ public:
	moving_platform(sf::Vector2f speed, sf::Vector2f size, sf::Vector2f position);
	~moving_platform();
	virtual void update();
	virtual sf::Vector2f return_speed();
private:
	void move_p(); 
	sf::Vector2f platform_speed; 
	sf::Vector2f initial_pos; 
};

