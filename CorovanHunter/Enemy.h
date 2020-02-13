#pragma once
#include "Entity.h"
class Enemy :
	public Entity
{
public:
	Enemy(sf::Image& image, Level& lev, sf::String Name, float X, float Y, int W, int H);
	void update(float time);
	void checkCollisionWithMap(float Dx, float Dy);
};

