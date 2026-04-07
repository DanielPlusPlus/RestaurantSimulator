#pragma once

#include "Character.hpp"

#include <SFML/Graphics.hpp>


class Waiter : public Character {
private:
    const CharactersTexturesPaths waiterTexturesPaths = CharactersTexturesPaths{
        "assets/characters/waiter/waiter_idle.png", 
        "assets/characters/waiter/waiter_run.png", 
        "assets/characters/waiter/waiter_sit.png"
    };
    sf::Texture waiterIdleTexture;
    sf::Texture waiterRunTexture;
    sf::Texture waiterSitTexture;
    std::vector<sf::Sprite> waiterIdleSprites;
    std::vector<sf::Sprite> waiterRunSprites;
    std::vector<sf::Sprite> waiterSitSprites;
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

    bool loadTextures(int scaleFactor);
    void changeAnimation(float deltaTime);
    void changeState(float deltaTime, int scaleFactor);
public:
    Waiter(int scaleFactor, float tileWidth, float tileHeight, float wallWidth);
    void update(float deltaTime, int scaleFactor);
    void render(sf::RenderWindow* window) override;
};
