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

int main() {
    extern sf::View view;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "korovan hunter 2.2.8 alpha");
    view.reset(sf::FloatRect(0, 0, 1280, 720));

    Level lvl;
    lvl.LoadFromFile("map/gameMap.tmx");

    sf::Image image;
    image.loadFromFile("images/sprites.png");
    image.createMaskFromColor(sf::Color(255, 0, 255));
 
    sf::Image BulletImage;
    BulletImage.loadFromFile("images/bullet.png");
    BulletImage.createMaskFromColor(sf::Color(0, 0, 0));

    sf::SoundBuffer shootBuffer;
    shootBuffer.loadFromFile("audio/shoot.ogg");
    sf::Sound shoot;
    shoot.setBuffer(shootBuffer);
    shoot.setVolume(1);

    sf::Music archerTheme;
    archerTheme.openFromFile("audio/archer.ogg");
    archerTheme.setVolume(5);
    archerTheme.play();
    archerTheme.setLoop(true);

    std::list<Entity*> enemies;
    std::list<Entity*> bullets;
    std::list<Entity*>::iterator it;
    std::list<Entity*>::iterator it2;

    std::vector<Object> e = lvl.GetObjects("easyEnemy");

    Object player = lvl.GetObject("player1");
    Player p(image, lvl, "player1", player.rect.left, player.rect.top, 32, 32);

    sf::Clock clock;
    sf::FloatRect bulletRect;
    bool delay = false;
    float delayTime = 0;
    int createObjectForMapTimer = 0;
    int spawnChance;
    int playerScore = 0;
    ScoreBar playerScoreBar;
    int recharge = 100;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        
        clock.restart();
        time = time / 800;
        sf::Event event;

        if (playerScore > 50) {
            recharge = 50;
            if (playerScore > 130) {
                recharge = 25;
                
            }
        }

        if (delay) {
            delayTime++;
            if (delayTime > recharge) {
                delayTime = 0;
                delay = false;
            }
        }

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

        if ((p.life) && (p.isShoot) && (!delay)) {
            bullets.push_back(new Bullet(BulletImage, "Bullet", lvl, p.x, p.y + 13, 8, 8, p.state));
            shoot.play();
            delay = true;
        }

        createObjectForMapTimer += time;
        int spawnThreshold = 3000 - playerScore * 15;
        if (spawnThreshold < 500) spawnThreshold = 500;
        if (createObjectForMapTimer > spawnThreshold) {
            for (int i = 0; i < e.size(); i++) {
                spawnChance = rand() % 10;
                if ((spawnChance < 2) && (p.life)) {
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

        for (it = bullets.begin(); it != bullets.end();) {
            (*it)->update(time);

            if (!(*it)->life) {
                delete (*it);
                it = bullets.erase(it);
            }
            else it++;
        }

        for (it = bullets.begin(); it != bullets.end(); it++) {
            bulletRect = (*it)->getRect();
            for (it2 = enemies.begin(); it2 != enemies.end(); it2++) {
                if ((*it2)->getRect().intersects(bulletRect)) {
                    (*it2)->health -= 50;
                    (*it)->life = false;
                }
            }
        }

        playerScoreBar.update(playerScore, p.health);

        changeView();
        window.setView(view);

        window.clear();
        lvl.Draw(window);

        for (it = enemies.begin(); it != enemies.end(); it++) {
            window.draw((*it)->sprite);
        }

        for (it = bullets.begin(); it != bullets.end(); it++) {
            window.draw((*it)->sprite);
        }

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