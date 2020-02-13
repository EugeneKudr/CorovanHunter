#pragma once
#include "Entity.h"
class Bullet :
	public Entity
{
public:
	int direction;
	Bullet(sf::Image& image, sf::String Name, Level& lvl, float X, float Y, int W, int H, int dir);
	void update(float time);
};

