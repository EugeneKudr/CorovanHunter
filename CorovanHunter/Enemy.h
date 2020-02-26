#pragma once
#include "Entity.h"
class Enemy :
	public Entity
{
public:
	float animationSpeed;
	int colorTime;
	int dieDelay;
	Enemy(sf::Image& image, Level& lev, sf::String Name, float X, float Y, int W, int H);
	void update(float time);
	void checkCollisionWithMap(float Dx, float Dy);
	sf::Image imageLife;
	sf::Texture t;
	sf::Sprite s;
	int max;
	sf::RectangleShape bar;
	void drawLifeBar(sf::RenderWindow& window);
};

