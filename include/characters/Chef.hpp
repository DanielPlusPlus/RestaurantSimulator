#pragma once

#include "Character.hpp"
#include "items/DishesManager.hpp"
#include "enums/ChefStatesEnum.hpp"

#include <queue>


class Chef : public Character {
private:
    const CharactersTexturesPaths chefTexturesPaths = CharactersTexturesPaths{
        "assets/characters/chef/chef_idle.png", 
        "assets/characters/chef/chef_run.png"
    };
    int chefNumber = 0;
    sf::Texture chefIdleTexture;
    sf::Texture chefRunTexture;
    sf::Texture chefSitTexture;
    std::vector<sf::Sprite> chefIdleSprites;
    std::vector<sf::Sprite> chefRunSprites;
    float width = 16.0f;
    float height = 32.0f;
    bool texturesLoaded = false;
    int animFrame = 0;
    float animTime = 0.0f;
    enum Directions startAnimDirection = Directions::UP;
    enum Directions animDirection = Directions::UP;

    enum ChefStatesEnum state = ChefStatesEnum::WAITING_TO_COOKING;
    Positions destinationPositions;
    float moveProgress = 0.0f;
    float moveDistance = 0.0f;
    float moveSpeed = 0.0f;
    float idleTimer = 0.0f;
    float cookingTime = 0.0f;

    std::queue<int> tablesNumbersToCookFor;

    DishesManager* dishesManager;

    bool loadTextures(int scaleFactor);
    void changeAnimation(float deltaTime);
    void changeState(float deltaTime, int scaleFactor, int* addedDishesNumber);
    enum ChefStatesEnum defineStateByStartDirection();
public:
    Chef(int scaleFactor, float tileWidth, float tileHeight, float moveXSpeed, 
        float moveYSpeed, int chefsNumber, Positions startPositions, Directions startDirection,
        DishesManager* dishesManager);
    void addTableToCookFor(int tableNumber);
    int getDishesToCookForNumber() {
        return tablesNumbersToCookFor.size();
    }
    void update(float deltaTime, int scaleFactor, int* addedDishesNumber);
    void render(sf::RenderWindow* window) override;
    float getSortY() override {
        return positions.yPos + (height * 0.3f);
    }
    int getChefNumber() {
        return chefNumber;
    }
};