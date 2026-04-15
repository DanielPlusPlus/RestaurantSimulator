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

    enum CustomerStatesEnum state = CustomerStatesEnum::PREPARING_TO_MOVE;
    Positions queueStartingPositions;
    Positions resignationPositions;
    Positions chairPositions;
    Positions enterChairPositions;
    float moveProgress = 0.0f;
    float moveDistance = 0.0f;
    float moveXSpeed = 0.0f;
    float moveYSpeed = 0.0f;
    float idleTimer = 0.0f;

    float previousQueueXPos = 0.0f;
    bool resigning = false;
    bool assignedToRemove = false;
    bool entered = false;

    bool loadTextures(int scaleFactor, CharactersTexturesPaths texturesPaths);
    void changeAnimation(float deltaTime);
    void changeWaitingState(float deltaTime, float queueXPos);
    void changeResigningState(float deltaTime);
    bool getResigningStatus() {
        return resigning;
    }
    void setAssignedToRemove(bool value) {
        assignedToRemove = value;
    }
public:
    Customer(int scaleFactor, CharactersTexturesPaths texturesPaths, float tileWidth, float tileHeight, 
             float moveXSpeed, float moveYSpeed, int customerNumber, Positions startPositions, 
             Positions queueStartingPositions);
    void updateIfWaiting(float deltaTime, int scaleFactor, float queueXPos);
    void updateIfResigning(float deltaTime, int scaleFactor);
    void render(sf::RenderWindow* window) override;
    void setResigning(bool value) {
        resigning = value;
        state = CustomerStatesEnum::TURNING_DOWN;
    }
    void setEntered(bool value) {
        entered = value;
    }
    void setChairAndEnterChairPositions(Positions chairPositions, Positions enterChairPositions) {
        this->chairPositions = chairPositions;
        this->enterChairPositions = enterChairPositions;
    }
    bool getAssignedToRemoveStatus() {
        return assignedToRemove;
    }
};