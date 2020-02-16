#pragma once

#include <SFML/Audio.hpp>

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

    Weapon();
    void update(int playerScore);
};

