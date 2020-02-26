#include "loadObjects.h"

void preLoad(sf::Image &image, sf::Image &BulletImage, sf::SoundBuffer &shootBuffer, sf::Sound &shoot, sf::Music &archerTheme) {
	image.loadFromFile("images/sprites.png");
	image.createMaskFromColor(sf::Color(255, 0, 255));

	BulletImage.loadFromFile("images/bullet.png");
	BulletImage.createMaskFromColor(sf::Color(0, 0, 0));

	shootBuffer.loadFromFile("audio/shoot.ogg");

	shoot.setBuffer(shootBuffer);
	shoot.setVolume(3);

	archerTheme.openFromFile("audio/archer.ogg");
	archerTheme.setVolume(5);
	//archerTheme.play();
	archerTheme.setLoop(true);
}