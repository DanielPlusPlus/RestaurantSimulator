#pragma once

#include "Character.hpp"
#include "enums/WaiterStatesEnum.hpp"


class PathFinder;

class Waiter : public Character {
private:
    const CharactersTexturesPaths waiterTexturesPaths = CharactersTexturesPaths{
        "assets/characters/waiter/waiter_idle.png", 
        "assets/characters/waiter/waiter_run.png",
        "",
        "assets/characters/waiter/waiter_note.png"
    };
    int waiterNumber = 0;
    int tableNumber = 0;
    sf::Texture waiterIdleTexture;
    sf::Texture waiterRunTexture;
    sf::Texture waiterNoteTexture;
    std::vector<sf::Sprite> waiterIdleSprites;
    std::vector<sf::Sprite> waiterRunSprites;
    std::vector<sf::Sprite> waiterNoteSprites;
    float width = 16.0f;
    float height = 32.0f;
    bool texturesLoaded = false;
    int animFrame = 0;
    float animTime = 0.0f;
    enum Directions animDirection = Directions::DOWN;
    enum Directions tableHandlingDirection = Directions::DOWN;

    enum WaiterStatesEnum state = WaiterStatesEnum::WAITING_TO_TASK;
    enum WaiterStatesEnum movingState = WaiterStatesEnum::NO_MOVEMENT;
    Positions queueHandlingPositions;
    Positions dishPickupPositions;
    Positions dishDropoffPositions;
    Positions tableHandlingPositions;
    float moveProgress = 0.0f;
    float moveDistance = 0.0f;
    float moveXSpeed = 0.0f;
    float moveYSpeed = 0.0f;
    float idleTimer = 0.0f;
    int failedCycles = 0;
    float tableHandlingTime = 0.0f;

    bool isAssignedToTask = false;
    bool isNewOrder = false;
    
    std::vector<Positions> pathToFollow;
    int currentPathIndex = 0;

    bool loadTextures(int scaleFactor);
    void changeAnimation(float deltaTime);
    void changeState(float deltaTime, float tileWidth, 
                     float tileHeight, PathFinder* pathFinder);
    bool moveToDestinationPositions(Positions destinationPositions, float deltaTime, 
                                    float tileWidth, float tileHeight, 
                                    PathFinder* pathFinder);
    void updateDirection(Positions nextPosition);
    void setNewOrder(bool value) {
        isNewOrder = value;
    }
    bool getIsNewOrder() {
        return isNewOrder;
    }
public:
    Waiter(int scaleFactor, float moveXSpeed, float moveYSpeed, 
           int waiterNumber, Positions startPositions, 
           Positions queueHandlingPositions, Positions dishPickupPositions, 
           Positions dishDropoffPositions);
    void update(float deltaTime, float tileWidth, 
                float tileHeight, PathFinder* pathFinder);
    void render(sf::RenderWindow* window) override;
    int getWaiterNumber() {
        return waiterNumber;
    } // do usunięcia
    void setAssignedToTask(bool value) {
        isAssignedToTask = value;
    }
    bool getIsAssignedToTask() {
        return isAssignedToTask;
    }
    bool getIsQueueHandling() {
        return state == WaiterStatesEnum::QUEUE_HANDLING;
    }
    bool getIsSelectedToQueueHandling() {
        if(state == WaiterStatesEnum::PREPARING_TO_MOVE_TO_QUEUE_HANDLING) {
            return true;
        }
        if(state == WaiterStatesEnum::MOVING_TO_QUEUE_HANDLING) {
            return true;
        }
        if(state == WaiterStatesEnum::PREPARING_TO_QUEUE_HANDLING) {
            return true;
        }
        return false;
    }
    bool getIsTableHandling() {
        return state == WaiterStatesEnum::TABLE_HANDLING;
    }
    bool getIsDishPickup() {
        return state == WaiterStatesEnum::DISH_PICKUP;
    }
    bool getIsDishDropoff() {
        return state == WaiterStatesEnum::DISH_DROPOFF;
    }
    bool getIsWaitingToTask() {
        return state == WaiterStatesEnum::WAITING_TO_TASK;
    };
    void changeToQueueHandlingState() {
        state = WaiterStatesEnum::PREPARING_TO_MOVE_TO_QUEUE_HANDLING;
    }
    void changeToTableHandlingState() {
        state = WaiterStatesEnum::PREPARING_TO_MOVE_TO_TABLE;
    }
    void changeToDishPickupState() {
        state = WaiterStatesEnum::PREPARING_TO_MOVE_TO_DISH_PICKUP;
    }
    void changeToDishDropoffState() {
        state = WaiterStatesEnum::PREPARING_TO_MOVE_TO_DISH_DROPOFF;
    }
    void setTableHandlingDirection(enum Directions direction) {
        tableHandlingDirection = direction;
    }
    void setTableNumberAndPositions(int scaleFactor, 
                                    int tableNumber, 
                                    Positions tableHandlingPositions);
};
