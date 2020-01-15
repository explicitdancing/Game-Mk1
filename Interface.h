#pragma once
#include "SFML/Graphics.hpp"
#include "Defines.h"

class Interface
{
public:
	Interface()
	{
		font.loadFromFile("arial.ttf");
		interface.setFont(font);
		interface.setFillColor(sf::Color::Red);
		interface.setString("move");
		interface.setOrigin(interface.getLocalBounds().width / 2, interface.getLocalBounds().height / 2);
		interface.setPosition(sf::Vector2f(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2));
	}
	void draw(sf::RenderWindow& window)
	{
		window.draw(interface);
	}

private:
	sf::Font font;
	sf::Text interface;
};