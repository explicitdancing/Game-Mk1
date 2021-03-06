#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include "Defines.h"

#include "Projectile.h"


class Player 
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f moveDirection;
	float velocity = 2;
public:
	Player(int windowSizeX, int windowSizeY) 
	{
		sprite.setScale(SPRITE_SCALE_PLAYER, SPRITE_SCALE_PLAYER);
		if (texture.loadFromFile("pudzian.png")) 
		{
			sprite.setTexture(texture, 1);
		}

		sf::IntRect playerRect = this->sprite.getTextureRect();
		this->sprite.setOrigin(playerRect.left + playerRect.width / 2.0f, playerRect.top + playerRect.height / 2.0f);
		sprite.setPosition(sf::Vector2f((windowSizeX) / 2.0f, (windowSizeY) / 2.0f));
	}

	sf::Sprite* getSprite() { return &sprite; }
	sf::Vector2f getPosition() { return sprite.getPosition(); }
	sf::Vector2f getDirection() { return moveDirection; }

	void move(int mousePositionX, int mousePositionY) 
	{
		int playerPositionX = 0, playerPositionY = 0, displacementX = 0, displacementY = 0;
		playerPositionX = sprite.getPosition().x;
		playerPositionY = sprite.getPosition().y;
		displacementX = mousePositionX - playerPositionX;
		displacementY = mousePositionY - playerPositionY;
		float displacementLength = sqrt(pow((displacementX), 2) + pow((displacementY), 2));
		if (displacementLength > 10)
		{
			moveDirection.x = displacementX / displacementLength;
			moveDirection.y = displacementY / displacementLength;
			sprite.move(moveDirection * velocity);
			sprite.setRotation(90+atan2(displacementY, displacementX)*180/3.141592);
		}
	}
};
