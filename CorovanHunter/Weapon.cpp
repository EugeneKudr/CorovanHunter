#include "Weapon.h"

Weapon::Weapon() {
    delay = false;
    delayTime = 0;
    maxDelayTime = 100;
    ammo = 20;
    maxAmmo = 20;
    recharge = false;
    rechargeTime = 500;
    weaponDamage = 25;
    name = "colt_45";

    reloadBuffer.loadFromFile("audio/reload.ogg");
    reload.setBuffer(reloadBuffer);
    reload.setVolume(10);
    weaponLoad(name, 12, 8);
}

void Weapon::weaponLoad(std::string name, int w, int h) {
    weapImage.loadFromFile("images/" + name + ".png");
    weapImage.createMaskFromColor(sf::Color(255, 255, 255));
    weapTexture.loadFromImage(weapImage);
    weapSprite.setTexture(weapTexture);
    weapSprite.setTextureRect(sf::IntRect(0, 0, w, h));
}

void Weapon::update(int playerScore, float x, float y) {
    weapSprite.setPosition(x + 6, y + 17);

    if ((playerScore > 10) && (name == "colt_45")) {
        name = "mp40";
        weaponLoad(name, 17, 8);
        maxDelayTime = 50;
        maxAmmo = 40;
    }

    if (delay) {
        delayTime++;
        if (delayTime > maxDelayTime) {
            delayTime = 0;
            delay = false;
        }
    }

    if (ammo <= 0) {
        if (rechargeTime == 500) {
            reload.play();
        }
        recharge = true;
        rechargeTime--;
    }

    if (rechargeTime <= 0) {
        ammo = maxAmmo;
        recharge = false;
        rechargeTime = 500;
    }
}

void Weapon::drawWeapon(sf::RenderWindow& window) {
    window.draw(weapSprite);
}