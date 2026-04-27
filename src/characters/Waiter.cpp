#include "characters/Waiter.hpp"
#include "utils/PathFinder.hpp"

#include <cmath>
#include <random>


Waiter::Waiter(int scaleFactor, float moveXSpeed, float moveYSpeed, 
               int waiterNumber, Positions startPositions, 
               Positions queueHandlingPositions, Positions dishPickupPositions, 
               Positions dishDropoffPositions, DishesManager* dishesManager) : 
               Character(startPositions), waiterNumber(waiterNumber), 
               queueHandlingPositions(queueHandlingPositions), dishPickupPositions(dishPickupPositions), 
               dishDropoffPositions(dishDropoffPositions), moveXSpeed(moveXSpeed), moveYSpeed(moveYSpeed),
               dishesManager(dishesManager) {
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

    state = WaiterStatesEnum::WAITING_TO_TASK;
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

    if(!waiterNoteTexture.loadFromFile(waiterTexturesPaths.noteTexturePath))
        return false;
    int noteFrameCount = waiterNoteTexture.getSize().x / frameWidth;
    waiterNoteSprites.clear();
    for(int i = 0; i < noteFrameCount; i++) {
        sf::Sprite sprite;
        sprite.setTexture(waiterNoteTexture);
        sprite.setTextureRect(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
        sprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));
        waiterNoteSprites.push_back(sprite);
    }

    return true;
}

void Waiter::update(float deltaTime, float tileWidth, 
                    float tileHeight, PathFinder* pathFinder) {
    changeAnimation(deltaTime);
    changeState(deltaTime, tileWidth, tileHeight, pathFinder);
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

void Waiter::changeState(float deltaTime, float tileWidth, 
                         float tileHeight, PathFinder* pathFinder) {
    switch(state) {
        case WaiterStatesEnum::PREPARING_TO_WAITING_TO_TASK:
            state = WaiterStatesEnum::WAITING_TO_TASK;
            setAssignedToTask(false);
            break;
        case WaiterStatesEnum::WAITING_TO_TASK:
            break;
        case WaiterStatesEnum::PREPARING_TO_MOVE_TO_QUEUE_HANDLING:
            state = WaiterStatesEnum::MOVING_TO_QUEUE_HANDLING;
            setAssignedToTask(true);
            pathToFollow.clear();
            currentPathIndex = 0;
            break;
        case WaiterStatesEnum::MOVING_TO_QUEUE_HANDLING:
            if(moveToDestinationPositions(queueHandlingPositions, deltaTime, 
                                          tileWidth, tileHeight, pathFinder)) {
                state = WaiterStatesEnum::PREPARING_TO_QUEUE_HANDLING;
            }
            break;
        case WaiterStatesEnum::PREPARING_TO_QUEUE_HANDLING:
            animDirection = Directions::DOWN;
            state = WaiterStatesEnum::QUEUE_HANDLING;
            movingState = WaiterStatesEnum::NO_MOVEMENT;
            idleTimer = 0.0f;
            break;
        case WaiterStatesEnum::QUEUE_HANDLING:
            idleTimer += deltaTime;
            if(idleTimer > 2.0f) {
                idleTimer = 0.0f;
                state = WaiterStatesEnum::PREPARING_TO_WAITING_TO_TASK;
            }
            break;
        case WaiterStatesEnum::PREPARING_TO_MOVE_TO_TABLE_HANDLING:
            state = WaiterStatesEnum::MOVING_TO_TABLE_HANDLING;
            pathToFollow.clear();
            currentPathIndex = 0;
            setAssignedToTask(true);
            break;
        case WaiterStatesEnum::MOVING_TO_TABLE_HANDLING:
            if(moveToDestinationPositions(tableHandlingPositions, deltaTime, 
                                          tileWidth, tileHeight, pathFinder)) {
                state = WaiterStatesEnum::PREPARING_TO_TABLE_HANDLING;
            }
            break;
        case WaiterStatesEnum::PREPARING_TO_TABLE_HANDLING: {
            animDirection = tableHandlingDirection;
            state = WaiterStatesEnum::TABLE_HANDLING;
            movingState = WaiterStatesEnum::NO_MOVEMENT;
            idleTimer = 0.0f;
            extern std::mt19937 globalRNG;
            std::uniform_int_distribution<int> dist(4, 8);
            tableHandlingTime = dist(globalRNG);
            break;
        }
        case WaiterStatesEnum::TABLE_HANDLING:
            idleTimer += deltaTime;
            if(idleTimer > tableHandlingTime) {
                idleTimer = 0.0f;
                state = WaiterStatesEnum::PREPARING_TO_WAITING_TO_TASK;
                setNewOrder(true);
            }
            break;
        case WaiterStatesEnum::PREPARING_TO_MOVE_TO_DISH_PICKUP:
            state = WaiterStatesEnum::MOVING_TO_DISH_PICKUP;
            pathToFollow.clear();
            currentPathIndex = 0;
            setAssignedToTask(true);
            break;
        case WaiterStatesEnum::MOVING_TO_DISH_PICKUP:
            if(moveToDestinationPositions(dishPickupPositions, deltaTime, 
                                          tileWidth, tileHeight, pathFinder)) {
                state = WaiterStatesEnum::PREPARING_TO_DISH_PICKUP;
            }
            break;
        case WaiterStatesEnum::PREPARING_TO_DISH_PICKUP:
            animDirection = Directions::LEFT;
            state = WaiterStatesEnum::DISH_PICKUP;
            movingState = WaiterStatesEnum::NO_MOVEMENT;
            idleTimer = 0.0f;
            break;
        case WaiterStatesEnum::DISH_PICKUP:
            if(idleTimer == 0.0f) {
                dishesManager->moveReadyDishToMoving();
            }
            idleTimer += deltaTime;
            if(idleTimer > 1.0f) {
                idleTimer = 0.0f;
                state = WaiterStatesEnum::PREPARING_TO_MOVE_TO_DISH_PUTDOWN;
            }
            break;
        case WaiterStatesEnum::PREPARING_TO_MOVE_TO_DISH_PUTDOWN:
            state = WaiterStatesEnum::MOVING_TO_DISH_PUTDOWN;
            pathToFollow.clear();
            currentPathIndex = 0;
            break;
        case WaiterStatesEnum::MOVING_TO_DISH_PUTDOWN:
            if(moveToDestinationPositions(tableHandlingPositions, deltaTime, 
                                          tileWidth, tileHeight, pathFinder)) {
                state = WaiterStatesEnum::PREPARING_TO_DISH_PUTDOWN;
            }
            break;
        case WaiterStatesEnum::PREPARING_TO_DISH_PUTDOWN:
            animDirection = Directions::DOWN;
            state = WaiterStatesEnum::DISH_PUTDOWN;
            movingState = WaiterStatesEnum::NO_MOVEMENT;
            idleTimer = 0.0f;
            break;
        case WaiterStatesEnum::DISH_PUTDOWN:
            idleTimer += deltaTime;
            if(idleTimer > 1.0f) {
                idleTimer = 0.0f;
                state = WaiterStatesEnum::PREPARING_TO_WAITING_TO_TASK;
                setIsDishToPutdown(true);
            }
            break;
        case WaiterStatesEnum::PREPARING_TO_MOVE_TO_DISH_DROPOFF:
            state = WaiterStatesEnum::MOVING_TO_DISH_DROPOFF;
            pathToFollow.clear();
            currentPathIndex = 0;
            setAssignedToTask(true);
            break;
        case WaiterStatesEnum::MOVING_TO_DISH_DROPOFF:
            if(moveToDestinationPositions(dishDropoffPositions, deltaTime, 
                                          tileWidth, tileHeight, pathFinder)) {
                state = WaiterStatesEnum::PREPARING_TO_DISH_DROPOFF;
            }
            break;
        case WaiterStatesEnum::PREPARING_TO_DISH_DROPOFF:
            animDirection = Directions::RIGHT;
            state = WaiterStatesEnum::DISH_DROPOFF;
            movingState = WaiterStatesEnum::NO_MOVEMENT;
            idleTimer = 0.0f;
            break;
        case WaiterStatesEnum::DISH_DROPOFF:
            idleTimer += deltaTime;
            if(idleTimer > 2.0f) {
                idleTimer = 0.0f;
                state = WaiterStatesEnum::PREPARING_TO_WAITING_TO_TASK;
            }
            break;
        default:
            break;
    }
}

bool Waiter::moveToDestinationPositions(Positions destinationPositions, float deltaTime, 
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

void Waiter::updateDirection(Positions nextPosition) {
    float dx = nextPosition.xPos - positions.xPos;
    float dy = nextPosition.yPos - positions.yPos;
    
    if(std::abs(dy) > std::abs(dx)) {
        if(dy < 0) {
            animDirection = Directions::UP;
            movingState = WaiterStatesEnum::MOVING_UP;
        }
        else {
            animDirection = Directions::DOWN;
            movingState = WaiterStatesEnum::MOVING_DOWN;
        }
    }
    else {
        if(dx < 0) {
            animDirection = Directions::LEFT;
            movingState = WaiterStatesEnum::MOVING_LEFT;
        }
        else {
            animDirection = Directions::RIGHT;
            movingState = WaiterStatesEnum::MOVING_RIGHT;
        }
    }
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

    if(state == WaiterStatesEnum::TABLE_HANDLING && 
       animDirection == Directions::DOWN) {
        spriteSet = &waiterNoteSprites;
    }
    
    int spriteIndex;
    if(state == WaiterStatesEnum::TABLE_HANDLING && 
       animDirection == Directions::DOWN) {
        spriteIndex = animFrame;
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

void Waiter::setTableNumberAndPositions(int scaleFactor, 
                                        int tableNumber, 
                                        Positions tableHandlingPositions) {
    this->tableNumber = tableNumber;
    this->tableHandlingPositions.xPos = tableHandlingPositions.xPos * scaleFactor;
    this->tableHandlingPositions.yPos = tableHandlingPositions.yPos * scaleFactor;
}