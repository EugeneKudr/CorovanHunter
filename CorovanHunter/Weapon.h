#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Weapon
{
public:
    bool delay;
    float delayTime;
    int maxDelayTime;
    int ammo;
    int maxAmmo;
    bool recharge;
    int rechargeTime;
    int weaponDamage;
    sf::SoundBuffer reloadBuffer;
    sf::Sound reload;
    std::string name;

    sf::Image weapImage;
    sf::Texture weapTexture;
    sf::Sprite weapSprite;

    Weapon();
    void update(int playerScore, float x, float y);
    void drawWeapon(sf::RenderWindow& window);
    void weaponLoad(std::string name, int w, int h);
};

