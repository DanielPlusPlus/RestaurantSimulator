#include "characters/Customer.hpp"

Customer::Customer(int scaleFactor, float tileWidth, float tileHeight, float wallWidth, CharactersTexturesPaths texturesPaths) : Character(Positions{0.0f, 0.0f}) {
    texturesLoaded = loadTextures(scaleFactor, texturesPaths);
    width = width * scaleFactor;
    height = height * scaleFactor;

    positions.xPos = wallWidth + tileWidth * 2.0f;
    positions.yPos = tileHeight * 1.5f;
    startX = positions.xPos;
    startY = positions.yPos;
    moveDistance = 5.0f * tileWidth;
    moveSpeed = tileWidth;
    moveProgress = 0.0f;
    animDirection = Directions::UP;
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
    changeState(deltaTime, scaleFactor);
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

void Customer::changeState(float deltaTime, int scaleFactor) {
   
}

void Customer::render(sf::RenderWindow* window) {
    if (!customerIdleSprites.empty()) {
        window->draw(customerIdleSprites[animFrame % customerIdleSprites.size()]);
    }
}
