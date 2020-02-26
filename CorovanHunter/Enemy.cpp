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
        colorTime = 0;
        dieDelay = 0;
    }

    imageLife.loadFromFile("images/enemybar.png");
    t.loadFromImage(imageLife);
    s.setTexture(t);
    s.setTextureRect(sf::IntRect(0, 0, 32, 5));
    bar.setFillColor(sf::Color(255, 0, 0));
    max = health;
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

        if (((sprite.getColor() == sf::Color::Red) || (sprite.getColor() == sf::Color::Green)) && (life)) {
            colorTime += time;
            if (colorTime > 130) {
                sprite.setColor(sf::Color::White);
                colorTime = 0;
            }
        }

        sprite.setPosition(x + w / 2, y + h / 2);

        if (health <= 0) { 
            dx = 0;
            sprite.setTextureRect(sf::IntRect(96, 256, 32, 32));
            dieDelay += time;
            if (dieDelay > 240) {
                life = false;
            }
        }
    }

    if (health >= 0) {
        bar.setSize(sf::Vector2f(health * 30 / max, 3));
        s.setPosition(x - 2, y - 10);
        bar.setPosition(x - 1, y - 9);
    }
}

void Enemy::checkCollisionWithMap(float Dx, float Dy) {
    for (int i = 0; i < obj.size(); i++)
        if (getRect().intersects(obj[i].rect)) {
            if (obj[i].name == "solid") {
                if (x > 100) { life = false; damageDeal = true; }
            }
        }
}

void Enemy::drawLifeBar(sf::RenderWindow& window) {
    if (health < max) {
        window.draw(s);
        window.draw(bar);
    }
}