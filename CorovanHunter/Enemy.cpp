#include "Enemy.h"

Enemy::Enemy(sf::Image& image, Level& lev, sf::String Name, float X, float Y, int W, int H) :
    Entity(image, X, Y, W, H, Name) {
    obj = lev.GetObjects("solid");
    if (name == "easyEnemy") {
        health = 100;
        damageDeal = false;
        sprite.setTextureRect(sf::IntRect(96, 256, w, h));
        int randoms = rand() % 5 + 5;
        dx = randoms * 0.01;
        animationSpeed = 0.005;
    }
}

void Enemy::update(float time) {
    if (name == "easyEnemy") {
        checkCollisionWithMap(dx, 0);
        x += dx * time;
        if (dx < 0) {
            currentFrame += animationSpeed * time;
            if (currentFrame > 4) currentFrame -= 3;
            sprite.setTextureRect(sf::IntRect(32 * int(currentFrame) + 256, 256, -32, 32));
        }
        if (dx > 0) {
            currentFrame += animationSpeed * time;
            if (currentFrame > 4) currentFrame -= 3;
            sprite.setTextureRect(sf::IntRect(32 * int(currentFrame) + 224, 256, 32, 32));
        }
        sprite.setPosition(x + w / 2, y + h / 2);
        if (health <= 0) { life = false; }
    }
}

void Enemy::checkCollisionWithMap(float Dx, float Dy) {
    for (int i = 0; i < obj.size(); i++)
        if (getRect().intersects(obj[i].rect)) {
            if (obj[i].name == "solid") {
                if (Dy > 0) { life = false; }
                if (Dy < 0) { life = false; }
                if (Dx > 0) { life = false; damageDeal = true; }
                if (Dx < 0) { life = false; }
            }
        }
}