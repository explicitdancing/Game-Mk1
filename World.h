#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include "Defines.h"


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
	int points = 0;
	World(sf::RenderWindow* window, int windowSizeX, int windowSizeY) 
	{
		this->window = window;
		this->windowSizeX = windowSizeX;
		this->windowSizeY = windowSizeY;
	}
	void newGame() 
	{
		player = new Player(windowSizeX, windowSizeY);
		newTime = clock();
	};
	void update(int mousePositionX, int mousePositionY) 
	{
		player->move(mousePositionX, mousePositionY);
		for (int i = 0; i < MAX_PROJECTILES; i++)
		{
			if (projectiles[i] != NULL)
			{
				projectiles[i]->move();
				bool outOfBorderFlag = 0;
				outOfBorderFlag = outOfBorders(projectiles[i]->getPosition().x, projectiles[i]->getPosition().y, projectiles[i]->getRadius());
				if (outOfBorderFlag == 1)
				{
					projectiles[i]->destroy();
					projectiles[i] = NULL;
					break;
				}

				for (int j = 0; j < MAX_MONSTERS; j++)
				{
					if (monsters[j] != NULL)
					{
						bool collisionFlag = 0;
						collisionFlag = collisionCheck(projectiles[i]->getPosition().x, projectiles[i]->getPosition().y, projectiles[i]->getRadius(), monsters[j]->getPosition().x, monsters[j]->getPosition().y, monsters[j]->getRadius());
						if (collisionFlag == 1)
						{
							projectiles[i]->destroy();
							projectiles[i] = NULL;
							monsters[j]->destroy();
							monsters[j] = NULL;
							points++;
							break;
						}
					}
				}
			}
		}
		for (int i = 0; i < MAX_MONSTERS; i++) 
		{
			if (monsters[i] != NULL)
			{
				monsters[i]->move();
				for (int j = 0; j < MAX_MONSTERS; j++)
				{
					if (monsters[j] != NULL && i != j)
					{
						bool collisionFlag = 0;
						collisionFlag = collisionCheck(monsters[i]->getPosition().x, monsters[i]->getPosition().y, monsters[i]->getRadius(), monsters[j]->getPosition().x, monsters[j]->getPosition().y, monsters[j]->getRadius());
						if (collisionFlag == 1)
						{
							//bounce
						}
					}
				}
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
	void shoot()
	{
		float x = player->getPosition().x;
		float y = player->getPosition().y;
		sf::Vector2f direction = player->getDirection();
		for (int i = 0; i < MAX_PROJECTILES; i++)
		{
			if (projectiles[i] == NULL)
			{
				projectiles[i] = new Projectile(x, y, direction);
				break;
			}
		}
	}
	void draw() 
	{
		window->draw(*(player->getSprite()));
		for (int i = 0; i < MAX_MONSTERS; i++) 
		{
			if (monsters[i] != NULL) { window->draw(*(monsters[i]->getSprite())); }
		}
		for (int i = 0; i < MAX_PROJECTILES; i++)
		{
			if (projectiles[i] != NULL) { window->draw(*(projectiles[i]->getSprite())); }
		}
	}
	bool collisionCheck(float x1, float y1, float radius1, float x2, float y2, float radius2)
	{
		float radiusSum, distanceFromCentres;
		radiusSum = radius1 + radius2;
		distanceFromCentres = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
		if (distanceFromCentres <= radiusSum) { return 1; }
		else { return 0; }
	}
	bool outOfBorders(float x, float y, float radius)
	{
		if (x<0 || x>WINDOW_SIZE_X || y<0 || y> WINDOW_SIZE_Y)
		{
			float distanceFromBorder;
			int whichBorder;
			if (x < 0) { whichBorder = 0; }
			if (x > WINDOW_SIZE_X) { whichBorder = 1; }
			if (y < 0) { whichBorder = 2; }
			if (y > WINDOW_SIZE_Y) { whichBorder = 3; }
			switch (whichBorder)
			{
			case 0:
				distanceFromBorder = -x;
				if (distanceFromBorder > radius) { return 1; }
				else { return 0; }
				break;
			case 1:
				distanceFromBorder = x - WINDOW_SIZE_X;
				if (distanceFromBorder > radius) { return 1; }
				else { return 0; }
				break;
			case 2:
				distanceFromBorder = -y;
				if (distanceFromBorder > radius) { return 1; }
				else { return 0; }
				break;
			case 3:
				distanceFromBorder = y - WINDOW_SIZE_Y;
				if (distanceFromBorder > radius) { return 1; }
				else { return 0; }
				break;
			}
		}
		return 0;
	}
};