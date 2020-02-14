#pragma once
#include "Entity.h"
#include "view.h"

class Player :
	public Entity
{
public:
	enum stateObject { left, right, up, down, stay } state;
	bool isShoot;

	Player(extern sf::Image& image, extern Level& lev, extern sf::String Name, extern float X, extern float Y, extern int W, extern int H);
	void control(float time);
	void update(float time);
	void checkCollisionWithMap(float Dx, float Dy);
};

