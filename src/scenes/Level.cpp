#include "scenes/Level.hpp"
#include "scenes/Scene.hpp"

#include <SFML/Graphics.hpp>


Level::Level(int scaleFactor) : Scene(scaleFactor) {
    tileWidth = tileWidth * scaleFactor;
    tileHeight = tileHeight * scaleFactor;
    wallWidth = wallWidth * scaleFactor;
    dishesManager = new DishesManager(tileWidth, tileHeight, wallWidth);
    tablesManager = new TablesManager(scaleFactor, 8, 3); // do poprawy - liczba stolików powinna być parametrem, a nie stałą
    chef = new Chef(scaleFactor, tileWidth, tileHeight, wallWidth, dishesManager);
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
    this->timeElapsed += deltaTime;
    this->chef->update(deltaTime);
}

void Level::render(sf::RenderWindow* window) {
    sf::Event event;
    while(window->pollEvent(event)) {
        if(event.type == sf::Event::Closed)
            window->close();
    }
    
    if(texturesLoaded) {
        window->draw(backgroundSprite);
        window->draw(wallsSprite);
        window->draw(flowersSprite);
        this->chef->render(window);
        this->dishesManager->render(window);
        this->tablesManager->render(window);
    }
}