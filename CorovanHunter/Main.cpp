#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

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
    shoot.setVolume(50);

    std::list<Entity*> entities;
    std::list<Entity*>::iterator it;
    std::list<Entity*>::iterator it2;

    std::vector<Object> e = lvl.GetObjects("easyEnemy");

    for (int i = 0; i < e.size(); i++) {
        entities.push_back(new Enemy(image, lvl, "easyEnemy", e[i].rect.left, e[i].rect.top, 32, 32));
    }

    Object player = lvl.GetObject("player1");
    Player p(image, lvl, "player1", player.rect.left, player.rect.top, 32, 32);

    sf::Clock clock;
    sf::FloatRect bulletRect;
    bool delay = false;
    float delayTime = 0;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        
        clock.restart();
        time = time / 800;
        sf::Event event;

        if (delay) {
            delayTime++;
            if (delayTime > 100) {
                delayTime = 0;
                delay = false;
            }
        }

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if ((event.key.code == sf::Keyboard::P) && (!delay))
                {
                    entities.push_back(new Bullet(BulletImage, "Bullet", lvl, p.x, p.y, 8, 8, p.state));
                    shoot.play();
                    delay = true;
                }
            }
        }

        p.update(time);

        for (it = entities.begin(); it != entities.end();) {
            Entity* b = *it;
            b->update(time);
            if (b->life == false) { it = entities.erase(it); delete b; }
            else it++;
        }

        for (it = entities.begin(); it != entities.end(); it++) {
            if ((*it)->name == "Bullet") {
                bulletRect = (*it)->getRect();

                for (it2 = entities.begin(); it2 != entities.end(); it2++) {
                    if (((*it2)->name == "easyEnemy") && ((*it2)->getRect().intersects(bulletRect))) {
                        (*it2)->health -= 50;
                        (*it)->life = false;
                    }
                }
            }
        }

        changeView();
        window.setView(view);

        window.clear();
        lvl.Draw(window);

        for (it = entities.begin(); it != entities.end(); it++) {
            window.draw((*it)->sprite);
        }

        window.draw(p.sprite);
        window.display();
    }

    return 0;
}