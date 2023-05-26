#include "bomb.h"

bomb::bomb(sf::Vector2f pos)
{
	if (!tekstura_wybuch.loadFromFile("assets/Explosion.png"))
	{
		std::cout << "Nie za³adowano  tekstury wybuchu" << std::endl;
	}
	if (!tekstura.loadFromFile("assets/bomb.png"))
	{
		std::cout << "Nie za³adowano grafiki bomby" << std::endl;
	}
	else
	{
		std::cout << "Tworze bombe" << std::endl; 
	}
	setPosition(pos); 
	setTexture(tekstura);
	setScale(0.5, 0.5); 
	blokada_zegar = false; 
}

bomb::~bomb()
{
	std::cout << "Usuwam bombe" << std::endl; 
}

void bomb::update(bool boom , sf::Clock clock )
{
	if (boom == true)
	{
		setTexture(tekstura_wybuch);
		setScale(sf::Vector2f(2, 2)); 
		animate_boom(clock);
	}
}

void bomb::animate_boom(sf::Clock clock) // animacja wybuchu 
{
		czas = clock.getElapsedTime();
		if (czas.asSeconds() < 0.1)
			setTextureRect(sf::IntRect(30, 20, 40, 100));		
		else if (czas.asSeconds() < 0.2)
			setTextureRect(sf::IntRect(80, 20, 100, 120));
		else if (czas.asSeconds() < 0.4)
			setTextureRect(sf::IntRect(180, 20, 100, 120));
		else if (czas.asSeconds() < 0.6)
			setTextureRect(sf::IntRect(280, 20, 100, 120));
		else if (czas.asSeconds() < 0.8)
			setTextureRect(sf::IntRect(380, 00, 100, 120));
		else if (czas.asSeconds() < 1)
			setTextureRect(sf::IntRect(480, 00, 100, 120));
		else if (czas.asSeconds() < 1.2)
			setTextureRect(sf::IntRect(580, 00, 90, 120));
		else if (czas.asSeconds() < 1.4)
			setTextureRect(sf::IntRect(680, 00, 90, 120));
		else if (czas.asSeconds() < 1.6)
			setTextureRect(sf::IntRect(780, 00, 90, 120));
		else if (czas.asSeconds() < 1.8)
			setTextureRect(sf::IntRect(880, 00, 90, 120));
		else if (czas.asSeconds() < 2)
			setTextureRect(sf::IntRect(980, 00, 90, 120));
}
