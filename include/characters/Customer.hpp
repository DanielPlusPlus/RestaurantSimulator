#pragma once

#include "Character.hpp"
#include "enums/CustomerStatesEnum.hpp"


class Customer : public Character {
private:
    int customerNumber = 0;
    sf::Texture customerIdleTexture;
    sf::Texture customerRunTexture;
    sf::Texture customerSitTexture;
    std::vector<sf::Sprite> customerIdleSprites;
    std::vector<sf::Sprite> customerRunSprites;
    std::vector<sf::Sprite> customerSitSprites;
    float width = 16.0f;
    float height = 32.0f;
    bool texturesLoaded = false;
    int animFrame = 0;
    float animTime = 0.0f;
    enum Directions animDirection = Directions::LEFT;

    enum CustomerStatesEnum state = CustomerStatesEnum::PREPARING_TO_MOVING;
    Positions queueStartingPositions;
    float moveProgress = 0.0f;
    float moveDistance = 0.0f;
    float moveSpeed = 0.0f;
    float idleTimer = 0.0f;
    float cookingTime = 0.0f;

    bool loadTextures(int scaleFactor, CharactersTexturesPaths texturesPaths);
    void changeAnimation(float deltaTime);
    void changeState(float deltaTime);
public:
    Customer(int scaleFactor, CharactersTexturesPaths texturesPaths, float tileWidth, float tileHeight, 
             float moveXSpeed, float moveYSpeed, int customerNumber, Positions startPositions, 
             Positions queueStartingPositions);
    void update(float deltaTime, int scaleFactor) override;
    void render(sf::RenderWindow* window) override;
};