#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "platform.h"
#include "moving_platform.h"
class bomb : public sf::Sprite
{
public:
	bomb(sf::Vector2f pos); 
	~bomb(); 
    //funkcje 
	void update(bool boom , sf::Clock clock ); 
private:
	void animate_boom(sf::Clock clock); // animcja wybuchu 
private:
	//tekstury 
	sf::Texture tekstura;
	sf::Texture tekstura_wybuch; 
	sf::Sprite sprite; 
	//czas
	sf::Time czas;
	bool blokada_zegar; 

};

