#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include "Monster.h"

class Projectile
{
private:
	sf::Vector2f moveDirection;
	sf::Texture texture;
	sf::Sprite sprite;
	float velocity = 2;
public:
	Projectile(int playerPositionX, int playerPositionY, sf::Vector2f moveDirection)
	{
		sprite.setScale(SPRITE_SCALE_PROJECTILE, SPRITE_SCALE_PROJECTILE);
		if (texture.loadFromFile("fireball.png"))
		{
			sprite.setTexture(texture, 1);
		}

		sf::IntRect projectileRect = this->sprite.getTextureRect();
		sprite.setOrigin(sprite.getLocalBounds().width / 4.0f, sprite.getLocalBounds().height / 2.0f);
		sprite.setPosition(sf::Vector2f((playerPositionX) / 2.0f, (playerPositionY) / 2.0f));
		this->moveDirection = moveDirection;
		sprite.setRotation(90 + atan2(moveDirection.y, moveDirection.x) * 180 / 3.141592);
	}

	sf::Sprite* getSprite() { return &sprite; }
	sf::Vector2f getPosition() { return sprite.getPosition(); }
	int getRadius() { return sprite.getTextureRect().height / 2 * SPRITE_SCALE_PROJECTILE; }

	void move() { sprite.move(moveDirection * velocity); }

	void hitCheck(Monster** monsters, Projectile** projectiles)
	{
		float x1, x2, y1, y2, radiusSum, distanceFromCentres;
		for (int i = 0; i < MAX_MONSTERS; i++)
		{
			if (monsters[i] != NULL)
			{
				x1 = (getPosition().x); //this x
				y1 = (getPosition().y); //this y
				x2 = monsters[i]->getPosition().x; //second x
				y2 = monsters[i]->getPosition().y; //second y
				radiusSum = getRadius() + monsters[i]->getRadius(); //sum of radiuses' lengths
				distanceFromCentres = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
				if (distanceFromCentres <= radiusSum)
				{
					this->destroy(projectiles);
					monsters[i]->destroy(monsters);

					break;
				}
			}
		}
	}
	void destroy(Projectile** projectiles)
	{
		for (int i = 0; i < MAX_PROJECTILES; i++)
		{
			if (projectiles[i] == this)
			{
				projectiles[i] = NULL;
				break;
			}
		}
		this->~Projectile();
	}


};
