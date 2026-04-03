#pragma once

#include "Character.hpp"

#include <SFML/Graphics.hpp>


class Customer : public Character {
private:
    sf::Texture customerIdleTexture;
    sf::Texture customerRunTexture;
    sf::Texture customerSitTexture;
    std::vector<sf::Sprite> customerIdleSprites;
    std::vector<sf::Sprite> customerRunSprites;
    std::vector<sf::Sprite> customerSitSprites;
    Positions positions{1.0f, 1.0f};
    float width = 16.0f;
    float height = 32.0f;
    bool texturesLoaded = false;
    int animFrame = 0;
    float animTime = 0.0f;
    enum Directions animDirection = Directions::UP;

    float moveProgress = 0.0f;
    float moveDistance = 0.0f;
    float moveSpeed = 0.0f;
    float startX = 0.0f;
    float startY = 0.0f;
    float idleTimer = 0.0f;

    bool loadTextures(int scaleFactor, CharactersTexturesPaths texturesPaths);
    void changeAnimation(float deltaTime);
    void changeState(float deltaTime, int scaleFactor);
public:
    Customer(int scaleFactor, float tileWidth, float tileHeight, float wallWidth, CharactersTexturesPaths texturesPaths);
    void update(float deltaTime, int scaleFactor) override;
    void render(sf::RenderWindow* window) override;
};
