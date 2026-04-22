#include "scenes/Level.hpp"

#include <SFML/Graphics.hpp>


Level::Level(int scaleFactor) : Scene(scaleFactor) {
    tileWidth *= scaleFactor;
    tileHeight *= scaleFactor;
    dishesManager = new DishesManager(scaleFactor);
    tablesManager = new TablesManager(scaleFactor, 8, 3); // do poprawy - liczba stolików powinna być parametrem, a nie stałą
    charactersManager = new CharactersManager(scaleFactor, tileWidth, tileHeight, 3, 3, dishesManager); // do poprawy - liczba postaci powinna być parametrem, a nie stałą
    pathFinder = new PathFinder(this);
    this->texturesLoaded = loadTextures(scaleFactor);
}

bool Level::loadTextures(int scaleFactor) {
    if (!backgroundTexture.loadFromFile("assets/interiors/background.png")) {
        return false;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));

    if (!kitchenWallsTexture.loadFromFile("assets/interiors/kitchen_walls.png")) {
        return false;
    }
    kitchenWallsSprite.setTexture(kitchenWallsTexture);
    kitchenWallsSprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));

    if (!entranceWallsTexture.loadFromFile("assets/interiors/entrance_walls.png")) {
        return false;
    }
    entranceWallsSprite.setTexture(entranceWallsTexture);
    entranceWallsSprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));

    if (!flowersTexture.loadFromFile("assets/interiors/flowers.png")) {
        return false;
    }
    flowersSprite.setTexture(flowersTexture);
    flowersSprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));

    return true;
}

void Level::update(float deltaTime, sf::RenderWindow* window) {
    (void)window;
    this->charactersManager->update(deltaTime, scaleFactor, tileWidth, 
                                    tileHeight, tablesManager, pathFinder);
}

bool Level::changeScene(enum ScenesEnum* sceneName) {
    if(isSceneToChange == true) {
        *sceneName = ScenesEnum::SUMMARY;
        return true;
    }
    return false;
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
        this->charactersManager->renderChefs(window);
        window->draw(kitchenWallsSprite);
        this->tablesManager->render(window);
        this->dishesManager->render(window);
        window->draw(entranceWallsSprite);
        this->charactersManager->renderWaitersAndCustomers(window);
    }
}

bool Level::isValidPositions(Positions positions) {
    if(positions.xPos >= (151.0f * scaleFactor) && 
      positions.xPos <= (280.0f * scaleFactor) && 
      positions.yPos == (24.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (151.0f * scaleFactor) 
       && positions.xPos <= (212.0f * scaleFactor) 
       && positions.yPos > (24.0f * scaleFactor) 
       && positions.yPos <= (56.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (151.0f * scaleFactor) 
       && positions.xPos <= (212.0f * scaleFactor) 
       && positions.yPos > (24.0f * scaleFactor) 
       && positions.yPos <= (56.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (70.0f * scaleFactor) 
       && positions.xPos <= (88.0f * scaleFactor)
       && positions.yPos == (72.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos > (151.0f * scaleFactor) 
       && positions.xPos <= (280.0f * scaleFactor)
       && positions.yPos == (72.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (151.0f * scaleFactor) 
       && positions.xPos <= (212.0f * scaleFactor)
       && positions.yPos > (56.0f * scaleFactor)
       && positions.yPos <= (72.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (7.0f * scaleFactor) 
       && positions.xPos <= (212.0f * scaleFactor)
       && positions.yPos == (88.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (70.0f * scaleFactor) 
       && positions.xPos <= (88.0f * scaleFactor)
       && positions.yPos > (72.0f * scaleFactor)
       && positions.yPos <= (88.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (151.0f * scaleFactor) 
       && positions.xPos <= (212.0f * scaleFactor) 
       && positions.yPos > (72.0f * scaleFactor)
       && positions.yPos <= (88.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (52.0f * scaleFactor) 
       && positions.xPos <= (280.0f * scaleFactor) 
       && positions.yPos == (104.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (52.0f * scaleFactor) 
       && positions.xPos <= (212.0f * scaleFactor) 
       && positions.yPos > (88.0f * scaleFactor)
       && positions.yPos <= (104.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (7.0f * scaleFactor) 
       && positions.xPos <= (212.0f * scaleFactor) 
       && positions.yPos == (120.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (52.0f * scaleFactor) 
       && positions.xPos <= (212.0f * scaleFactor) 
       && positions.yPos > (104.0f * scaleFactor)
       && positions.yPos <= (120.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (101.0f * scaleFactor) 
       && positions.xPos <= (164.0f * scaleFactor)
       && positions.yPos > (120.0f * scaleFactor)
       && positions.yPos <= (136.0f * scaleFactor)) { 
        return true;
    }
    if(positions.xPos >= (7.0f * scaleFactor) 
       && positions.xPos <= (280.0f * scaleFactor) 
       && positions.yPos == (152.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (101.0f * scaleFactor) 
       && positions.xPos <= (164.0f * scaleFactor)
       && positions.yPos > (136.0f * scaleFactor)
       && positions.yPos <= (152.0f * scaleFactor)) { 
        return true;
    }
    if(positions.xPos >= (131.0f * scaleFactor) 
       && positions.xPos <= (171.0f * scaleFactor)
       && positions.yPos > (152.0f * scaleFactor) 
       && positions.yPos <= (168.0f * scaleFactor)) {
        return true;
    }
    return false;
} 