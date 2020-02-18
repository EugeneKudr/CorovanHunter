#include "ScoreBar.h"

ScoreBar::ScoreBar() {
    font.loadFromFile("fonts/font1.ttf");
    text.setString("");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setOutlineColor(sf::Color::White);
    text.setOutlineThickness(1);
}

void ScoreBar::update(int score, int health, int ammo) {
    std::ostringstream playerScoreString;  
    std::ostringstream playerAmmoString;
    playerScoreString << score;
    playerAmmoString << ammo;
    text.setString("Score: " + playerScoreString.str() + "\nAmmo: " + playerAmmoString.str());

    if (health <= 0) {
        text.setCharacterSize(50);
        text.setString("GAME OVER\nSCORE: " + playerScoreString.str());
    }
}

void ScoreBar::draw(sf::RenderWindow& window) {
    sf::Vector2f center = window.getView().getCenter();
    sf::Vector2f size = window.getView().getSize();

    text.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 4);

    window.draw(text);
}

void ScoreBar::gameOver(sf::RenderWindow& window) {
    sf::Vector2f center = window.getView().getCenter();
    sf::Vector2f size = window.getView().getSize();

    text.setPosition(center.x - 128, center.y - 32);

    window.draw(text);
}