#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Game.h"
#include <vector>
#define MAX_NUMBER_OF_BUTTONS 3

class MainMenu
{
public:
	void Play(sf::RenderWindow* window , Game gra);//pêtla menu g³ównego
	MainMenu(float width, float height);//konstruktor menu, tworzenie przycisków
	~MainMenu();
private:
	void draw(sf::RenderWindow *window);//rysowanie przycisków i tytu³u
	void MoveUp();//przesuwanie w górê
	void MoveDown();//przesuwanie w dó³
	int GetPressedItem();//getter selectedItemIndex
	//void draw_tlo(sf::RenderWindow*window);
	

	//deklaracje elementów sk³adaj¹cych siê na przycisk
	enum buttons;
	int selectedItemIndex;
	sf::Text buttontext[MAX_NUMBER_OF_BUTTONS];
	sf::Text title;
	sf::Font font;
	sf::RectangleShape button[MAX_NUMBER_OF_BUTTONS];
	
};
