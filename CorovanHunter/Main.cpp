#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "ScoreBar.h"
#include "Weapon.h"
#include "loadObjects.h"
#include "PlayerEffects.h"

int main() {
    extern sf::View view;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "korovan hunter 2.2.8 alpha");
    view.reset(sf::FloatRect(0, 0, 1280, 720));

    Level lvl;
    lvl.LoadFromFile("map/gameMap.tmx");

    sf::Image image;
    sf::Image BulletImage;
    sf::SoundBuffer shootBuffer;
    sf::Sound shoot;
    sf::Music archerTheme;

    preLoad(image, BulletImage, shootBuffer, shoot, archerTheme);

    std::list<Enemy*> enemies;
    std::list<Bullet*> bullets;
    std::list<Enemy*>::iterator it;
    std::list<Bullet*>::iterator it2;

    std::vector<Object> e = lvl.GetObjects("easyEnemy");

    Object player = lvl.GetObject("player1");
    Player p(image, lvl, "player1", player.rect.left, player.rect.top, 32, 32);

    sf::Clock clock;
    sf::FloatRect bulletRect;
    int createObjectForMapTimer = 0;
    int spawnChance;
    int playerScore = 0;
    ScoreBar playerScoreBar;
    Weapon pistol;
    int maxSpawnChance = 2;
    PlayerEffects fire;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        
        clock.restart();
        time = time / 800;
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::P)
                    p.isShoot = true;
            if (event.type == sf::Event::KeyReleased)
                if (event.key.code == sf::Keyboard::P)
                    p.isShoot = false;
        }

        if ((p.life) && (p.isShoot) && (!pistol.delay)) {
            if (!pistol.recharge) {
                bullets.push_back(new Bullet(BulletImage, "Bullet", lvl, p.x, p.y + 13, 8, 8, p.state));
                pistol.ammo--;
                shoot.play();
                pistol.delay = true;
                fire.gunFire();
            }
        }
        
        fire.updateFire(p.x, p.y, time);
        pistol.update(playerScore);

        createObjectForMapTimer += time;
        int spawnThreshold = 4000 - playerScore * 15;
        if (spawnThreshold < 500) spawnThreshold = 500;
        if (playerScore > 250) {
            maxSpawnChance = 3;
            if (playerScore > 350) {
                maxSpawnChance = 4;
                if (playerScore > 500) {
                    maxSpawnChance = 7;
                }
            }
        }

        if (createObjectForMapTimer > spawnThreshold) {
            for (int i = 0; i < e.size(); i++) {
                spawnChance = rand() % 10;
                if ((spawnChance < maxSpawnChance) && (p.life)) {
                    enemies.push_back(new Enemy(image, lvl, "easyEnemy", e[i].rect.left, e[i].rect.top, 32, 32));
                }
            }
            createObjectForMapTimer = 0;
        }

        p.update(time);

        for (it = enemies.begin(); it != enemies.end();) {
            (*it)->update(time);

            if ((*it)->damageDeal) {
                    p.health -= 1;
            }

            if (!p.life) {
                (*it)->dx = 0;
            }

            if (!(*it)->life) { 
                playerScore++;
                delete (*it);
                it = enemies.erase(it); 
            }
            else it++;
        }

        for (it2 = bullets.begin(); it2 != bullets.end();) {
            (*it2)->update(time);

            if (!(*it2)->life) {
                delete (*it2);
                it2 = bullets.erase(it2);
            }
            else it2++;
        }

        for (it2 = bullets.begin(); it2 != bullets.end(); it2++) {
            bulletRect = (*it2)->getRect();
            for (it = enemies.begin(); it != enemies.end(); it++) {
                if ((*it)->getRect().intersects(bulletRect)) {
                    (*it)->health -= pistol.weaponDamage;
                    (*it2)->life = false;
                }
            }
        }

        playerScoreBar.update(playerScore, p.health, pistol.ammo);

        changeView();
        window.setView(view);

        window.clear();
        lvl.Draw(window);

        for (it = enemies.begin(); it != enemies.end(); it++) {
            window.draw((*it)->sprite);
        }

        for (it2 = bullets.begin(); it2 != bullets.end(); it2++) {
            window.draw((*it2)->sprite);
        }

        window.draw(fire.sprite);

        window.draw(p.sprite);
        
        if (p.life) {
            playerScoreBar.draw(window);
        }
        else {
            playerScoreBar.gameOver(window);
        }
        window.display();
    }

    return 0;
}