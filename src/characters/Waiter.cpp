#include "characters/Waiter.hpp"

Waiter::Waiter(int scaleFactor, float tileWidth, float tileHeight, float wallWidth) {
    texturesLoaded = loadTextures(scaleFactor);
    width = width * scaleFactor;
    height = height * scaleFactor;

    xPos = wallWidth + tileWidth * 2.0f;
    yPos = tileHeight * 1.5f;
    startX = xPos;
    startY = yPos;
    moveDistance = 5.0f * tileWidth;
    moveSpeed = tileWidth;
    moveProgress = 0.0f;
    animDirection = Directions::UP;
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

void Waiter::update(float deltaTime, int scaleFactor) {
    changeAnimation(deltaTime);
    changeState(deltaTime, scaleFactor);
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

void Waiter::changeState(float deltaTime, int scaleFactor) {
    
}

void Waiter::render(sf::RenderWindow* window) {
    if (!waiterIdleSprites.empty()) {
        window->draw(waiterIdleSprites[animFrame % waiterIdleSprites.size()]);
    }
}
