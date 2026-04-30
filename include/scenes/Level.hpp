#pragma once

#include "Scene.hpp"
#include "items/DishesManager.hpp"
#include "interiors/TablesManager.hpp"
#include "characters/CharactersManager.hpp"
#include "utils/PathFinder.hpp"


class Level : public Scene {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture kitchenWallsTexture;
    sf::Sprite kitchenWallsSprite;
    sf::Texture entranceWallsTexture;
    sf::Sprite entranceWallsSprite;
    sf::Texture flowersTexture;
    sf::Sprite flowersSprite;
    sf::Font font;
    sf::Text timeLabelText;
    sf::Text timeValueText;
    sf::Text speedMultiplierLabelText;
    sf::Text speedMultiplierValueText;
    bool texturesLoaded = false;
    bool fontLoaded = false;
    float tileWidth = 16.0f;
    float tileHeight = 16.0f;
    int fontSize = 8;
    DishesManager* dishesManager;
    TablesManager* tablesManager;
    CharactersManager* charactersManager;
    PathFinder* pathFinder;

    int timeToEndSimulationInMinutes = 0;
    int speedMultiplier = 5;
    int secondsNumber = 0;
    int minutesNumber = 0;
    float simulationTime = 0.0f;

    int* totalCustomersNumberCounterPtr;
    int* resigningCustomersNumberCounterPtr;
    int* insideCustomersNumberCounterPtr;
    int* leavingCustomersNumberCounterPtr;
    int* orderedDishesNumberCounterPtr;
    int* preparedDishesNumberCounterPtr;
    int* servedDishesNumberCounterPtr;
    int* eatenDishesNumberCounterPtr;
    int* droppedDishesNumberCounterPtr;

    bool loadTextures(int scaleFactor) override;
    void configureTextsStyles();
    void updateValuesTexts();
    void updateTextsPositions();
    bool isMouseOverText(sf::RenderWindow* window, sf::Text text);
    void updateHoverState(sf::RenderWindow* window);
    void handleMouseClick(sf::RenderWindow* window, bool isLeftClick);
public:
    Level(int scaleFactor, int chefsNumber, int waitersNumber, 
          int twoChairsTablesNumber, int fourChairsTablesNumber, 
          int timeToEndSimulationInMinutes, 
          int* totalCustomersNumberCounterPtr,
          int* resigningCustomersNumberCounterPtr,
          int* insideCustomersNumberCounterPtr,
          int* leavingCustomersNumberCounterPtr,
          int* orderedDishesNumberCounterPtr,
          int* preparedDishesNumberCounterPtr,
          int* servedDishesNumberCounterPtr,
          int* eatenDishesNumberCounterPtr,
          int* droppedDishesNumberCounterPtr);
    ~Level();
    void update(float deltaTime, sf::RenderWindow* window) override;
    bool changeScene(enum ScenesEnum* sceneName) override;
    void render(sf::RenderWindow* window) override;
    bool isValidPositions(Positions positions);
};