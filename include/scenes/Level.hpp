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
    bool texturesLoaded = false;
    float tileWidth = 16.0f;
    float tileHeight = 16.0f;
    DishesManager* dishesManager;
    TablesManager* tablesManager;
    CharactersManager* charactersManager;
    PathFinder* pathFinder;

    bool loadTextures(int scaleFactor) override;
public:
    Level(int scaleFactor, int chefsNumber, int waitersNumber, 
          int twoChairsTablesNumber, int fourChairsTablesNumber, 
          int timeToEndSimulationInMinutes);
    void update(float deltaTime, sf::RenderWindow* window) override;
    bool changeScene(enum ScenesEnum* sceneName) override;
    void render(sf::RenderWindow* window) override;
    bool isValidPositions(Positions positions);
};