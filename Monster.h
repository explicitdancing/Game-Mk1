#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include "Player.h"

class Monster 
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f currentDirection;
	sf::Vector2f targetDirection;
	sf::IntRect collisionBox;
	Player* player;
	float velocity = 0.5;
public:
	Monster(int windowSizeX, int windowSizeY, Player* player)
	{
		this->player = player;
		sprite.setScale(SPRITE_SCALE_MONSTER, SPRITE_SCALE_MONSTER);
		if (texture.loadFromFile("mclovich.png")) 
		{
			sprite.setTexture(texture, 1);
		}
		sf::IntRect rect = this->sprite.getTextureRect();
		collisionBox.height = (sprite.getLocalBounds().height * SPRITE_SCALE_MONSTER);
		collisionBox.width = (sprite.getLocalBounds().width * SPRITE_SCALE_MONSTER);
		sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
		srand(time(NULL));
		int spawnPlace = rand() % 4;
		switch (spawnPlace)
		{
		case 0:
			sprite.setPosition(0, rand() % windowSizeY);
			break;
		case 1:
			sprite.setPosition(rand() % windowSizeX, 0);
			break;
		case 2:
			sprite.setPosition(windowSizeX, rand() % windowSizeY);
			break;
		case 3:
			sprite.setPosition(rand() % windowSizeX, windowSizeY);
			break;
		}
		sprite.setPosition((rand() % windowSizeX) + (sprite.getLocalBounds().width / 2), (rand() % windowSizeY) + (sprite.getLocalBounds().height));
	}

	float getVelocity() { return velocity; }
	void changeVelocity(float x) { velocity = velocity * x; }
	int getRadius() { return sprite.getTextureRect().height / 2 * SPRITE_SCALE_MONSTER; }
	sf::Sprite* getSprite() { return &sprite; }
	sf::Vector2f getPosition() { return sprite.getPosition(); }
	sf::Vector2f getSpeed() { return currentDirection; }

	void move() 
	{
		sf::Vector2f playerPosition = player->getPosition();
		int displacementX = 0, displacementY = 0;
		displacementX = playerPosition.x - sprite.getPosition().x;
		displacementY = playerPosition.y - sprite.getPosition().y;
		float displacementLength = sqrt(pow((displacementX), 2) + pow((displacementY), 2));
		if (displacementLength != 0)
		{
			targetDirection.x = displacementX / displacementLength;
			targetDirection.y = displacementY / displacementLength;
			currentDirection.x = ((500 * currentDirection.x + targetDirection.x) / 501);
			currentDirection.y = ((500 * currentDirection.y + targetDirection.y) / 501);
			sprite.move(currentDirection * velocity);
			sprite.setRotation(90 + atan2(currentDirection.y, currentDirection.x) * 180 / 3.141592);
		}
		if (velocity < 0.5) 
		{
			velocity = velocity + 0.0001;
		}
	}

	void collided() 
	{
		currentDirection = -currentDirection;
		//sprite.setPosition((sprite.getPosition().x + currentDirection.x * velocity), (sprite.getPosition().y + currentDirection.y * velocity));
	}

	void collisionCheck(Monster* monsters[]) 
	{
		float x1, x2, y1, y2, radiusSum, distanceFromCentres;
		for (int i = 0; i < MAX_MONSTERS; i++) 
		{
			if (monsters[i] != NULL && monsters[i] != this)
			{
				x1 = (getPosition().x); //this x
				y1 = (getPosition().y); //this y
				x2 = monsters[i]->getPosition().x; //second x
				y2 = monsters[i]->getPosition().y; //second y
				radiusSum = getRadius() + monsters[i]->getRadius(); //sum of radiuses' lengths
				distanceFromCentres = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
				if (distanceFromCentres <= radiusSum)
				{
					collided();
					monsters[i]->collided();
				}
			}
		}
	}

	void destroy(Monster* monsters[])
	{
		for (int i = 0; i < MAX_MONSTERS; i++)
		{
			if (monsters[i] == this)
			{
				monsters[i] = NULL;
				break;
			}
		}
		this->~Monster();
	}

	void spawnCheck(Monster* monsters[])
	{
		float x1, x2, y1, y2, radiusSum, distanceFromCentres;
		for (int i = 0; i < MAX_MONSTERS; i++)
		{
			if (monsters[i] != NULL && monsters[i] != this)
			{
				x1 = (getPosition().x); //this x
				y1 = (getPosition().y); //this y
				x2 = monsters[i]->getPosition().x; //second x
				y2 = monsters[i]->getPosition().y; //second y
				radiusSum = getRadius() + monsters[i]->getRadius(); //sum of radiuses' lengths
				distanceFromCentres = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
				if (distanceFromCentres <= radiusSum)
				{
					this->destroy(monsters);
					break;
				}
			}
		}
	}


};