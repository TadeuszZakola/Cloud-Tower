#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Game.h"

#define MAX_NUMBER_OF_PAUSE_BUTTONS 2
class PauseMenu
{
public:
	PauseMenu(float width,float height);
	void draw(sf::RenderWindow*window);
	void MoveUp();
	void MoveDown();
	void Play(sf::RenderWindow*window);
	int GetPressedItem() { return selectedItemIndex; }
private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text buttontext[MAX_NUMBER_OF_PAUSE_BUTTONS];
	sf::Text title;
	sf::RectangleShape button[MAX_NUMBER_OF_PAUSE_BUTTONS], pauseBackground;

};

