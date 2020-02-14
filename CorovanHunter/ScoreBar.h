#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>

class ScoreBar
{
public:
	sf::Font font;
	sf::Text text;
	ScoreBar();
	void update(int score, int health, int ammo);
	void draw(sf::RenderWindow& window);
	void gameOver(sf::RenderWindow& window);
};

