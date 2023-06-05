#include "Game.h"
#include "player.h"
#include "coin.h"
#include <algorithm>
#include <vector>
#include "MainMenu.h"
#include "PauseMenu.h"
Game::Game()
{
	std::cout << "Witamy w cloud TOWER!" << std::endl; 
	std::cout << "Wykonali :" << std::endl; 
	std::cout << "Aby zaczac wcisnij dowolny przycisk :-)" << std::endl;
	std::cin.get();
}

void Game::play()
{
	ready_game(); 	
	player gracz(1, sf::Vector2f(2050, 790));
	//platformy.emplace_back(new platform(sf::Vector2f(200, 50) , sf::Vector2f(650 , 700))); 
	while (window->isOpen())
	{ 
		sf::Vector2f play_pos = gracz.getPosition(); 
		//sf::Time elapsed = clock.restart();
		generate_platform(gracz); // sprawdzanie pozycji platform , nastepnie generowanie lub usuwanie zbednych platform
		generate_bombs(gracz); // to samo tylko z bombami 
		while (window->pollEvent(event)) // zamkniecie okna 
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
		pauza(window,gracz); // pauzuje gre 
		window->clear(sf::Color::Red); // czyszcenie ekranu 
		draw_tlo(window); // rysowanie tla , tlo sklada sie z 6 grafik nalozonych na siebie 
		update_all(gracz); // updatowanie pozycji platform oraz bomb nastepnie rysowanie ich		
        draw_all(window); // rysowanie wszystkich obiektow poza graczem 
		gracz.update(window, platformy, bomby , monety); // update gracza na podstawie pozycji platform i innych rzeczy nastepnie rysowanie go 
		view_game.setCenter(gracz.getPosition()); 
		window->setView(view_game); 
		window->display(); // wyswietlanie klatki gry
		if (gracz.get_status() == player::dead) // sprawdzanie warunku konca gry  , sam status dead czy alive jest aktualizowany w funkcji update
		{
			death(gracz , window); //jezeli gracz jest 'dead' to funkcja konczy gre 
		}
		update_minimap(gracz); 	
	}
}
void Game::generate_platform(player play) 

	{
	int los_monety = rand() % 4; 
	int los_kierunek = rand() % 2;
	int kierunek_ruchu = 1;
	if (los_kierunek == 1)
	{
		kierunek_ruchu = -1; 
	}
		if (platformy.size() < 7) 
		{
			int los = rand() % 6;
			if (los == 1 || los ==2)
			{ // platformy.emplace_back(new platform(sf::Vector2f(200, 50), sf::Vector2f(generate_rand_dist(), platformy.back()->getPosition().y - 200)));
				platformy.emplace_back(new platform(sf::Vector2f(200, 50), sf::Vector2f(platformy.back()->getPosition().x + (70 + rand() % 50)*kierunek_ruchu, platformy.back()->getPosition().y - 200)));
				if (los_monety == 3)
					monety->emplace_back(new coin(sf::Vector2f(platformy.back()->getPosition().x + rand() % 100, platformy.back()->getPosition().y - 50))); 
			}
			else if (los == 3 || los == 4)
			{
				platformy.emplace_back(new moving_platform(sf::Vector2f((rand() % 30) / 10 + 2, 0), sf::Vector2f(200, 50), sf::Vector2f(platformy.back()->getPosition().x + (70 + rand() % 50)*kierunek_ruchu, platformy.back()->getPosition().y - 200)));
				if (los_monety == 3)
				monety->emplace_back(new coin(sf::Vector2f(platformy.back()->getPosition().x + rand() % 100, platformy.back()->getPosition().y - 50)));
			}
			else if (los == 5)
			{
				platformy.emplace_back(new disappearing_platform(sf::Vector2f(3 + (rand() % 30) / 10, 1.2 - (rand() % 50) / 100), sf::Vector2f(200, 50), sf::Vector2f(platformy.back()->getPosition().x + (70 + rand() % 50)*kierunek_ruchu, platformy.back()->getPosition().y - 200)));
				if (los_monety == 3)
					monety->emplace_back(new coin(sf::Vector2f(platformy.back()->getPosition().x + rand() % 100, platformy.back()->getPosition().y - 50)));
			}
		}
		for (auto x : platformy)
		{
			if (x->getPosition().y  > play.getPosition().y + 800 ) 
			{
				auto element = std::find(platformy.begin(), platformy.end(), x);
				if (element != platformy.end())
				{
					delete x;
					platformy.erase(element);
				}
			}
		}
			for (auto m : *monety)
			{
				if (m->getPosition().y > play.getPosition().y + 400 && monety->size()>0)
				{
					auto element = std::find(monety->begin(), monety->end(), m);
					if (element != monety->end()) // gdy nie znajdzie elementu zwraca end()
					{
						delete m;
						monety->erase(element);
					}
				}
			}
		
	}


void Game::move_all(sf::Vector2f ruch)
{
	for (auto& p : platformy)
	{
		p->move(ruch); 
	}
	for (auto& m : *monety)
	{
		m->move(ruch); 
	}
}


void Game::next_screen(player &play) // funkcja rusza wszystkie elementy na ekranie w zaleznosci od wysokosci gracza 
{		
	if (play.getPosition().y < -1600 && map_number == 1 )
	{
		map_number = 2; 
		platformy.clear(); 
		play.setPosition(sf::Vector2f(play.getPosition().x, -3250));
		platformy.emplace_back(new platform(sf::Vector2f(200, 50), sf::Vector2f(play.getPosition().x-50, -3200)));
		//minimap->setPosition(sf::Vector2i(play.getPosition().x - 1000, minimap->getPosition().y));
		viev_minimap.setCenter(play.getPosition().x , play.getPosition().y -1500);
		minimap->setView(viev_minimap); 
	}
	if (play.getPosition().y < -6500 && map_number == 2)
	{
		map_number = 3; 
		platformy.clear();
		play.setPosition(sf::Vector2f(play.getPosition().x, -7450));
		platformy.emplace_back(new platform(sf::Vector2f(200, 50), sf::Vector2f(play.getPosition().x - 50, -7350)));
		viev_minimap.setCenter(play.getPosition().x, play.getPosition().y - 1350);
		
		
		minimap->setView(viev_minimap);
	}
	if (play.getPosition().y < -8500 && map_number == 3)
	{
		map_number = 1; 
		platformy.clear();
		monety->clear();
		bomby.clear();
		platformy.emplace_back(new platform(sf::Vector2f(200, 50), sf::Vector2f(2000, 900)));
		play.setPosition(2100, 850); 
		viev_minimap.setCenter(play.getPosition().x, play.getPosition().y - 1350);
		minimap->setView(viev_minimap);

	}

}


void Game::ready_game() // przygotowanie gry , ladowanie grafik oraz ustalanie poczatkowych wartosci zmiennych
{
	ready_background_texture(); 
	srand((unsigned)time(NULL));
	platformy.emplace_back(new platform(sf::Vector2f(200, 50), sf::Vector2f(2000, 900)));
	bomby.emplace_back(new bomb(sf::Vector2f(400, 20000)));
	game_speed = 0; 
	monety = new std::vector<coin*>; 
	window = new sf::RenderWindow(sf::VideoMode(800, 1000), "Cloud tower"); // tworzenie okna  
	minimap = new sf::RenderWindow(sf::VideoMode(250, 350), "MiniMap" , sf::Style::None);
	view_game = sf::View(sf::FloatRect(650, 790, 800.0f, 1000.0f));
	viev_minimap = sf::View(sf::FloatRect(1000, -2100, 2428, 3400));
	//viev_minimap = sf::View(sf::FloatRect(1500, -2000, 2000, 3000));
	coin moneta(sf::Vector2f(100, 100));
	window->setPosition(sf::Vector2i(600, 0)); 
	view_game.setCenter(650, 790);
	window->setView(view_game);
	window->setFramerateLimit(60);
	minimap->setView(viev_minimap);
	minimap->setFramerateLimit(60); 
	minimap->setPosition(sf::Vector2i(window->getPosition().x, window->getPosition().y+750));
	map_number = 1; 
	ready_background_texture();
	draw_tlo(window);
	
	
}


void Game::draw_tlo(sf::RenderWindow*window) // rysowanie tla 
{
	window->draw(tlo_s);
	//window->draw(tlo_s5);
	
	//window->draw(tlo_s4); 
  
    window->draw(tlo_s3);
     window->draw(tlo_s2);
}


float Game::generate_rand_dist() // generowanie pozycji X nastepnej platformy na podstawie pozycji poprzedniej 
{		                         // tak aby gracz byl w stanie doskoczyc do kazdej platformy 
	int dodatni = 1; 
	bool blokada = true; 
	float wynik = 0; ;
	while (blokada == true)
	{
		float random = rand() % 20;
		random = random / 10;
		if (rand() % 3 == 1)
		{
			dodatni = -1;
		}
		else 
		{
			dodatni = 1; 
		}
		wynik = dodatni * ( 120 + rand() % 200 ) ;
		if (wynik + platformy.back()->getPosition().x > 1 && wynik  +  platformy.back()->getPosition().x < 599)
		{
			return wynik + platformy.back()->getPosition().x; 
		}
		else
		{
		}
	}
}


void Game::generate_bombs(player play) // tworzenie i usuwanie bomb
{
	int los_kierunek = rand() % 2;
	int kierunek = 1; 
	if (los_kierunek == 1)
	{
		kierunek = -1; 
	}
	bomb_time = bomb_clock.getElapsedTime(); 
	if (bomby.size() < 8 && bomb_time.asSeconds() > 2)
	{
		bomby.emplace_back(new bomb(sf::Vector2f(play.getPosition().x + (rand()%400)*kierunek , play.getPosition().y - 1500)));
		bomb_clock.restart(); 
	}
	if(bomby.size()>0)
	if (bomby.front()->getPosition().y > play.getPosition().y + 300)
	{
		delete bomby.front(); 
		bomby.erase(bomby.begin()); 
	}
}


void Game::update_all(player& play)
{
	for (auto& x : platformy) // updatowanie pozycji platform oraz rysowanie ich
	{
		x->update();
	}
	if (monety->size() > 0)
	for (auto& m : *monety)
	{
		m->update(); 
	}
	move_bombs(); 
	next_screen(play); // updatowanie pozycji bomb oraz platform 
}


void Game::draw_all(sf::RenderWindow*window)
{
	for (auto& x : platformy)
	{
		window->draw(*x); 
	}
	for (auto& x : bomby)
	{
		window->draw(*x);
	}	
	for (auto& m : *monety)
	{
		window->draw(*m);
	}
}



void Game::death(player& play, sf::RenderWindow*window) // ekran smierci 
{
	for (auto x : bomby)
	{
		if (play.getGlobalBounds().intersects(x->getGlobalBounds()))
		{
			sf::Clock zegar;
			x->move(sf::Vector2f(-100, 0));
			while (zegar.getElapsedTime().asSeconds() < 2)
			{
				window->clear(sf::Color::White);
				draw_tlo(window);
				draw_all(window);
				x->update(true, zegar);
				window->draw(*x);
				window->display();

			}
		}
	}
	system("CLS");
	std::cout << "Przegrales!" << std::endl;
	std::cout << "Wcisnij cokolwiek aby kontynuowac" << std::endl;
	std::cout << "Wynik gracza to: " <<play.return_score()<< std::endl; 
	std::cin.get();
	window->close();
}


void Game::pauza(sf::RenderWindow*window, player& gracz)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // dodany element pauzy , gdy gracz jest w powietrzu 
	{
		// wywolujemy element klasy pauza ktory pobiera okno oraz rysuje swoje elementy na to
		PauseMenu pause(800, 1000);
		// zaokraglamy pozycje elementow do liczb calkowtych aby elementy nie "skakaly" po ekranie 
		window->clear(); // nastepnie rysujemy nowa klatke , po czym przekazujemy tak narysowane okno do funkcji "Play"; 
		draw_tlo(window);
		for (auto x : platformy)
		{
			x->setPosition(std::round(x->getPosition().x), std::round(x->getPosition().y));
		}
		//pause.Play(window); 
		draw_all(window);
		window->draw(gracz);
		window->display();
		std::cout << "Zapauzowano!" << std::endl;
		pause.Play(window);
		clock.restart();



	}
}

void Game::move_bombs()
{
	for (auto& x : bomby) // bomby 
	{
		x->move(sf::Vector2f(0, 3));
	}
}


void Game::ready_background_texture()
{
	if (!tlo1.loadFromFile("assets/winter 8/hd.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s.setTexture(tlo1);
	tlo_s.setScale(3, 3);
	tlo_s.setPosition(-1000, -3500);
	if (!tlo2.loadFromFile("assets/winter 7/hd.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s2.setTexture(tlo2);
	tlo_s2.setPosition(sf::Vector2f(-1000, -7000));
	tlo_s2.setScale(sf::Vector2f(3, 3));
	if (!tlo3.loadFromFile("assets/winter 4/hd.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s3.setTexture(tlo3);
	tlo_s3.setPosition(sf::Vector2f(-1000, -10500));
	tlo_s3.setScale(sf::Vector2f(3, 3));
	if (!tlo4.loadFromFile("assets/parallax-mountain-trees.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s4.setTexture(tlo4);
	tlo_s4.setPosition(sf::Vector2f(0-1000, 4000-9000));
	tlo_s4.setScale(sf::Vector2f(20, 40));
	if (!tlo5.loadFromFile("assets/parallax-mountain-mountains.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s5.setTexture(tlo5);
	tlo_s5.setPosition(sf::Vector2f(0-1000, 0-9000));
	tlo_s5.setScale(sf::Vector2f(60, 60));
}

void Game::update_minimap(player play )
{
	minimap->setPosition(sf::Vector2i(window->getPosition().x + 10, window->getPosition().y + 700));
	minimap->clear(sf::Color::Blue);
	draw_tlo(minimap); 
    draw_all(minimap);
	//play.setTextureRect(sf::IntRect(0, 0, 48, 48));
	//play.setScale(8, 8);
	minimap->draw(play);
	//play.setScale(2, 2); 
	minimap->display(); 
}