#include "characters/Waiter.hpp"
#include "scenes/Level.hpp"


Waiter::Waiter(int scaleFactor, float tileWidth, float tileHeight, float moveXSpeed, 
           float moveYSpeed, int waiterNumber, Positions startPositions, 
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

    state = WaiterStatesEnum::WAITING_TO_START;
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

void Waiter::update(float deltaTime, int scaleFactor, Level* level) {
    changeAnimation(deltaTime);
    changeState(deltaTime, scaleFactor, level);
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

void Waiter::changeState(float deltaTime, int scaleFactor, Level* level) {
    level->isValidPosition(positions);
}

void Waiter::render(sf::RenderWindow* window) {
    std::vector<sf::Sprite>* spriteSet = &waiterIdleSprites;

    int framesPerAnim = 6;
    int spriteIndex = static_cast<int>(animDirection) * framesPerAnim + animFrame;
    if(texturesLoaded && spriteIndex < spriteSet->size()) {
        sf::Sprite sprite = spriteSet->at(spriteIndex);
        sprite.setPosition(positions.xPos, positions.yPos);
        window->draw(sprite);
    }
}
