#include "moving_platform.h"

moving_platform::moving_platform(sf::Vector2f speed, sf::Vector2f size, sf::Vector2f position) : platform(size , position)
{
	platform_speed = speed; 
	//setFillColor(sf::Color::Blue);
	setOutlineColor(sf::Color::Blue);
	initial_pos = position; 
	std::cout << "Tworze platforme ruszajaca" << std::endl; 
}

moving_platform::~moving_platform()
{
	std::cout << "Usuwam ruszajaca platforme" << std::endl; 
}

void moving_platform::update()
{
	//std::cout << "jestem pokrewny" << std::endl;
	move_p();
}

sf::Vector2f moving_platform::return_speed()
{ 
	return platform_speed; 
}



void moving_platform::move_p()
{
	if (getGlobalBounds().left <= initial_pos.x -400)
	{
		platform_speed.x = -platform_speed.x;
	}
	if (getGlobalBounds().left + getGlobalBounds().width >= initial_pos.x + 400)
	{
		platform_speed.x = -platform_speed.x;
	}
	move(platform_speed); 
}
