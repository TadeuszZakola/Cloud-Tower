#include "player.h"
#include "Game.h"

player::player(int klasa_gracza, sf::Vector2f pos) 
{
	if (klasa_gracza == 1)
	{
		if (!klasa.loadFromFile("assets/warpgal-shooting-sheet-alpha.png"))
		{
			std::cout << "Nie za³adowano grafiki gracza" << std::endl;
		}
	}
	setPosition(pos);
	setTexture(klasa);
	setScale(2, 2);
	setTextureRect(sf::IntRect(0, 0, 48, 48));
	grawitacja = sf::Vector2f(0, 0.3); 
	stan = alive; 
	score = 0; 
}
void player::update(sf::RenderWindow* okno, std::vector<platform*> platformy, std::vector<bomb*> bomby , std::vector<coin*> *monety)
{    //  // sprawdzilismy w funckji collision czy kolizja wystepuje z ruchom¹ platforma. jezeli tak to move_platforma jest rozna od zera a za razem gracz "jedzie" z platforma
	move_x(platformy);
	move_y(platformy);
	if_przegrana(bomby); // sprawdzanie czy gracz zyje 
	animate(); // po zakonczonym ruszaniu gracza animujemy go na podstawie zmienionej pozycji 
	add_score(monety); // sprawdza kolizje z monetami nastepnie zwieksza wynik gracza 
	draw(okno);
}

sf::Vector2f player::sprawdz_klaw() // na podstawie inputu gracza rusza go w osi X
{
	sf::Vector2f predkosc(0, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		predkosc.x = -3;
		kierunek = left; 
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		predkosc.x = 3;
		kierunek = right; 
	}
	else
	{
		kierunek = stand; 
	}
	return predkosc;
}

void player::draw(sf::RenderWindow* okno)
{
	okno->draw(*this);
}

bool player::collision(std::vector<platform*> platformy, bool blokada) // funkcja sprawdzajaca kolizje miedzy graczem a obiektami 
{
	move_platform = sf::Vector2f(0, 0); 
	bool kolizja = false; 
	for (auto platforma : platformy)
	{	
		 if (getGlobalBounds().intersects(platforma->getGlobalBounds()) && v_gracz.y >= 0 && getGlobalBounds().top + getGlobalBounds().height - 19*grawitacja.y - 3 <= platforma->getGlobalBounds().top)
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


void player::if_przegrana(std::vector<bomb*> bomby) // sprwadza kolizje miedzy graczem a bombami
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

void player::animate() // funkcja animate pobiera kierunek ruchu gracza , tzn left lub right nastepnie szykuje klatki animacji 
{
	time = clock.getElapsedTime(); 
	if (kierunek == right || kierunek == left) // ruch lewo prawo
	{
          if (time.asSeconds() > 1.5)
		       clock.restart(); 
		if (time.asSeconds() < 0.15)
		setTextureRect(sf::IntRect(96, 0, 48, 48));
		else if (time.asSeconds() < 0.3)
			setTextureRect(sf::IntRect(140, 0, 48, 48));
		else if (time.asSeconds() < 0.45)
			setTextureRect(sf::IntRect(192, 0, 48, 48));
		else if (time.asSeconds() < 0.6)
			setTextureRect(sf::IntRect(240, 0, 48, 48));
			else if (time.asSeconds() < 0.75)
			setTextureRect(sf::IntRect(288, 0, 48, 48));
			else if (time.asSeconds() < 0.9)
		setTextureRect(sf::IntRect(336, 0, 48, 48));
			else if (time.asSeconds() < 1.05)
		setTextureRect(sf::IntRect(384, 0, 48, 48));
			else if (time.asSeconds() < 1.2)
		setTextureRect(sf::IntRect(432, 0, 48, 48));
			else if (time.asSeconds() < 1.35)
		setTextureRect(sf::IntRect(480, 0, 48, 48)); 
			else if (time.asSeconds() < 1.5)
		setTextureRect(sf::IntRect(528, 0, 48, 48));
		if (kierunek == left && getScale().x == 2) // obracanie sprita w lewo 
		{
			setScale(-2, 2);
			move(96, 0); // aby sie gracz nie teleportowal trzeba go ruszyc o dwukrotnosc szerokosci sprita 
		}
		else  if (kierunek == right && getScale().x == -2) // obracanie sprita w prawo 
		{
			setScale(2, 2);
			move(-96, 0); // tak samo tylko  w druga strone 
		}
			
	}
	else if(kierunek == stand) // gdy stoi 

	{
		setTextureRect(sf::IntRect(0, 0, 48, 48));
	}
	if (kierunek == fall) // gdy spada
	{
		setTextureRect(sf::IntRect(140, 0, 48, 48));
	}


}

void player::move_x(std::vector<platform*> platformy)
{
	pozycja = getPosition();
	move(sprawdz_klaw());// ruch jest rozpatrywany osobno w plaszczyznie x oraz y , tutaj jest plaszczyzna X 
	move(move_platform);
	if (collision(platformy, true) == true) // najpierw ruszamy w plaszyznie x , sprawdzamy kolizje. jezeli wystapila to cofamy obiekt
	{                                       // do momentu przed kolizja 
		setPosition(pozycja);

	}
	v_gracz.x = 0; // po zakonczonym ruchu zerujemy predkosc gracza na osi x 
}

void player::move_y(std::vector<platform*> platformy)
{
	pozycja = getPosition();
	if (v_gracz.y < 8)
	{
		v_gracz += grawitacja;
	}
	move(v_gracz);// tutaj to samo tylko dla osi y 
	move(move_platform);
	if (collision(platformy, false) == true)
	{
		setPosition(pozycja);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			v_gracz.y -= 22;
		}
	}
	else if (v_gracz.y > 0)
	{
		kierunek = fall; // jezeli kolizja nie wystapila oraz predkosc gracza jest wieksza od zera to znaczy , ze gracz spada
	}
}

void player::add_score(std::vector<coin*> *monety)
{
	for (auto& m : *monety)
	{
		if (this->getGlobalBounds().intersects(m->getGlobalBounds()))
		{
			score++; 
			auto element = std::find(monety->begin(), monety->end(), m);
			delete(m);
			monety->erase(element);
		}
	}
}

int player::return_score()
{
	return score;
}
