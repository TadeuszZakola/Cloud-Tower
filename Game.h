#pragma once
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "platform.h"
#include "moving_platform.h"
#include "disappearing_platform.h"
class Game
{ public:
	Game();
	void play();
	void draw_tlo(sf::RenderWindow* window);
private:
	// funkcje generujace 
	void generate_platform(); // generuje platformy z szansa na wygenerowanie monety na jednej z nich
	void generate_bombs();
	float generate_rand_dist(); // generuje dystans w okreslonym przedziale , aby gracz doskoczyl do kazdej platformy 

	// funkcje przygotowywujace
	void ready_game();
	void ready_background_texture();

	// funkcje updatujace
	void update_all(player& play, const sf::Time& elapsed); // updatuje kazda platforme 
    void death(player& play ,  sf::RenderWindow* window); // ekran smierci 
    void move_all(sf::Vector2f ruch); // rusza wszystkie platformy 
	void next_screen(player &play, const sf::Time& elapsed); // przygotowanie nastepnej klatki 
	void pauza(sf::RenderWindow *window,player& gracz); // ekran pauzy 

	// funkcje rysujace	
	//void draw_tlo(sf::RenderWindow *window); 	
	void draw_all(sf::RenderWindow* window);	

private:
	sf::RenderWindow *window;
	// vectory obiektow na planszy 
	std::vector<platform*> platformy;
	std::vector<bomb*> bomby; 
	std::vector<coin*> *monety; 

	// zmienne czasowe do animacji bomby
	sf::Clock bomb_clock; 
	sf::Time bomb_time; 

	// tekstury oraz sprite'y dla tla
	sf::Texture tlo1; 
	sf::Texture tlo2;
	sf::Texture tlo3;
	sf::Texture tlo4;
	sf::Texture tlo5;
	sf::Sprite tlo_s;
	sf::Sprite tlo_s2;
	sf::Sprite tlo_s3;
	sf::Sprite tlo_s4;
	sf::Sprite tlo_s5;

	// glowna zmienna event
	sf::Event event;

	// zmienne dodatkowe
	sf::Clock clock;
	bool pauza_bool;
	float game_speed; 
};

