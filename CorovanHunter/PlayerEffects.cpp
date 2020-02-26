#include "PlayerEffects.h"
#include <iostream>

PlayerEffects::PlayerEffects() {

	image.loadFromFile("images/fire.png");
	image.createMaskFromColor(sf::Color(249, 249, 249));
	image.createMaskFromColor(sf::Color(255, 255, 255));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setOrigin(180 / 2, 98 / 2);
	sprite.scale(-0.08, 0.08);
	sprite.setTextureRect(sf::IntRect(180, 0, 180, 98));
	counter = 0;
}

void PlayerEffects::gunFire() {
	sprite.setTextureRect(sf::IntRect(0, 0, 180, 98));
	counter = 0;
}

void PlayerEffects::updateFire(int x, int y, float time) {
	counter += time;
	sprite.setPosition(x - 4, y + 19.5);

	if (counter > 100) {
		sprite.setTextureRect(sf::IntRect(180, 0, 180, 98));
	}
}