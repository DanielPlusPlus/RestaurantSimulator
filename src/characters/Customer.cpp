#include "characters/Customer.hpp"


Customer::Customer(int scaleFactor, CharactersTexturesPaths texturesPaths, float tileWidth, float tileHeight, 
         float moveXSpeed, float moveYSpeed, int customerNumber, Positions startPositions, 
         Positions rightDoorPositions) : Character(startPositions), 
         customerNumber(customerNumber), queueStartingPositions(rightDoorPositions) {
    texturesLoaded = loadTextures(scaleFactor, texturesPaths);
    width *= scaleFactor;
    height *= scaleFactor;
    this->startPositions.xPos *= scaleFactor;
    this->startPositions.yPos *= scaleFactor;
    this->positions.xPos *= scaleFactor;
    this->positions.yPos *= scaleFactor;
    this->queueStartingPositions.xPos *= scaleFactor;
    this->queueStartingPositions.yPos *= scaleFactor;
    this->queueStartingPositions.yPos -= tileHeight;

    state = CustomerStatesEnum::PREPARING_TO_MOVING;
    moveSpeed = tileWidth;
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

void Customer::update(float deltaTime, int scaleFactor) {
    changeAnimation(deltaTime);
    changeState(deltaTime);
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

void Customer::changeState(float deltaTime) {
   switch(state) {
        case CustomerStatesEnum::PREPARING_TO_MOVING:
            animDirection = Directions::LEFT;
            state = CustomerStatesEnum::MOVING_LEFT;
        break;
        case CustomerStatesEnum::MOVING_LEFT: {
            float moveStep = moveSpeed * deltaTime;
            float startX = queueStartingPositions.xPos;
            float targetX = positions.xPos - moveDistance;
            if(positions.xPos > queueStartingPositions.xPos) {
                float remaining = positions.xPos - queueStartingPositions.xPos;
                float step = (moveStep < remaining) ? moveStep : remaining;
                positions.xPos -= step;
                if (positions.xPos <= queueStartingPositions.xPos) {
                    positions.xPos = queueStartingPositions.xPos;
                    state = CustomerStatesEnum::TURNING_UP;
                }
            }
            else {
                state = CustomerStatesEnum::TURNING_UP;
            }
            break;
            }
        case CustomerStatesEnum::TURNING_UP:
            animDirection = Directions::UP;
            // state = CustomerStatesEnum::MOVING_UP;
            break;
    }
}

void Customer::render(sf::RenderWindow* window) {
    std::vector<sf::Sprite>* spriteSet = &customerIdleSprites;

    int framesPerAnim = 6;
    if(state == CustomerStatesEnum::MOVING_LEFT) {
        spriteSet = &customerRunSprites;
    }
    int spriteIndex = static_cast<int>(animDirection) * framesPerAnim + animFrame;
    if(texturesLoaded && spriteIndex < spriteSet->size()) {
        sf::Sprite sprite = spriteSet->at(spriteIndex);
        sprite.setPosition(positions.xPos, positions.yPos);
        window->draw(sprite);
    }
}
