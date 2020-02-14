#include "Player.h"

Player::Player(sf::Image& image, Level& lev, sf::String Name, float X, float Y, int W, int H) :
	Entity(image, X, Y, W, H, Name), state(stay) {

    obj = lev.GetAllObjects();
    health = 4;
    if (name == "player1")
    {
        sprite.setTextureRect(sf::IntRect(96, 32, w, h));
    }
}

void Player::control(float time)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        state = left;
        speed = 0.15;
        currentFrame += 0.005 * time;
        if (currentFrame > 4) currentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(32 * int(currentFrame) + 288, 32, -32, 32));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        state = right;
        speed = 0.15;
        currentFrame += 0.005 * time;
        if (currentFrame > 4) currentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(32 * int(currentFrame) + 256, 32, 32, 32));
    }

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
        state = up;
        speed = 0.15;
        currentFrame += 0.005 * time;
        if (currentFrame > 4) currentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(32 * int(currentFrame) + 128, 32, 32, 32));
    }

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {
        state = down;
        speed = 0.15;
        currentFrame += 0.005 * time;
        if (currentFrame > 4) currentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(32 * int(currentFrame), 32, 32, 32));
    }
}

void Player::update(float time)
{
    if (life) {
        control(time);
        switch (state)
        {
        case right: dx = speed; dy = 0; break;
        case left: dx = -speed; dy = 0; break;
        case up: dx = 0; dy = -speed; break;
        case down: dx = 0;  dy = speed; break;
        case stay: dx = 0; dy = 0; break;
        }
        x += dx * time;
        checkCollisionWithMap(dx, 0);
        y += dy * time;
        checkCollisionWithMap(0, dy);

        speed = 0;

        sprite.setPosition(x + w / 2, y + h / 2); 
    }

    if (health <= 0) { life = false; }
}

void Player::checkCollisionWithMap(float Dx, float Dy)
{
    for (int i = 0; i < obj.size(); i++)//���������� �� ��������
        if (getRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
        {
            if (obj[i].name == "solid")//���� ��������� �����������
            {
                if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; }
                if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
                if (Dx > 0) { x = obj[i].rect.left - w; }
                if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
            }
        }
}