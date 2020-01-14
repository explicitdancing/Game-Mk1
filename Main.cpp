#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include "Defines.h"

#include "Menu.h"
#include "Help.h"
#include "Monster.h"
#include "Projectile.h"
#include "Player.h"
#include "World.h"

int main()
{
	int mousePositionX = 0, mousePositionY = 0;
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "DAJCIE MI GODNEGO PRZECIWNIKA");
	World world(&window, WINDOW_SIZE_X, WINDOW_SIZE_Y);
	sf::Event event;
	Menu menu(WINDOW_SIZE_X, WINDOW_SIZE_Y);
	Help help(WINDOW_SIZE_X, WINDOW_SIZE_Y);
	bool menuFlag = 1;
	bool helpFlag = 0;
	while (window.isOpen())
	{
		if (menuFlag)
		{
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						if (!helpFlag)
							menu.moveUp();
						break;
						
					case sf::Keyboard::Down:
						if (!helpFlag)
							menu.moveDown();
						break;

					case sf::Keyboard::Escape:
						helpFlag = 0;
						break;

					case sf::Keyboard::Return:
						if(!helpFlag)
							switch (menu.selectChosenItem())
							{
							case 0:
								//resume
								menuFlag = 0;
								break;

							case 1:
								//new game
								menuFlag = 0;
								world.newGame();
								break;

							case 2:
								//options
								break;

							case 3:
								//help
								helpFlag = 1;
								break;

							case 4:
								//exit
								window.close();
								break;
							}
						break;
					}
					break;

				case sf::Event::Closed:
					window.close();
					break;
				}
			}

			window.clear();
			if (helpFlag)
				help.draw(window);
			else
				menu.draw(window);

			window.display();
		}
		else
		{
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::MouseMoved)
				{
					mousePositionX = event.mouseMove.x;
					mousePositionY = event.mouseMove.y;
				}
			}

			window.clear();

			world.update(mousePositionX, mousePositionY);
			world.draw();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				menuFlag = 1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
			{
				menuFlag = 1;
				helpFlag = 1;
			}



			window.display();

		}
	}

	return 0;
}