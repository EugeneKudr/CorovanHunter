#pragma once
#include <SFML/Graphics.hpp>

class LifeBar
{
public:
	sf::Image image;
	sf::Texture t;
	sf::Sprite s;
	LifeBar();
	void update(int k);
	void draw(sf::RenderWindow& window);
};

