#include "player.h"
#include "Game.h"

player::player(int klasa_gracza, sf::Vector2f pos) 
{
	if (klasa_gracza == 1)
	{
		if (!klasa.loadFromFile("assets/character.png"))
		{
			std::cout << "Nie za³adowano grafiki gracza" << std::endl;
		}
	}
	setPosition(pos);
	setTexture(klasa);
	setScale(2, 2);
	setTextureRect(sf::IntRect(110, 0, 30, 37));
	grawitacja = sf::Vector2f(0, 0.3); 
	stan = alive; 
}

sf::Vector2f player::sprawdz_klaw()
{
	sf::Vector2f predkosc(0, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		predkosc.x = -2;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		predkosc.x = 2;
	}
	return predkosc;
}

void player::draw(sf::RenderWindow& okno)
{
	okno.draw(*this);
}

void player::update(sf::RenderWindow& okno , std::vector<platform*> platformy, std::vector<bomb*> bomby)
{    //  // sprawdzilismy w funckji collision czy kolizja wystepuje z ruchom¹ platforma. jezeli tak to move_platforma jest rozna od zera a za razem gracz "jedzie" z platforma
	pozycja = getPosition(); 
	move(sprawdz_klaw()) ;// ruch jest rozpatrywany osobno w plaszczyznie x oraz y , tutaj jest plaszczyzna X 
	move(move_platform); 
	if (collision(platformy, true) == true) // najpierw ruszamy w plaszyznie x , sprawdzamy kolizje. jezeli wystapila to cofamy obiekt
	{                                       // do momentu przed kolizja 
		setPosition(pozycja); 
		
	}	
	pozycja = getPosition();
	if (v_gracz.y < 8)
	{
		v_gracz += grawitacja; 
	}
	move(v_gracz);// tutaj to samo tylko dla osi y 
	move(move_platform); 
	if (collision(platformy, false ) == true) 
	{
		setPosition(pozycja);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			v_gracz.y -= 22;
		}
	}
	v_gracz.x = 0;
	if_przegrana(bomby); // sprawdzanie czy gracz zyje 
	draw(okno);
}
bool player::collision(std::vector<platform*> platformy, bool blokada)
{
	move_platform = sf::Vector2f(0, 0); 
	bool kolizja = false; 
	for (auto platforma : platformy)
	{	
		 if (getGlobalBounds().intersects(platforma->getGlobalBounds()) && v_gracz.y >= 0 && getGlobalBounds().top + getGlobalBounds().height - 19*grawitacja.y - 4 <= platforma->getGlobalBounds().top)
		{
			move_platform = platforma->return_speed();
			kolizja = true;	
		}
		 else if (getGlobalBounds().intersects(platforma->getGlobalBounds()) && v_gracz.y < 0)
		 {
			 move(0, -0.1); // debugging , tzn jezeli gracz znajduje sie w platformie oraz spada to zamiast zatrzymac sie to nie zablokuje sie 
		 }	
	}
	return kolizja; 
}


void player::if_przegrana(std::vector<bomb*> bomby)
{   
	if (getGlobalBounds().top + getGlobalBounds().height >= 1000)
	{
		stan = dead; 
	}
	for (auto x : bomby)
	{
		if (getGlobalBounds().intersects(x->getGlobalBounds()))
		{
			stan = dead; 
		}
	}
}

player::status player::get_status()
{
	return stan; 
}