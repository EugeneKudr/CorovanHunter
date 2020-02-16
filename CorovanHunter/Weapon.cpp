#include "Weapon.h"

Weapon::Weapon() {
    delay = false;
    delayTime = 0;
    maxDelayTime = 100;
    ammo = 20;
    maxAmmo = 20;
    recharge = false;
    rechargeTime = 500;
    weaponDamage = 50;

    reloadBuffer.loadFromFile("audio/reload.ogg");
    reload.setBuffer(reloadBuffer);
    reload.setVolume(10);
}

void Weapon::update(int playerScore) {
    if (playerScore > 50) {
        maxDelayTime = 50;
        maxAmmo = 40;
        if (playerScore > 130) {
            maxDelayTime = 25;
            maxAmmo = 100;
            if (playerScore > 250) {
                weaponDamage = 100;
            }
        }
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