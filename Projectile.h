#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include "Defines.h"

#include "Monster.h"

class Projectile
{
private:
	sf::Vector2f moveDirection;
	sf::Texture texture;
	sf::Sprite sprite;
	float velocity = 3;
public:
	Projectile(float playerPositionX, float playerPositionY, sf::Vector2f moveDirection)
	{
		this->moveDirection = moveDirection;
		sprite.setScale(SPRITE_SCALE_PROJECTILE, SPRITE_SCALE_PROJECTILE);
		if (texture.loadFromFile("fireball.png"))
		{
			sprite.setTexture(texture, 1);
		}

		sf::IntRect rect = this->sprite.getTextureRect();
		sprite.setOrigin(sprite.getLocalBounds().width / 4.0f, sprite.getLocalBounds().height / 2.0f);
		sprite.setPosition((playerPositionX), (playerPositionY));
		sprite.setRotation(180 + atan2(moveDirection.y, moveDirection.x) * 180 / 3.141592);
	}

	sf::Sprite* getSprite() { return &sprite; }
	sf::Vector2f getPosition() { return sprite.getPosition(); }
	int getRadius() { return (sprite.getTextureRect().height / 2 * SPRITE_SCALE_PROJECTILE); }

	void move() { sprite.move(moveDirection * velocity); }

	void destroy()
	{
		this->~Projectile();
	}
};
