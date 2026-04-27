#include "characters/Chef.hpp"

#include <random>


Chef::Chef(int scaleFactor, float tileWidth, float tileHeight, float moveXSpeed, 
           float moveYSpeed, int chefNumber, Positions startPositions, Directions startDirection,
           DishesManager* dishesManager) : Character(startPositions), startAnimDirection(startDirection), 
           chefNumber(chefNumber), dishesManager(dishesManager) {
    texturesLoaded = loadTextures(scaleFactor);
    width *= scaleFactor;
    height *= scaleFactor;
    this->startPositions.xPos *= scaleFactor;
    this->startPositions.yPos *= scaleFactor;
    this->positions.xPos *= scaleFactor;
    this->positions.yPos *= scaleFactor;
    destinationPositions = dishesManager->getReadyDishesPositions();
    destinationPositions.xPos -= tileWidth;

    state = ChefStatesEnum::WAITING_TO_COOKING;
    moveSpeed = moveXSpeed;
    moveProgress = 0.0f;
    animDirection = startAnimDirection;
}

bool Chef::loadTextures(int scaleFactor) {
    int frameWidth = 16;
    int frameHeight = 32;

    if(!chefIdleTexture.loadFromFile(chefTexturesPaths.idleTexturePath))
        return false;
    int idleFrameCount = chefIdleTexture.getSize().x / frameWidth;
    chefIdleSprites.clear();
    for(int i = 0; i < idleFrameCount; i++) {
        sf::Sprite sprite;
        sprite.setTexture(chefIdleTexture);
        sprite.setTextureRect(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
        sprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));
        chefIdleSprites.push_back(sprite);
    }

    if(!chefRunTexture.loadFromFile(chefTexturesPaths.runTexturePath))
        return false;
    int runFrameCount = chefRunTexture.getSize().x / frameWidth;
    chefRunSprites.clear();
    for(int i = 0; i < runFrameCount; i++) {
        sf::Sprite sprite;
        sprite.setTexture(chefRunTexture);
        sprite.setTextureRect(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
        sprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));
        chefRunSprites.push_back(sprite);
    }

    return true;
}

void Chef::update(float deltaTime, int scaleFactor) {
    changeAnimation(deltaTime);
    changeState(deltaTime, scaleFactor);
}

void Chef::changeAnimation(float deltaTime) {
    animTime += deltaTime;
    if(animTime > 0.2f) {
        animTime = 0.0f;
        animFrame++;
        if(animFrame >= 6) {
            animFrame = 0;
        }
    }
}

void Chef::changeState(float deltaTime, int scaleFactor) {
    switch(state) {
        case ChefStatesEnum::WAITING_TO_COOKING:
            if(!tablesNumbersToCookFor.empty()) {
                state = ChefStatesEnum::PREPARING_TO_COOKING;
            }
            break;
        case ChefStatesEnum::PREPARING_TO_COOKING: {
            state = ChefStatesEnum::COOKING;
            extern std::mt19937 globalRNG;
            std::uniform_int_distribution<int> dist(2, 5);
            cookingTime = dist(globalRNG);
            break;
        }
        case ChefStatesEnum::COOKING:
            idleTimer += deltaTime;
            if(idleTimer > cookingTime) {
                idleTimer = 0.0f;
                state = ChefStatesEnum::TURNING_RIGHT;
            }
            break;
        case ChefStatesEnum::TURNING_RIGHT:
            animDirection = Directions::RIGHT;
            state = ChefStatesEnum::MOVING_RIGHT;
            break;
        case ChefStatesEnum::MOVING_RIGHT: {
            float moveStep = moveSpeed * deltaTime;
            float targetX = destinationPositions.xPos;
            if(positions.xPos < destinationPositions.xPos) {
                float remaining = targetX - positions.xPos;
                float step = (moveStep < remaining) ? moveStep : remaining;
                positions.xPos += step;
                if(positions.xPos >= targetX) {
                    positions.xPos = targetX;
                    state = ChefStatesEnum::PREPARING_TO_PUTTING_DOWN;
                }
            }
            else {
                state = ChefStatesEnum::PREPARING_TO_PUTTING_DOWN;
            }
            break;
        }
        case ChefStatesEnum::PREPARING_TO_PUTTING_DOWN:
            state = ChefStatesEnum::PUTTING_DOWN;
            idleTimer = 0.0f;
            break;
        case ChefStatesEnum::PUTTING_DOWN:
            if(idleTimer == 0.0f) {
                int numberOfTable = tablesNumbersToCookFor.front();
                tablesNumbersToCookFor.pop();
                dishesManager->addDish(scaleFactor, numberOfTable);
            }
            idleTimer += deltaTime;
            if(idleTimer > 1.0f) {
                idleTimer = 0.0f;
                state = ChefStatesEnum::TURNING_LEFT;
            }
            break;
        case ChefStatesEnum::TURNING_LEFT:
            animDirection = Directions::LEFT;
            state = ChefStatesEnum::MOVING_LEFT;
            break;
        case ChefStatesEnum::MOVING_LEFT: {
            float moveStep = moveSpeed * deltaTime;
            float startX = destinationPositions.xPos;
            float targetX = positions.xPos - moveDistance;
            if(positions.xPos > startPositions.xPos) {
                float remaining = positions.xPos - startPositions.xPos;
                float step = (moveStep < remaining) ? moveStep : remaining;
                positions.xPos -= step;
                if (positions.xPos <= startPositions.xPos) {
                    positions.xPos = startPositions.xPos;
                    state = defineStateByStartDirection();
                }
            }
            else {
                state = defineStateByStartDirection();
            }
            break;
        }
        case ChefStatesEnum::TURNING_UP:
            animDirection = Directions::UP;
            state = ChefStatesEnum::WAITING_TO_COOKING;
            idleTimer = 0.0f;
            break;
        case ChefStatesEnum::TURNING_DOWN:
            animDirection = Directions::DOWN;
            state = ChefStatesEnum::WAITING_TO_COOKING;
            idleTimer = 0.0f;
            break;
        default:
            break;
    }
}

enum ChefStatesEnum Chef::defineStateByStartDirection() {
    if(startAnimDirection == Directions::UP) {
        return ChefStatesEnum::TURNING_UP;
    }
    else if(startAnimDirection == Directions::DOWN) {
        return ChefStatesEnum::TURNING_DOWN;
    }
    // wyjatek trzeba obsłużyć, ale na razie zakładam, że kucharze zawsze będą zaczynać animację zwróceni w górę lub w dół
    return ChefStatesEnum::TURNING_UP;
}

void Chef::addTableToCookFor(int tableNumber) {
    tablesNumbersToCookFor.push(tableNumber);
}

void Chef::render(sf::RenderWindow* window) {
    std::vector<sf::Sprite>* spriteSet = &chefIdleSprites;

    int framesPerAnim = 6;
    if(state == ChefStatesEnum::MOVING_RIGHT || state == ChefStatesEnum::MOVING_LEFT) {
        spriteSet = &chefRunSprites;
    }
    int spriteIndex = static_cast<int>(animDirection) * framesPerAnim + animFrame;
    if(texturesLoaded && spriteIndex < spriteSet->size()) {
        sf::Sprite sprite = spriteSet->at(spriteIndex);
        sprite.setPosition(positions.xPos, positions.yPos);
        window->draw(sprite);
    }
}