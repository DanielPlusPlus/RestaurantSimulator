#include "characters/Customer.hpp"
#include "utils/PathFinder.hpp"

#include <cmath>


Customer::Customer(int scaleFactor, CharactersTexturesPaths texturesPaths, float tileWidth, float tileHeight, 
                   float moveXSpeed, float moveYSpeed, Positions startPositions, 
                   Positions queueStartingPositions, Positions enterRestaurantPositions, 
                   Positions exitRestaurantPositions
                   ) : Character(startPositions), moveXSpeed(moveXSpeed), 
                       moveYSpeed(moveYSpeed), 
                       queueStartingPositions(queueStartingPositions), 
                       enterRestaurantPositions(enterRestaurantPositions),
                       exitRestaurantPositions(exitRestaurantPositions) {
    texturesLoaded = loadTextures(scaleFactor, texturesPaths);
    width *= scaleFactor;
    height *= scaleFactor;
    this->startPositions.xPos *= scaleFactor;
    this->startPositions.yPos *= scaleFactor;
    this->positions.xPos *= scaleFactor;
    this->positions.yPos *= scaleFactor;
    this->queueStartingPositions.xPos *= scaleFactor;
    this->queueStartingPositions.yPos *= scaleFactor;
    this->enterRestaurantPositions.xPos *= scaleFactor;
    this->enterRestaurantPositions.yPos *= scaleFactor;
    this->exitRestaurantPositions.xPos *= scaleFactor;
    this->exitRestaurantPositions.yPos *= scaleFactor;
    this->resignationPositions.xPos = this->startPositions.xPos;
    this->resignationPositions.yPos = this->startPositions.yPos + tileHeight;
    this->leavingPositions.xPos = 0.0f - tileWidth;
    this->leavingPositions.yPos = this->startPositions.yPos;

    state = CustomerStatesEnum::PREPARING_TO_MOVE;
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

void Customer::updateIfWaiting(float deltaTime, float queueXPos) {
    changeAnimation(deltaTime);
    changeWaitingState(deltaTime, queueXPos);
}

void Customer::updateIfResigning(float deltaTime) {
    changeAnimation(deltaTime);
    changeResigningState(deltaTime);
}

void Customer::updateIfEntered(float deltaTime, 
                               float tileWidth, float tileHeight, 
                               PathFinder* pathFinder, 
                               int* eatenDishesNumberCounter) {
    changeAnimation(deltaTime);
    changeEnterState(deltaTime, 
                     tileWidth, tileHeight, 
                     pathFinder, 
                     eatenDishesNumberCounter);
}

void Customer::updateIfLeaving(float deltaTime) {
    changeAnimation(deltaTime);
    changeLeavingState(deltaTime);
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
            state = CustomerStatesEnum::WAITING_TO_ENTER;
            break;
        case CustomerStatesEnum::WAITING_TO_ENTER:
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

void Customer::changeEnterState(float deltaTime, 
                                float tileWidth, float tileHeight, 
                                PathFinder* pathFinder, 
                                int* eatenDishesNumberCounter) {
    switch(state) {
        case CustomerStatesEnum::PREPARING_TO_ENTER_RESTAURANT:
            animDirection = Directions::UP;
            state = CustomerStatesEnum::ENTER_TO_RESTAURANT;
            movingState = CustomerStatesEnum::MOVING_UP;
            break;
        case CustomerStatesEnum::ENTER_TO_RESTAURANT: {
            float moveStep = moveYSpeed * deltaTime;
            float targetY = enterRestaurantPositions.yPos;
            if(positions.yPos > targetY) {
                float remaining = positions.yPos - targetY;
                float step = (moveStep < remaining) ? moveStep : remaining;
                positions.yPos -= step;
                if(positions.yPos <= targetY) {
                    positions.yPos = targetY;
                    state = CustomerStatesEnum::PREPARING_TO_MOVE_TO_CHAIR;
                }
            }
            else {
                state = CustomerStatesEnum::PREPARING_TO_MOVE_TO_CHAIR;
            }
            break;
        }
        case CustomerStatesEnum::PREPARING_TO_MOVE_TO_CHAIR:
            state = CustomerStatesEnum::MOVING_TO_CHAIR;
            pathToFollow.clear();
            currentPathIndex = 0;
            break;
        case CustomerStatesEnum::MOVING_TO_CHAIR:
            if(moveToDestinationPositions(enterChairPositions, deltaTime, 
                                          tileWidth, tileHeight, pathFinder)) {
                state = CustomerStatesEnum::PREPARING_TO_SIT;
            }
            break;
        case CustomerStatesEnum::PREPARING_TO_SIT:
            animDirection = chairHorizontalDirection;
            state = CustomerStatesEnum::WAITING_TO_SIT;
            movingState = CustomerStatesEnum::NO_MOVEMENT;
            positions.xPos = chairPositions.xPos;
            positions.yPos = chairPositions.yPos;
            idleTimer = 0.0f;
            break;
        case CustomerStatesEnum::WAITING_TO_SIT:
            break;
        case CustomerStatesEnum::SITTING:
            break;
        case CustomerStatesEnum::PREPARING_TO_EATING:
            state = CustomerStatesEnum::EATING;
            idleTimer = 0.0f;
            break;
        case CustomerStatesEnum::EATING:
            idleTimer += deltaTime;
            if(idleTimer > eatingTime) {
                idleTimer = 0.0f;
                (*eatenDishesNumberCounter)++; 
                state = CustomerStatesEnum::PREPARING_TO_MOVE_TO_EXIT;
            }
            break;
        case CustomerStatesEnum::PREPARING_TO_MOVE_TO_EXIT:
            state = CustomerStatesEnum::MOVING_TO_EXIT;
            positions.xPos = enterChairPositions.xPos;
            positions.yPos = enterChairPositions.yPos;
            pathToFollow.clear();
            currentPathIndex = 0;
            break;
        case CustomerStatesEnum::MOVING_TO_EXIT:
            if(moveToDestinationPositions(exitRestaurantPositions, deltaTime, 
                                          tileWidth, tileHeight, pathFinder)) {
                state = CustomerStatesEnum::TURNING_DOWN;
            }
            break;
        case CustomerStatesEnum::TURNING_DOWN:
            animDirection = Directions::DOWN;
            state = CustomerStatesEnum::WAITING_TO_LEAVE;
            movingState = CustomerStatesEnum::NO_MOVEMENT;
            break;
        case CustomerStatesEnum::WAITING_TO_LEAVE:
            break;
        default:
            break;
    }
}

void Customer::changeLeavingState(float deltaTime) {
    switch(state) {
        case CustomerStatesEnum::TURNING_DOWN:
            animDirection = Directions::DOWN;
            state = CustomerStatesEnum::MOVING_DOWN;
            break;
        case CustomerStatesEnum::MOVING_DOWN: {
            float moveStep = moveYSpeed * deltaTime;
            float targetY = leavingPositions.yPos;
            if(positions.yPos < targetY) {
                float remaining = targetY - positions.yPos;
                float step = (moveStep < remaining) ? moveStep : remaining;
                positions.yPos += step;
                if(positions.yPos >= targetY) {
                    positions.yPos = targetY;
                    state = CustomerStatesEnum::TURNING_LEFT;
                }
            }
            else {
                state = CustomerStatesEnum::TURNING_LEFT;
            }
            break;
        }
        case CustomerStatesEnum::TURNING_LEFT:
            animDirection = Directions::LEFT;
            state = CustomerStatesEnum::MOVING_LEFT;
            break;
        case CustomerStatesEnum::MOVING_LEFT: {
            float moveStep = moveXSpeed * deltaTime;
            float targetX = leavingPositions.xPos;
            if(positions.xPos > targetX) {
                float remaining = positions.xPos - targetX;
                float step = (moveStep < remaining) ? moveStep : remaining;
                positions.xPos -= step;
                if(positions.xPos <= targetX) {
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

bool Customer::moveToDestinationPositions(Positions destinationPositions, float deltaTime, 
                                          float tileWidth, float tileHeight, 
                                          PathFinder* pathFinder) {
    if(std::abs(positions.xPos - destinationPositions.xPos) == 0.0f && 
        std::abs(positions.yPos - destinationPositions.yPos) == 0.0f) {
        pathToFollow.clear();
        currentPathIndex = 0;
        return true;
    }

    if(pathToFollow.empty()) {
        pathToFollow = pathFinder->findPath(positions, destinationPositions, tileWidth, tileHeight);
        currentPathIndex = 0;

        if(pathToFollow.empty()) {
            failedCycles++;
            if(failedCycles > 5) {
                failedCycles = 0;
                return true;
            }
            return false;
        }
    }

    if(currentPathIndex < pathToFollow.size()) {
        Positions nextWaypoint = pathToFollow[currentPathIndex];
        updateDirection(nextWaypoint);

        float dx = nextWaypoint.xPos - positions.xPos;
        float dy = nextWaypoint.yPos - positions.yPos;
        float distance = std::sqrt(dx * dx + dy * dy);

        float moveDistance = moveYSpeed * deltaTime;
        
        if(distance < moveDistance) {
            positions = nextWaypoint;
            currentPathIndex++;
            failedCycles = 0;
        }
        else {
            float ratio = moveDistance / distance;
            positions.xPos += dx * ratio;
            positions.yPos += dy * ratio;
        }
    }
    else {
        pathToFollow.clear();
        currentPathIndex = 0;
        return true;
    }
    return false;
}

void Customer::updateDirection(Positions nextPosition) {
    float dx = nextPosition.xPos - positions.xPos;
    float dy = nextPosition.yPos - positions.yPos;
    
    if(std::abs(dy) > std::abs(dx)) {
        if(dy < 0) {
            animDirection = Directions::UP;
            movingState = CustomerStatesEnum::MOVING_UP;
        }
        else {
            animDirection = Directions::DOWN;
            movingState = CustomerStatesEnum::MOVING_DOWN;
        }
    }
    else {
        if(dx < 0) {
            animDirection = Directions::LEFT;
            movingState = CustomerStatesEnum::MOVING_LEFT;
        }
        else {
            animDirection = Directions::RIGHT;
            movingState = CustomerStatesEnum::MOVING_RIGHT;
        }
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
    if(movingState == CustomerStatesEnum::MOVING_LEFT || 
       movingState == CustomerStatesEnum::MOVING_DOWN || 
       movingState == CustomerStatesEnum::MOVING_RIGHT ||
       movingState == CustomerStatesEnum::MOVING_UP) {
        spriteSet = &customerRunSprites;
    }
    if(state == CustomerStatesEnum::SITTING ||
       state == CustomerStatesEnum::PREPARING_TO_EATING ||
       state == CustomerStatesEnum::EATING) {
        spriteSet = &customerSitSprites;
    }
    
    int spriteIndex;
    if(state == CustomerStatesEnum::SITTING ||
       state == CustomerStatesEnum::PREPARING_TO_EATING ||
       state == CustomerStatesEnum::EATING) {
        int directionIndex = (animDirection == Directions::LEFT) ? 0 : 1;
        spriteIndex = directionIndex * framesPerAnim + animFrame;
    }
    else {
        spriteIndex = static_cast<int>(animDirection) * framesPerAnim + animFrame;
    }
    
    if(texturesLoaded && spriteIndex < spriteSet->size()) {
        sf::Sprite sprite = spriteSet->at(spriteIndex);
        sprite.setPosition(positions.xPos, positions.yPos);
        window->draw(sprite);
    }
}

void Customer::setTableNumberChairAndEnterChairPositions(int scaleFactor, 
                                                         int tableNumber, 
                                                         Positions chairPositions, 
                                                         Positions enterChairPositions) {
    this->tableNumber = tableNumber;
    this->chairPositions.xPos = chairPositions.xPos * scaleFactor;
    this->chairPositions.yPos = chairPositions.yPos * scaleFactor;
    this->enterChairPositions.xPos = enterChairPositions.xPos * scaleFactor;
    this->enterChairPositions.yPos = enterChairPositions.yPos * scaleFactor;
}