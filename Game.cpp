#include "Game.h"
#include "player.h"
#include <vector>
Game::Game()
{
	std::cout << "Witamy w cloud TOWER!" << std::endl; 
	std::cout << "Wykonali :" << std::endl; 
	std::cout << "Aby zaczac wcisnij dowolny przycisk :-)" << std::endl;
	std::cin.get();
	pauza_bool = true; 
	
}

void Game::play()
{
	ready_game(); 
    player play(1, sf::Vector2f(650, 790)); //tworzenie gracza 
    sf::RenderWindow window(sf::VideoMode(800, 1000), "Cloud tower"); // tworzenie okna 
    
	window.setFramerateLimit(60);	
	ready_background_texture(); 
	draw_tlo(window); // tutaj zaimplementuj menu pobierz ten window ;  
	while (window.isOpen())
	{ 
		sf::Time elapsed = clock.restart();
		generate_platform(); // sprawdzanie pozycji platform , nastepnie generowanie lub usuwanie zbednych platform
		generate_bombs(); // to samo tylko z bombami 
		while (window.pollEvent(event)) // zamkniecie okna 
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		pauza(window); // pauzuje gre 
		window.clear(sf::Color::Red); // czyszcenie ekranu 
		draw_tlo(window); // rysowanie tla , tlo sklada sie z 6 grafik nalozonych na siebie 
		update_all(play, elapsed); // updatowanie pozycji platform oraz bomb nastepnie rysowanie ich		
        draw_all(window); // rysowanie wszystkich obiektow poza graczem 
		play.update(window, platformy, bomby); // update gracza na podstawie pozycji platform i innych rzeczy nastepnie rysowanie go 
		window.display(); // wyswietlanie klatki gry
		if (play.get_status() == player::dead) // sprawdzanie warunku konca gry  , sam status dead czy alive jest aktualizowany w funkcji update
		{
			death(play , window); //jezeli gracz jest 'dead' to funkcja konczy gre 
		}
	}
}
void Game::generate_platform() 

	{
		if (platformy.size() < 8) 
		{
			int los = rand() % 6;
			if (los == 1 || los ==2)
			{
				platformy.emplace_back(new platform(sf::Vector2f(200, 50), sf::Vector2f(generate_rand_dist(), platformy.back()->getPosition().y - 200)));
			}
			else if (los == 3 || los == 4)
				platformy.emplace_back(new moving_platform(sf::Vector2f((rand() % 30) / 10 + 2, 0), sf::Vector2f(200, 50), sf::Vector2f(generate_rand_dist(), platformy.back()->getPosition().y - 200)));
			else if (los ==5)
				platformy.emplace_back(new disappearing_platform(sf::Vector2f(3 + (rand()%30) / 10, 1.2 - (rand()%50) / 100), sf::Vector2f(200, 50), sf::Vector2f(generate_rand_dist(), platformy.back()->getPosition().y - 200)));
		}
		if (platformy.front()->getPosition().y > 1000)
		{

			delete platformy.front();
			platformy.erase(platformy.begin());
		}

	}


void Game::move_all(sf::Vector2f ruch)
{
	for (auto& p : platformy)
	{
		p->move(ruch); 
	}
}

void Game::next_screen(player &play, const sf::Time& elapsed) // funkcja rusza wszystkie elementy na ekranie w zaleznosci od wysokosci gracza 
{
		move_all(sf::Vector2f(0 * elapsed.asMilliseconds(), game_speed * elapsed.asMilliseconds())); // platformy 
		play.move(sf::Vector2f(0 * elapsed.asMilliseconds(), game_speed * elapsed.asMilliseconds())); // gracz
		if (play.getPosition().y < 200)
		{
			game_speed = game_speed + 0.00055;
		}
		else if (play.getPosition().y > 600 && game_speed > 0.06)
		{
			game_speed = game_speed - 0.002;
		}
		else if (play.getPosition().y < 400 && game_speed < 0.6)
		{
			game_speed += 0.00025;
		}
		if (play.getPosition().y < 200) // zabezpieczenie aby gracz nie wyskoczyl poza ekran 
		{

			move_all((sf::Vector2f(0, 200 - play.getPosition().y)));
			play.move(sf::Vector2f(0, 200 - play.getPosition().y));
		}
		for (auto& x : bomby) // bomby 
		{
			x->move(sf::Vector2f(0 * elapsed.asMilliseconds(), 4 * game_speed * elapsed.asMilliseconds()));
		}
		player_score += game_speed * 5; // naliczanie punktow dla gracza 
}

void Game::ready_game() // przygotowanie gry , ladowanie grafik oraz ustalanie poczatkowych wartosci zmiennych
{
	ready_background_texture(); 
	srand((unsigned)time(NULL));
	player_score = 0; 
	platformy.emplace_back(new platform(sf::Vector2f(200, 50), sf::Vector2f(600, 900)));
	bomby.emplace_back(new bomb(sf::Vector2f(400, 20000)));
	game_speed = 0; 
	
	
}


void Game::draw_tlo(sf::RenderWindow& window) // rysowanie tla 
{
	window.draw(tlo_s);
	window.draw(tlo_s5); 
	window.draw(tlo_s3);
	window.draw(tlo_s4); 
    window.draw(tlo_s2);
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

void Game::generate_bombs() // tworzenie i usuwanie bomb
{
	bomb_time = bomb_clock.getElapsedTime(); 
	if (bomby.size() < 4 && bomb_time.asSeconds() > 4 && game_speed != 0 )
	{
		bomby.emplace_back(new bomb(sf::Vector2f(rand()%800, platformy.back()->getPosition().y - 200 )));
		bomb_clock.restart(); 
		std::cout << "tworze bombe " << std::endl;
	}
	if (bomby.front()->getPosition().y > 1000 && bomby.size() > 0 )
	{
		delete bomby.front(); 
		bomby.erase(bomby.begin()); 
	}
}

void Game::update_all(player& play, const sf::Time& elapsed)
{
	for (auto& x : platformy) // updatowanie pozycji platform oraz rysowanie ich
	{
		x->update();
	}
	next_screen(play, elapsed); // updatowanie pozycji bomb oraz platform 
}

void Game::draw_all(sf::RenderWindow& window)
{
	for (auto& x : platformy)
	{
		window.draw(*x); 
	}
	for (auto& x : bomby)
	{
		window.draw(*x);
	}
}

void Game::death(player& play, sf::RenderWindow& window) // ekran smierci 
{
	for (auto x : bomby)
	{
		if (play.getGlobalBounds().intersects(x->getGlobalBounds()))
		{
			sf::Clock zegar;
			x->move(sf::Vector2f(-80, 0));
			while (zegar.getElapsedTime().asSeconds() < 2)
			{
				window.clear(sf::Color::White);
				draw_tlo(window);
				draw_all(window);
				x->update(true, zegar);
				window.draw(*x);
				window.display();

			}
		}
	}
	system("CLS");
	std::cout << "Przegrales!" << std::endl;
	std::cout << "Wcisnij cokolwiek aby kontynuowac" << std::endl;
	std::cout << "Wynik gracza to: " << std::round(player_score) << std::endl; 
	std::cin.get();
	window.close();
}

void Game::pauza(sf::RenderWindow &window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // dodany element pauzy , gdy gracz jest w powietrzu 
	{
		// tutaj zaimplementowac pauze
		 pauza_bool = true;
		system("CLS");
		std::cout << "Zapauzowano!" << std::endl;
		float game_spped2 = game_speed;
		game_speed = 0; 
		while (pauza_bool)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
			{
				pauza_bool = false;
				game_speed = game_spped2; 
				clock.restart(); 
				
			}
		}
	}
}

void Game::ready_background_texture()
{
	if (!tlo1.loadFromFile("assets/parallax-mountain-bg.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s.setTexture(tlo1);
	tlo_s.setScale(3, 5);
	tlo_s.setPosition(0, 0);
	if (!tlo2.loadFromFile("assets/parallax-mountain-foreground-trees.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s2.setTexture(tlo2);
	tlo_s2.setPosition(sf::Vector2f(0, 350));
	tlo_s2.setScale(sf::Vector2f(4, 4));
	if (!tlo3.loadFromFile("assets/parallax-mountain-montain-far.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s3.setTexture(tlo3);
	tlo_s3.setPosition(sf::Vector2f(0, -100));
	tlo_s3.setScale(sf::Vector2f(4, 7));
	if (!tlo4.loadFromFile("assets/parallax-mountain-trees.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s4.setTexture(tlo4);
	tlo_s4.setPosition(sf::Vector2f(0, 400));
	tlo_s4.setScale(sf::Vector2f(2, 4));
	if (!tlo5.loadFromFile("assets/parallax-mountain-mountains.png"))
	{
		std::cout << "nie zaladowano tla";
	}
	tlo_s5.setTexture(tlo5);
	tlo_s5.setPosition(sf::Vector2f(0, 0));
	tlo_s5.setScale(sf::Vector2f(6, 6));
}
