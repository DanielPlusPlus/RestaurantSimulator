#include "characters/Waiter.hpp"
#include "scenes/Level.hpp"
#include <cmath>

Waiter::Waiter(int scaleFactor, float moveXSpeed, float moveYSpeed, 
               int waiterNumber, Positions startPositions, 
               Positions queueHandlingPositions, Positions dishPickupPositions, 
               Positions dishDropoffPositions) : Character(startPositions), waiterNumber(waiterNumber), 
               queueHandlingPositions(queueHandlingPositions), dishPickupPositions(dishPickupPositions), 
               dishDropoffPositions(dishDropoffPositions), moveXSpeed(moveXSpeed), moveYSpeed(moveYSpeed) {
    texturesLoaded = loadTextures(scaleFactor);
    width = width * scaleFactor;
    height = height * scaleFactor;
    
    this->startPositions.xPos *= scaleFactor;
    this->startPositions.yPos *= scaleFactor;
    this->positions.xPos *= scaleFactor;
    this->positions.yPos *= scaleFactor;
    this->queueHandlingPositions.xPos *= scaleFactor;
    this->queueHandlingPositions.yPos *= scaleFactor;
    this->dishPickupPositions.xPos *= scaleFactor;
    this->dishPickupPositions.yPos *= scaleFactor;
    this->dishDropoffPositions.xPos *= scaleFactor;
    this->dishDropoffPositions.yPos *= scaleFactor;

    state = WaiterStatesEnum::MOVING_TO_QUEUE_HANDLING;
    moveProgress = 0.0f;
    animDirection = Directions::DOWN;
}

bool Waiter::loadTextures(int scaleFactor) {
    int frameWidth = 16;
    int frameHeight = 32;

    if(!waiterIdleTexture.loadFromFile(waiterTexturesPaths.idleTexturePath))
        return false;
    int idleFrameCount = waiterIdleTexture.getSize().x / frameWidth;
    waiterIdleSprites.clear();
    for(int i = 0; i < idleFrameCount; i++) {
        sf::Sprite sprite;
        sprite.setTexture(waiterIdleTexture);
        sprite.setTextureRect(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
        sprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));
        waiterIdleSprites.push_back(sprite);
    }

    if(!waiterRunTexture.loadFromFile(waiterTexturesPaths.runTexturePath))
        return false;
    int runFrameCount = waiterRunTexture.getSize().x / frameWidth;
    waiterRunSprites.clear();
    for(int i = 0; i < runFrameCount; i++) {
        sf::Sprite sprite;
        sprite.setTexture(waiterRunTexture);
        sprite.setTextureRect(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
        sprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));
        waiterRunSprites.push_back(sprite);
    }

    if(!waiterSitTexture.loadFromFile(waiterTexturesPaths.sitTexturePath))
        return false;
    int sitFrameCount = waiterSitTexture.getSize().x / frameWidth;
    waiterSitSprites.clear();
    for(int i = 0; i < sitFrameCount; i++) {
        sf::Sprite sprite;
        sprite.setTexture(waiterSitTexture);
        sprite.setTextureRect(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
        sprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));
        waiterSitSprites.push_back(sprite);
    }
    return true;
}

void Waiter::update(float deltaTime, int scaleFactor, float tileWidth, float tileHeight, Level* level) {
    changeAnimation(deltaTime);
    changeState(deltaTime, scaleFactor, tileWidth, tileHeight, level);
}

void Waiter::changeAnimation(float deltaTime) {
    animTime += deltaTime;
    if(animTime > 0.2f) {
        animTime = 0.0f;
        animFrame++;
        if(animFrame >= 6) {
            animFrame = 0;
        }
    }
}

void Waiter::changeState(float deltaTime, int scaleFactor, float tileWidth, float tileHeight, Level* level) {
    level->isValidPositions(positions);
    switch(state) {
        case WaiterStatesEnum::PREPARING_TO_MOVE_TO_QUEUE_HANDLING:
            animDirection = Directions::DOWN;
            state = WaiterStatesEnum::MOVING_TO_QUEUE_HANDLING;
            movingState = WaiterStatesEnum::TURNING_UP;
            break;
        case WaiterStatesEnum::MOVING_TO_QUEUE_HANDLING: {
            if(moveToDestinationPositions(queueHandlingPositions, deltaTime, level)) {
                state = WaiterStatesEnum::PREPARING_TO_QUEUE_HANDLING;
            }
            break;
        }
        case WaiterStatesEnum::PREPARING_TO_QUEUE_HANDLING:
            animDirection = Directions::DOWN;
            state = WaiterStatesEnum::QUEUE_HANDLING;
            idleTimer = 0.0f;
            break;
        case WaiterStatesEnum::QUEUE_HANDLING:
            idleTimer += deltaTime;
            if(idleTimer > 1.0f) {
                idleTimer = 0.0f;
                state = WaiterStatesEnum::WAITING_TO_START;
            }
            break;
        default:
            break;
    }
}

bool Waiter::moveToDestinationPositions(Positions destinationPositions, float deltaTime, Level* level) {
    if(std::abs(positions.xPos - destinationPositions.xPos) < 1.0f && 
        std::abs(positions.yPos - destinationPositions.yPos) < 1.0f) {
        movingState = WaiterStatesEnum::TURNING_UP;
        return true;
    }

    if(movingState == WaiterStatesEnum::TURNING_UP) {
        if((std::abs(positions.xPos - lastCyclePosition.xPos) < 0.1f) && 
            (std::abs(positions.yPos - lastCyclePosition.yPos) < 0.1f)) {
            failedCycles++;
            if(failedCycles > 5) {
                failedCycles = 0;
                return true;
            }
        }
        else {
            failedCycles = 0;
        }
        lastCyclePosition = positions;
    }
    
    switch(movingState) {
        case WaiterStatesEnum::TURNING_UP:
            animDirection = Directions::UP;
            movingState = WaiterStatesEnum::MOVING_UP;
            break;
        case WaiterStatesEnum::MOVING_UP: {
            float moveStep = moveYSpeed * deltaTime;
            float targetY = destinationPositions.yPos;
            if (positions.yPos > targetY) {
                float remaining = positions.yPos - targetY;
                float step = (moveStep < remaining) ? moveStep : remaining;
                Positions newPositionsitions = positions;
                newPositionsitions.yPos -= step;
                if(level->isValidPositions(newPositionsitions)) {
                    positions.yPos = newPositionsitions.yPos;
                    if(positions.yPos <= targetY) {
                        positions.yPos = targetY;
                        movingState = WaiterStatesEnum::TURNING_RIGHT;
                    }
                }
                else {
                    movingState = WaiterStatesEnum::TURNING_RIGHT;
                }
            }
            else {
                movingState = WaiterStatesEnum::TURNING_RIGHT;
            }
            break;
        }
        case WaiterStatesEnum::TURNING_RIGHT:
            animDirection = Directions::RIGHT;
            movingState = WaiterStatesEnum::MOVING_RIGHT;
            break;
        case WaiterStatesEnum::MOVING_RIGHT: {
            float moveStep = moveXSpeed * deltaTime;
            float targetX = destinationPositions.xPos;
            if(positions.xPos < targetX) {
                float remaining = targetX - positions.xPos;
                float step = (moveStep < remaining) ? moveStep : remaining;
                Positions newPositions = positions;
                newPositions.xPos += step;
                if(level->isValidPositions(newPositions)) {
                    positions.xPos = newPositions.xPos;
                    if(positions.xPos >= targetX) {
                        positions.xPos = targetX;
                        movingState = WaiterStatesEnum::TURNING_DOWN;
                    }
                }
                else {
                    movingState = WaiterStatesEnum::TURNING_DOWN;
                }
            }
            else {
                movingState = WaiterStatesEnum::TURNING_DOWN;
            }
            break;
        }
        case WaiterStatesEnum::TURNING_DOWN:
            animDirection = Directions::DOWN;
            movingState = WaiterStatesEnum::MOVING_DOWN;
            break;
        case WaiterStatesEnum::MOVING_DOWN: {
            float moveStep = moveYSpeed * deltaTime;
            float targetY = destinationPositions.yPos;
            if (positions.yPos < targetY) {
                float remaining = targetY - positions.yPos;
                float step = (moveStep < remaining) ? moveStep : remaining;
                Positions newPositions = positions;
                newPositions.yPos += step;
                if(level->isValidPositions(newPositions)) {
                    positions.yPos = newPositions.yPos;
                    if(positions.yPos >= targetY) {
                        positions.yPos = targetY;
                        movingState = WaiterStatesEnum::TURNING_LEFT;
                    }
                }
                else {
                    movingState = WaiterStatesEnum::TURNING_LEFT;
                }
            }
            else {
                movingState = WaiterStatesEnum::TURNING_LEFT;
            }
            break;
        }
        case WaiterStatesEnum::TURNING_LEFT:
            animDirection = Directions::LEFT;
            movingState = WaiterStatesEnum::MOVING_LEFT;
            break;
        case WaiterStatesEnum::MOVING_LEFT: {
            float moveStep = moveXSpeed * deltaTime;
            float targetX = destinationPositions.xPos;
            if (positions.xPos > targetX) {
                float remaining = positions.xPos - targetX;
                float step = (moveStep < remaining) ? moveStep : remaining;
                Positions newPositions = positions;
                newPositions.xPos -= step;
                if(level->isValidPositions(newPositions)) {
                    positions.xPos = newPositions.xPos;
                    if(positions.xPos <= targetX) {
                        positions.xPos = targetX;
                        movingState = WaiterStatesEnum::TURNING_UP;
                    }
                }
                else {
                    movingState = WaiterStatesEnum::TURNING_UP;
                }
            }
            else {
                movingState = WaiterStatesEnum::TURNING_UP;
            }
            break;
        }
        default:
            break;
    }
    return false;
}

void Waiter::render(sf::RenderWindow* window) {
    std::vector<sf::Sprite>* spriteSet = &waiterIdleSprites;
    if(movingState == WaiterStatesEnum::MOVING_LEFT || 
       movingState == WaiterStatesEnum::MOVING_DOWN || 
       movingState == WaiterStatesEnum::MOVING_RIGHT ||
       movingState == WaiterStatesEnum::MOVING_UP) {
        spriteSet = &waiterRunSprites;
    }
    int framesPerAnim = 6;
    int spriteIndex = static_cast<int>(animDirection) * framesPerAnim + animFrame;
    if(texturesLoaded && spriteIndex < spriteSet->size()) {
        sf::Sprite sprite = spriteSet->at(spriteIndex);
        sprite.setPosition(positions.xPos, positions.yPos);
        window->draw(sprite);
    }
}
