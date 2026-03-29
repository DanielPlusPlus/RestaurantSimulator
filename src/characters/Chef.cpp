#include "characters/Chef.hpp"
#include <iostream>

Chef::Chef(int scaleFactor) : Character(scaleFactor) {
    texturesLoaded = loadTextures(scaleFactor);
    width = width * scaleFactor;
    height = height * scaleFactor;
}

bool Chef::loadTextures(int scaleFactor) {
    int frameWidth = 16;
    int frameHeight = 32;

    if(!adamIdleTexture.loadFromFile("assets/characters/chef/chef_idle.png"))
        return false;
    int idleFrameCount = adamIdleTexture.getSize().x / frameWidth;
    adamIdleSprites.clear();
    for(int i = 0; i < idleFrameCount; i++) {
        sf::Sprite sprite;
        sprite.setTexture(adamIdleTexture);
        sprite.setTextureRect(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
        sprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));
        adamIdleSprites.push_back(sprite);
    }

    if(!adamRunTexture.loadFromFile("assets/characters/chef/chef_run.png"))
        return false;
    int runFrameCount = adamRunTexture.getSize().x / frameWidth;
    adamRunSprites.clear();
    for(int i = 0; i < runFrameCount; i++) {
        sf::Sprite sprite;
        sprite.setTexture(adamRunTexture);
        sprite.setTextureRect(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
        sprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));
        adamRunSprites.push_back(sprite);
    }

    if(!adamSitTexture.loadFromFile("assets/characters/chef/chef_sit.png"))
        return false;
    int sitFrameCount = adamSitTexture.getSize().x / frameWidth;
    adamSitSprites.clear();
    for(int i = 0; i < sitFrameCount; i++) {
        sf::Sprite sprite;
        sprite.setTexture(adamSitTexture);
        sprite.setTextureRect(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
        sprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));
        adamSitSprites.push_back(sprite);
    }

    return true;
}

void Chef::update(sf::RenderWindow& window, float deltaTime, float tileWidth, float tileHeight, float wallWidth) {
    animTime += deltaTime;
    if(animTime > 0.2f) {
        animTime = 0.0f;
        animDirection = rand() % 4;
        animFrame = rand() % 6;
    }
    xPos = wallWidth + tileWidth * 2;
    yPos = tileHeight * 1.5f;
}

void Chef::render(sf::RenderWindow& window) {
    sf::Event event;
    int spriteIndex = animDirection * 6 + animFrame;
    if(texturesLoaded && spriteIndex < adamIdleSprites.size()) {
        sf::Sprite sprite = adamIdleSprites.at(spriteIndex);
        sprite.setPosition(xPos, yPos);
        window.draw(sprite);
        std::cout << "Drawing sprite index: " << spriteIndex << " of " << adamIdleSprites.size() << std::endl;
    }
}