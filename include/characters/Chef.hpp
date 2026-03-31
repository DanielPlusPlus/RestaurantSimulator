#pragma once

#include "Character.hpp"
#include "enums/ChefStatesEnum.hpp"


class Chef : public Character {
private:
    sf::Texture chefIdleTexture;
    sf::Texture chefRunTexture;
    sf::Texture chefSitTexture;
    std::vector<sf::Sprite> chefIdleSprites;
    std::vector<sf::Sprite> chefRunSprites;
    std::vector<sf::Sprite> chefSitSprites;
    float xPos = 0.0f;
    float yPos = 0.0f;
    float width = 16.0f;
    float height = 32.0f;
    bool texturesLoaded = false;
    int animFrame = 0;
    float animTime = 0.0f;
    enum Directions animDirection = Directions::UP;

    enum ChefStatesEnum state = ChefStatesEnum::COOKING;
    float moveProgress = 0.0f;
    float moveDistance = 0.0f;
    float moveSpeed = 0.0f;
    float startX = 0.0f;
    float startY = 0.0f;
    float idleTimer = 0.0f;
public:
    Chef(int scaleFactor, float tileWidth, float tileHeight, float wallWidth);
    bool loadTextures(int scaleFactor);
    void update(sf::RenderWindow& window, float deltaTime) override;
    void changeAnimation(float deltaTime);
    void changeState(float deltaTime);
    void render(sf::RenderWindow& window) override;
};