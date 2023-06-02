#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "platform.h"
#include "moving_platform.h"
#include "bomb.h" 
#include "coin.h"
class player : public sf::Sprite 
{public:
	enum status // enum musi byc publiczny poniewaz w klasie game sprawdzamy stan gracza
	{           // a z prywatnym enumem nie mozna porownac jego stanu w if-ie
		dead,
		alive
	};
public:
	player(int klasa, sf::Vector2f pos); 		
	void update(sf::RenderWindow* okno, std::vector<platform*> platformy, std::vector<bomb*> bomby , std::vector<coin*> *monety ); // updatuje pozycje oraz predkosc gracza
	status get_status(); // zwraca enuma stan , tzn dead lub alive
	int return_score(); 
private:
	bool collision(std::vector<platform*> platformy, bool blokada); // kolizja 
	void animate(); 
	void move_x(std::vector<platform*> platformy); // ruch w osi x
	void move_y(std::vector<platform*> platformy); // ruch w osi y 
	sf::Vector2f sprawdz_klaw(); // sprawdza wcisniete klawisze 
	void draw(sf::RenderWindow* okno);	// rysuje gracza , jest elementem funckji update
    void if_przegrana(std::vector<bomb*> bomby , std::vector<platform*> platformy); // sprawdza czy grac zyje czy nie 
	void add_score(std::vector<coin*> *monety);
private:
	sf::Vector2f v_gracz; // predkosc gracza
	sf::Vector2f grawitacja; // grawitacja
	sf::Vector2f pozycja; // pozycja gracza
	sf::Vector2f move_platform; // rusza gracza o predkosc platformy na ktorej stoi 
	//
	int score; 
	// tekstury gracza 
	sf::Sprite gracz; 
	sf::Texture klasa;
	//status gracza 
	status stan; 
	// zmienne uzyte do funkcji animate 
	enum travel
	{
		left, right, fall , stand
	};
	sf::Clock clock; 
	sf::Time time; 
	travel kierunek;
};

