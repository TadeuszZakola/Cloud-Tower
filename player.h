#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "platform.h"
#include "moving_platform.h"
#include "bomb.h" 
class player : public sf::Sprite 
{public:
	enum status
	{
		dead,
		alive
	};
public:
	player(int klasa, sf::Vector2f pos); 		
	void update(sf::RenderWindow& okno, std::vector<platform*> platformy, std::vector<bomb*> bomby); // updatuje pozycje oraz predkosc gracza
	status get_status(); // zwraca enuma stan , tzn dead lub alive
private:
	bool collision(std::vector<platform*> platformy, bool blokada); // kolizja 
	sf::Vector2f sprawdz_klaw(); // sprawdza wcisniete klawisze 
	void draw(sf::RenderWindow& okno);	// rysuje gracza , jest elementem funckji update
    void if_przegrana(std::vector<bomb*> bomby); // sprawdza czy grac zyje czy nie 
private:
	sf::Vector2f v_gracz; // predkosc gracza
	sf::Vector2f grawitacja; // grawitacja
	sf::Vector2f pozycja; // pozycja gracza
	sf::Vector2f move_platform; // rusza gracza o predkosc platformy na ktorej stoi 
	// tekstury gracza 
	sf::Sprite gracz; 
	sf::Texture klasa;
	//status gracza 
	status stan; 
};

