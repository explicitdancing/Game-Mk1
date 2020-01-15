#pragma once
#include "SFML/Graphics.hpp"

class Help
{
public:
	Help(float width, float height)
	{
		font.loadFromFile("arial.ttf");
		help.setFont(font);
		help.setFillColor(sf::Color::Red);
		help.setString("move");
		help.setOrigin(help.getLocalBounds().width / 2, help.getLocalBounds().height / 2);
		help.setPosition(sf::Vector2f(width / 2, height / 2));
	}
	void draw(sf::RenderWindow& window)
	{
		window.draw(help);
	}

private:
	sf::Font font;
	sf::Text help;
};

