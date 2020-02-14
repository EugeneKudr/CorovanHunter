#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "level.h"

class Entity
{
public:
    std::vector<Object> obj;

    sf::Texture texture;
    sf::Sprite sprite;
    sf::String name;

    float x;
    float y;
    float dx;
    float dy;
    float speed;
    float moveTimer;
    float currentFrame;
    int w;
    int h;
    int health;
    bool life;
    bool damageDeal;

    Entity(sf::Image& image, float X, float Y, int W, int H, sf::String Name);

    sf::FloatRect getRect();

    virtual void update(float time) = 0;
};

