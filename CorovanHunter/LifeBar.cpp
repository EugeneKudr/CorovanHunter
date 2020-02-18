#include "LifeBar.h"

LifeBar::LifeBar() {
	image.loadFromFile("images/healthbar.png");
	image.createMaskFromColor(sf::Color(255, 255, 255));
	t.loadFromImage(image);
	s.setTexture(t);
	s.setTextureRect(sf::IntRect(0, 0, 128, 32));
}

void LifeBar::update(int k) {
	if (k == 3) {
		s.setTextureRect(sf::IntRect(0, 32, 128, 32));
	}
	if (k == 2) {
		s.setTextureRect(sf::IntRect(0, 64, 128, 32));
	}
	if (k == 1) {
		s.setTextureRect(sf::IntRect(0, 96, 128, 32));
	}
	if (k == 0) {
		s.setTextureRect(sf::IntRect(0, 128, 128, 32));
	}
}

void LifeBar::draw(sf::RenderWindow& window)
{
	sf::Vector2f center = window.getView().getCenter();
	sf::Vector2f size = window.getView().getSize();

	s.setPosition(center.x + size.x / 2 - 138, center.y - size.y / 2 + 10);

	window.draw(s);
}