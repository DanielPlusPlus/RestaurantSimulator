#include "characters/Customer.hpp"


Customer::Customer(int scaleFactor, CharactersTexturesPaths texturesPaths, float tileWidth, float tileHeight, 
         float moveXSpeed, float moveYSpeed, int customerNumber, Positions startPositions, 
         Positions queueStartingPositions) : Character(startPositions), moveXSpeed(moveXSpeed), 
         moveYSpeed(moveYSpeed), customerNumber(customerNumber), 
         queueStartingPositions(queueStartingPositions) {
    texturesLoaded = loadTextures(scaleFactor, texturesPaths);
    width *= scaleFactor;
    height *= scaleFactor;
    this->startPositions.xPos *= scaleFactor;
    this->startPositions.yPos *= scaleFactor;
    this->positions.xPos *= scaleFactor;
    this->positions.yPos *= scaleFactor;
    this->queueStartingPositions.xPos *= scaleFactor;
    this->queueStartingPositions.yPos *= scaleFactor;
    this->resignationPositions.xPos = this->startPositions.xPos;
    this->resignationPositions.yPos = this->startPositions.yPos + tileHeight;

    state = CustomerStatesEnum::PREPARING_TO_MOVE;
    moveProgress = 0.0f;
    animDirection = Directions::LEFT;
}

bool Customer::loadTextures(int scaleFactor, CharactersTexturesPaths texturesPaths) {
    int frameWidth = 16;
    int frameHeight = 32;

    if(!customerIdleTexture.loadFromFile(texturesPaths.idleTexturePath))
        return false;
    int idleFrameCount = customerIdleTexture.getSize().x / frameWidth;
    customerIdleSprites.clear();
    for(int i = 0; i < idleFrameCount; i++) {
        sf::Sprite sprite;
        sprite.setTexture(customerIdleTexture);
        sprite.setTextureRect(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
        sprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));
        customerIdleSprites.push_back(sprite);
    }

    if(!customerRunTexture.loadFromFile(texturesPaths.runTexturePath))
        return false;
    int runFrameCount = customerRunTexture.getSize().x / frameWidth;
    customerRunSprites.clear();
    for(int i = 0; i < runFrameCount; i++) {
        sf::Sprite sprite;
        sprite.setTexture(customerRunTexture);
        sprite.setTextureRect(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
        sprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));
        customerRunSprites.push_back(sprite);
    }

    if(!customerSitTexture.loadFromFile(texturesPaths.sitTexturePath))
        return false;
    int sitFrameCount = customerSitTexture.getSize().x / frameWidth;
    customerSitSprites.clear();
    for(int i = 0; i < sitFrameCount; i++) {
        sf::Sprite sprite;
        sprite.setTexture(customerSitTexture);
        sprite.setTextureRect(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
        sprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));
        customerSitSprites.push_back(sprite);
    }
    return true;
}

void Customer::updateIfWaiting(float deltaTime, int scaleFactor, float queueXPos) {
    changeAnimation(deltaTime);
    changeWaitingState(deltaTime, queueXPos);
}

void Customer::updateIfResigning(float deltaTime, int scaleFactor) {
    changeAnimation(deltaTime);
    changeResigningState(deltaTime);
}

void Customer::changeAnimation(float deltaTime) {
    animTime += deltaTime;
    if(animTime > 0.2f) {
        animTime = 0.0f;
        animFrame++;
        if(animFrame >= 6) {
            animFrame = 0;
        }
    }
}

void Customer::changeWaitingState(float deltaTime, float queueXPos) {
   switch(state) {
        case CustomerStatesEnum::PREPARING_TO_MOVE:
            animDirection = Directions::LEFT;
            state = CustomerStatesEnum::MOVING_LEFT;
        break;
        case CustomerStatesEnum::MOVING_LEFT: {
            float moveStep = moveXSpeed * deltaTime;
            float startX = queueXPos;
            float targetX = positions.xPos - moveDistance;
            if(positions.xPos > queueXPos) {
                float remaining = positions.xPos - queueXPos;
                float step = (moveStep < remaining) ? moveStep : remaining;
                positions.xPos -= step;
                if(positions.xPos <= queueXPos) {
                    positions.xPos = queueXPos;
                    previousQueueXPos = queueXPos;
                    state = CustomerStatesEnum::WAITING_TO_MOVE;
                }
            }
            else {
                state = CustomerStatesEnum::WAITING_TO_MOVE;
            }
            break;
            }
        case CustomerStatesEnum::WAITING_TO_MOVE:
            if(queueXPos < previousQueueXPos) {
                state = CustomerStatesEnum::MOVING_LEFT;
            }
            else if(queueXPos <= queueStartingPositions.xPos) {
                state = CustomerStatesEnum::TURNING_UP;
            }
            break;
        case CustomerStatesEnum::TURNING_UP:
            animDirection = Directions::UP;
            break;
        default:
            break;
    }
}

void Customer::changeResigningState(float deltaTime) {
    switch(state) {
        case CustomerStatesEnum::TURNING_DOWN:
            animDirection = Directions::DOWN;
            state = CustomerStatesEnum::MOVING_DOWN;
            break;
        case CustomerStatesEnum::MOVING_DOWN: {
            float moveStep = moveYSpeed * deltaTime;
            float targetY = resignationPositions.yPos;
            if(positions.yPos < targetY) {
                float remaining = targetY - positions.yPos;
                float step = (moveStep < remaining) ? moveStep : remaining;
                positions.yPos += step;
                if(positions.yPos >= targetY) {
                    positions.yPos = targetY;
                    state = CustomerStatesEnum::TURNING_RIGHT;
                }
            }
            else {
                state = CustomerStatesEnum::TURNING_RIGHT;
            }
            break;
        }
        case CustomerStatesEnum::TURNING_RIGHT:
            animDirection = Directions::RIGHT;
            state = CustomerStatesEnum::MOVING_RIGHT;
            break;
        case CustomerStatesEnum::MOVING_RIGHT: {
            float moveStep = moveXSpeed * deltaTime;
            float targetX = resignationPositions.xPos;
            if(positions.xPos < targetX) {
                float remaining = targetX - positions.xPos;
                float step = (moveStep < remaining) ? moveStep : remaining;
                positions.xPos += step;
                if(positions.xPos >= targetX) {
                    positions.xPos = targetX;
                    state = CustomerStatesEnum::WAITING_TO_REMOVE;
                }
            }
            else {
                state = CustomerStatesEnum::WAITING_TO_REMOVE;
            }
            break;
        }
        case CustomerStatesEnum::WAITING_TO_REMOVE:
            setAssignedToRemove(true);
            break;
        default:
            break;
    }
}

void Customer::render(sf::RenderWindow* window) {
    std::vector<sf::Sprite>* spriteSet = &customerIdleSprites;

    int framesPerAnim = 6;
    if(state == CustomerStatesEnum::MOVING_LEFT || 
       state == CustomerStatesEnum::MOVING_DOWN || 
       state == CustomerStatesEnum::MOVING_RIGHT) {
        spriteSet = &customerRunSprites;
    }
    int spriteIndex = static_cast<int>(animDirection) * framesPerAnim + animFrame;
    if(texturesLoaded && spriteIndex < spriteSet->size()) {
        sf::Sprite sprite = spriteSet->at(spriteIndex);
        sprite.setPosition(positions.xPos, positions.yPos);
        window->draw(sprite);
    }
}
