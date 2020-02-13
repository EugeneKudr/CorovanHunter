#include "view.h"

sf::View view;

sf::View getPlayerCoordinateForView(float cordX, float cordY)
{
	float tempX = cordX;
	float tempY = cordY;

	view.setCenter(tempX, tempY);

	return view;
}

void changeView()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
	{
		view.zoom(1.01);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		view.setSize(640, 480);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
	{
		view.setSize(540, 380);
	}
}

