#include "Entity.h"

Entity::Entity(sf::Image& image, float X, float Y, int W, int H, sf::String Name) :
    x(X), y(Y), w(W), h(H), name(Name), moveTimer(0), currentFrame(0), speed(0), dx(0), dy(0) {

    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setOrigin(w / 2, h / 2);
}

sf::FloatRect Entity::getRect() {
    return sf::FloatRect(x, y, w, h);
}