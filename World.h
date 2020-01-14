#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>


class World {
public:
	Player* player;
	Monster* monsters[MAX_MONSTERS] = { NULL };
	Projectile* projectiles[MAX_PROJECTILES] = { NULL };
	int windowSizeX, windowSizeY;
	sf::RenderWindow* window;
	float oldTime = 0;
	float newTime;
	float spawnTimer = 0;
	World(sf::RenderWindow* window, int windowSizeX, int windowSizeY) 
	{
		this->window = window;
		this->windowSizeX = windowSizeX;
		this->windowSizeY = windowSizeY;
	}
	void newGame() 
	{
		player = new Player(windowSizeX, windowSizeY, projectiles);
		newTime = clock();
	};
	void update(int mousePositionX, int mousePositionY) 
	{
		player->move(mousePositionX, mousePositionY);
		for (int i = 0; i < MAX_MONSTERS; i++) 
		{
			if (monsters[i] != NULL)
			{
				monsters[i]->move();
				monsters[i]->collisionCheck(monsters);
			}
		}
		for (int i = 0; i < MAX_PROJECTILES; i++)
		{
			if (projectiles[i] != NULL)
			{
				projectiles[i]->move();
				projectiles[i]->hitCheck(monsters, projectiles);
			}
		}

		oldTime = newTime;
		newTime = clock();
		float timeDifferenceSeconds = (newTime - oldTime) / CLOCKS_PER_SEC;
		spawnTimer += timeDifferenceSeconds;
		if (spawnTimer >= 1) 
		{
			spawnMonster();
			spawnTimer = 0;
		}
	}
	void spawnMonster() 
	{
		for (int i = 0; i < MAX_MONSTERS; i++) 
		{
			if (monsters[i] == NULL)
			{
				monsters[i] = new Monster(windowSizeX, windowSizeY, player);
				monsters[i]->spawnCheck(monsters);
				break;
			}
		}
	}
	void draw() 
	{
		window->draw(*(player->getSprite()));
		for (int i = 0; i < MAX_MONSTERS; i++) 
		{
			if (monsters[i] != NULL)
			{
				window->draw(*(monsters[i]->getSprite()));
			}
		}
	}
};