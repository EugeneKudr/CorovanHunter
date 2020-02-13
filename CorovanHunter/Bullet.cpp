#include "Bullet.h"
#include <iostream>

Bullet::Bullet(sf::Image& image, sf::String Name, Level& lvl, float X, float Y, int W, int H, int dir) : 
    Entity(image, X, Y, W, H, Name) {

    obj = lvl.GetObjects("solid");
    x = X;
    y = Y;
    direction = dir;
    speed = 0.8;
    w = h = 8;
}

void Bullet::update(float time) {
    switch (direction)
    {
    case 0: dx = -speed; dy = 0;   break;
    case 1: dx = speed; dy = 0;   break;
    case 2: dx = -speed; dy = 0;   break;
    case 3: dx = -speed; dy = 0;   break;
    case 4: dx = -speed; dy = 0;   break;
    }

    x += dx * time;
    y += dy * time;

    for (int i = 0; i < obj.size(); i++) {
        if (getRect().intersects(obj[i].rect)) {
            life = false;
        }
    }

    sprite.setPosition(x + w / 2, y + h / 2);
}