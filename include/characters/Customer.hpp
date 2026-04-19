#pragma once

#include "Character.hpp"
#include "enums/CustomerStatesEnum.hpp"


class PathFinder;

class Customer : public Character {
private:
    int customerNumber = 0;
    int tableNumber = 0;
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
    enum Directions chairHorizontalDirection = Directions::RIGHT;
    enum Directions chairVerticalDirection = Directions::DOWN;

    enum CustomerStatesEnum state = CustomerStatesEnum::PREPARING_TO_MOVE;
    enum CustomerStatesEnum movingState = CustomerStatesEnum::NO_MOVEMENT;
    Positions queueStartingPositions;
    Positions resignationPositions;
    Positions leavingPositions;
    Positions enterRestaurantPositions;
    Positions exitRestaurantPositions;
    Positions chairPositions;
    Positions enterChairPositions;
    float moveProgress = 0.0f;
    float moveDistance = 0.0f;
    float moveXSpeed = 0.0f;
    float moveYSpeed = 0.0f;
    float idleTimer = 0.0f;
    int failedCycles = 0;

    float previousQueueXPos = 0.0f;
    bool assignedToRemove = false;
    bool occupyTableInstantly = false;

    std::vector<Positions> pathToFollow;
    int currentPathIndex = 0;

    bool loadTextures(int scaleFactor, CharactersTexturesPaths texturesPaths);
    void changeAnimation(float deltaTime);
    void changeWaitingState(float deltaTime, float queueXPos);
    void changeResigningState(float deltaTime);
    void changeEnterState(float deltaTime, int scaleFactor, 
                          float tileWidth, float tileHeight, 
                          PathFinder* pathFinder);
    void changeLeavingState(float deltaTime);
    void setAssignedToRemove(bool value) {
        assignedToRemove = value;
    }
    bool moveToDestinationPositions(Positions destinationPositions, float deltaTime, 
                                    float tileWidth, float tileHeight, 
                                    PathFinder* pathFinder);
    void updateDirection(Positions nextPosition);
public:
    Customer(int scaleFactor, CharactersTexturesPaths texturesPaths, float tileWidth, float tileHeight, 
             float moveXSpeed, float moveYSpeed, int customerNumber, Positions startPositions, 
             Positions queueStartingPositions, Positions enterRestaurantPositions, 
             Positions exitRestaurantPositions);
    void updateIfWaiting(float deltaTime, float queueXPos);
    void updateIfResigning(float deltaTime);
    void updateIfEntered(float deltaTime, int scaleFactor, 
                         float tileWidth, float tileHeight, 
                         PathFinder* pathFinder);
    void updateIfLeaving(float deltaTime);
    void render(sf::RenderWindow* window) override;
    void changeToResigningState() {
        state = CustomerStatesEnum::TURNING_DOWN;
    }
    void changeToEnteredState() {
        state = CustomerStatesEnum::PREPARING_TO_ENTER_RESTAURANT;
    }
    void changeToLeavingState() {
        state = CustomerStatesEnum::TURNING_DOWN;
    }
    void setTableNumber(int tableNumber) {
        this->tableNumber = tableNumber;
    }
    void setOccupyTableInstantly(bool value) {
        occupyTableInstantly = value;
    }
    void setTableNumberChairAndEnterChairPositions(int scaleFactor, 
                                                   int tableNumber, 
                                                   Positions chairPositions, 
                                                   Positions enterChairPositions);
    bool getAssignedToRemoveStatus() {
        return assignedToRemove;
    }
    bool getLeaveRestaurantStatus() {
        return state == CustomerStatesEnum::WAITING_TO_LEAVE;
    }
    void setChairHorizontalDirection(enum Directions direction) {
        chairHorizontalDirection = direction;
    }
    void setChairVerticalDirection(enum Directions direction) {
        chairVerticalDirection = direction;
    }
    int getTableNumber() {
        return tableNumber;
    }
    bool getOccupyTableInstantly() {
        return occupyTableInstantly;
    }
    Directions getChairHorizontalDirection() {
        return chairHorizontalDirection;
    }
    Directions getChairVerticalDirection() {
        return chairVerticalDirection;
    }
    bool isWaitingToEnter() {
        return state == CustomerStatesEnum::WAITING_TO_ENTER;
    }
};