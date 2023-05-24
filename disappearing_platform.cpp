#include "disappearing_platform.h"
disappearing_platform::disappearing_platform(sf::Vector2f switch_speed2 , sf::Vector2f size, sf::Vector2f position) : platform(size, position)
{
	switch_speed = switch_speed2; 
	pozycja = position; 
	setFillColor(sf::Color::Magenta); 
	std::cout << "Tworze platforme znikajaca" << std::endl; 
	offset = rand() % 20 / 20; 
	clock.restart(); 
}

disappearing_platform::~disappearing_platform()
{
	std::cout << "Usuwam znikajaca platforme" << std::endl; 
}

void disappearing_platform::update() // platforma znika w okreslonych interwalach , na okreslony czas , oraz z okreslonym przesunieciem pierwotnym
{
	if (czas.asSeconds() == offset)
	{
		clock.restart(); 
	}
	czas = clock.getElapsedTime(); 
	if (czas.asSeconds() > switch_speed.x)
	{
		if(getPosition().x > 0)
		move(-5000,0); 
		if (czas.asSeconds() > switch_speed.x + switch_speed.y)
		{
			move(5000,0); 
			clock.restart(); 
		}
	}
	
}

