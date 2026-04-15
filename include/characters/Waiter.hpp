#pragma once

#include "Character.hpp"
#include "enums/WaiterStatesEnum.hpp"



class PathFinder;

class Waiter : public Character {
private:
    const CharactersTexturesPaths waiterTexturesPaths = CharactersTexturesPaths{
        "assets/characters/waiter/waiter_idle.png", 
        "assets/characters/waiter/waiter_run.png", 
        "assets/characters/waiter/waiter_sit.png"
    };
    int waiterNumber = 0;
    sf::Texture waiterIdleTexture;
    sf::Texture waiterRunTexture;
    sf::Texture waiterSitTexture;
    std::vector<sf::Sprite> waiterIdleSprites;
    std::vector<sf::Sprite> waiterRunSprites;
    std::vector<sf::Sprite> waiterSitSprites;
    float width = 16.0f;
    float height = 32.0f;
    bool texturesLoaded = false;
    int animFrame = 0;
    float animTime = 0.0f;
    enum Directions animDirection = Directions::DOWN;

    enum WaiterStatesEnum state = WaiterStatesEnum::MOVING_TO_QUEUE_HANDLING;
    enum WaiterStatesEnum movingState = WaiterStatesEnum::NO_MOVEMENT;
    Positions queueHandlingPositions;
    Positions dishPickupPositions;
    Positions dishDropoffPositions;
    Positions lastCyclePosition;
    float moveProgress = 0.0f;
    float moveDistance = 0.0f;
    float moveXSpeed = 0.0f;
    float moveYSpeed = 0.0f;
    float idleTimer = 0.0f;
    int failedCycles = 0;
    
    std::vector<Positions> pathToFollow;
    int currentPathIndex = 0;

    bool loadTextures(int scaleFactor);
    void changeAnimation(float deltaTime);
    void changeState(float deltaTime, int scaleFactor, float tileWidth, float tileHeight, PathFinder* pathFinder);
    bool moveToDestinationPositions(Positions destinationPositions, float deltaTime, 
                                    float tileWidth, float tileHeight, PathFinder* pathFinder);
    void updateDirection(Positions nextPosition);
public:
    Waiter(int scaleFactor, float moveXSpeed, float moveYSpeed, 
           int waiterNumber, Positions startPositions, 
           Positions queueHandlingPositions, Positions dishPickupPositions, 
           Positions dishDropoffPositions);
    void update(float deltaTime, int scaleFactor, float tileWidth, float tileHeight, PathFinder* pathFinder);
    void render(sf::RenderWindow* window) override;
};
