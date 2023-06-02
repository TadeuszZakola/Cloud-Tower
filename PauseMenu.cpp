#include "PauseMenu.h"
PauseMenu::PauseMenu(float width, float height)
{
	std::cout << "obiekt pauzy" << std::endl;
	font.loadFromFile("./assets/BigSmoke.ttf");

	title.setFont(font);
	title.setFillColor(sf::Color::Black);
	//title.setFillColor(sf::Color::White);
	title.setCharacterSize(100);
	title.setString("PAUZA");
	title.setPosition(sf::Vector2f(250, 50));

	std::vector<sf::FloatRect> textbounds;
	std::vector<sf::FloatRect> buttonbounds;

	//TEKST PRZYCISKU GRAJ
	buttontext[0].setString("WZNOW");
	buttontext[1].setString("WYJSCIE");
	for(int i = 0; i < MAX_NUMBER_OF_PAUSE_BUTTONS; i++)
	{
		buttontext[i].setFont(font);
		buttontext[i].setFillColor(sf::Color::Black);
		buttontext[i].setCharacterSize(70);
		buttontext[i].setPosition(sf::Vector2f(400, (320 * (i + 1)) + 50));
		textbounds.emplace_back(buttontext[i].getLocalBounds());
		buttontext[i].setOrigin(sf::Vector2f(textbounds[i].left + textbounds[i].width / 2, textbounds[i].top + textbounds[i].height / 2));

		button[i].setSize(sf::Vector2f(textbounds[i].width + 5.0, 80));
		buttonbounds.emplace_back(button[i].getLocalBounds());

		button[i].setFillColor(sf::Color(255, 247, 226));
		button[i].setOutlineColor(sf::Color::Black);
		button[i].setOutlineThickness(5);
		button[i].setOrigin(sf::Vector2f(buttonbounds[i].left + buttonbounds[i].width / 2, buttonbounds[i].top + buttonbounds[i].height / 2));
		button[i].setPosition(sf::Vector2f(400, (320 * (i + 1)) + 50));
	}
	pauseBackground.setFillColor(sf::Color(0,0,0,1));
	pauseBackground.setSize(sf::Vector2f(width,height));
	pauseBackground.setPosition(sf::Vector2f(0,0));
	selectedItemIndex = 2;

}
void PauseMenu::draw(sf::RenderWindow*window)
{
	
	window->draw(title);
	for(int i = 0; i < MAX_NUMBER_OF_PAUSE_BUTTONS; i++)
	{
		window->draw(button[i]);
		window->draw(buttontext[i]);
	}
}
void PauseMenu::MoveUp()
{
	if(selectedItemIndex - 1 >= 0)
	{
		buttontext[selectedItemIndex].setFillColor(sf::Color::Black);
		button[selectedItemIndex].setOutlineColor(sf::Color::Black);
		selectedItemIndex--;
		buttontext[selectedItemIndex].setFillColor(sf::Color::Red);
		button[selectedItemIndex].setOutlineColor(sf::Color::Red);
	}
}
void PauseMenu::MoveDown()
{
	if(selectedItemIndex + 1 < MAX_NUMBER_OF_PAUSE_BUTTONS)
	{
		buttontext[selectedItemIndex].setFillColor(sf::Color::Black);
		button[selectedItemIndex].setOutlineColor(sf::Color::Black);
		selectedItemIndex++;
		buttontext[selectedItemIndex].setFillColor(sf::Color::Red);
		button[selectedItemIndex].setOutlineColor(sf::Color::Red);
	}
}
void PauseMenu::Play(sf::RenderWindow*window)
{
	bool pauza=true;
	//PauseMenu pause(window->getSize().x, window->getSize().y);
	while(pauza)
	{
		sf::Event event;
		while(window->pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::KeyReleased:
					switch(event.key.code)
					{
						case sf::Keyboard::Up:
							this->MoveUp();
							break;

						case sf::Keyboard::Down:
							this->MoveDown();
							break;

						case sf::Keyboard::Return:
							switch(this->GetPressedItem())
							{
								case 0:
									pauza=!pauza;
									std::cout << "Play button has been pressed" << std::endl;
									break;
								case 1:
									window->close();
									break;
							}

							break;
					}

					break;
				case sf::Event::Closed:
					window->close();

					break;

			}
		}


		this->draw(window);
		window->draw(pauseBackground);
		window->display();
	}

}