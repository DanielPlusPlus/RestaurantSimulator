#include "scenes/Level.hpp"
#include "scenes/Scene.hpp"

#include <SFML/Graphics.hpp>


Level::Level(int scaleFactor) : Scene(scaleFactor) {
    tileWidth *= scaleFactor;
    tileHeight *= scaleFactor;
    dishesManager = new DishesManager(scaleFactor);
    tablesManager = new TablesManager(scaleFactor, 8, 3); // do poprawy - liczba stolików powinna być parametrem, a nie stałą
    charactersManager = new CharactersManager(scaleFactor, tileWidth, tileHeight, 3, 0, dishesManager); // do poprawy - liczba postaci powinna być parametrem, a nie stałą
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

void Level::update(float deltaTime) {
    this->charactersManager->update(deltaTime, scaleFactor);
}

void Level::render(sf::RenderWindow* window) {
    sf::Event event;
    while(window->pollEvent(event)) {
        if(event.type == sf::Event::Closed)
            window->close();
    }
    
    if(texturesLoaded) {
        window->draw(backgroundSprite);
        window->draw(flowersSprite);
        window->draw(wallsSprite);
        this->charactersManager->render(window);
        this->dishesManager->render(window);
        this->tablesManager->render(window);
    }
}