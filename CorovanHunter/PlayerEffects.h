#pragma once
#include <SFML/Graphics.hpp>

class PlayerEffects
{
public:
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::String name;
	float counter;
	PlayerEffects();
	void gunFire();
	void updateFire(int x, int y, float time);
};

