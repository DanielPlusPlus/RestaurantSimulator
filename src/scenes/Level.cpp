#include "scenes/Level.hpp"
#include "scenes/Scene.hpp"

#include <SFML/Graphics.hpp>

Level::Level(int scaleFactor) : Scene(scaleFactor) {
    this->texturesLoaded = loadTextures(scaleFactor);
}

bool Level::loadTextures(int scaleFactor) {
    if (!backgroundTexture.loadFromFile("assets/interiors/background.png")) {
        return false;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));

    if (!wallsTexture.loadFromFile("assets/interiors/walls.png")) {
        return false;
    }
    wallsSprite.setTexture(wallsTexture);
    wallsSprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));

    if (!flowersTexture.loadFromFile("assets/interiors/flowers.png")) {
        return false;
    }
    flowersSprite.setTexture(flowersTexture);
    flowersSprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));

    return true;
}

void Level::update(sf::RenderWindow& window, float deltaTime) {
    this->timeElapsed += deltaTime;
    
    if (int(timeElapsed) % 10 < 5) {
        window.clear(sf::Color::White);
    }
    else {
        window.clear(sf::Color::Black);
    }

    if (this->timeElapsed >= 10.0f) {
        this->timeElapsed = 0.0f;
    }
}

void Level::render(sf::RenderWindow& window) {
    sf::Event event;
    while(window.pollEvent(event)) {
        if(event.type == sf::Event::Closed)
            window.close();
    }
    
    if(texturesLoaded) {
        window.draw(backgroundSprite);
        window.draw(wallsSprite);
        window.draw(flowersSprite);
    }
}