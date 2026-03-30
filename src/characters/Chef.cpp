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

    if(!chefIdleTexture.loadFromFile("assets/characters/chef/chef_idle.png"))
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

    if(!chefRunTexture.loadFromFile("assets/characters/chef/chef_run.png"))
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

    if(!chefSitTexture.loadFromFile("assets/characters/chef/chef_sit.png"))
        return false;
    int sitFrameCount = chefSitTexture.getSize().x / frameWidth;
    chefSitSprites.clear();
    for(int i = 0; i < sitFrameCount; i++) {
        sf::Sprite sprite;
        sprite.setTexture(chefSitTexture);
        sprite.setTextureRect(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
        sprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));
        chefSitSprites.push_back(sprite);
    }

    return true;
}

void Chef::update(sf::RenderWindow& window, float deltaTime, float tileWidth, float tileHeight, float wallWidth) {
    if(!initialized) {
        xPos = wallWidth + tileWidth * 2;
        yPos = tileHeight * 1.5f;
        startX = xPos;
        startY = yPos;
        state = State::TURNING_RIGHT;
        moveDistance = 5.0f * tileWidth;
        moveSpeed = tileWidth;
        moveProgress = 0.0f;
        animDirection = Directions::UP;
        initialized = true;
    }

    animTime += deltaTime;
    if(animTime > 0.2f) {
        animTime = 0.0f;
        animFrame++;
        if(animFrame >= 6) {
            animFrame = 0;
        }
    }

    switch(state) {
        case State::TURNING_RIGHT:
            animDirection = Directions::RIGHT;
            state = State::MOVING_RIGHT;
            moveProgress = 0.0f;
            break;
        case State::MOVING_RIGHT:
            if(moveProgress < moveDistance) {
                float moveStep = moveSpeed * deltaTime;
                float remaining = moveDistance - moveProgress;
                float step = (moveStep < remaining) ? moveStep : remaining;
                xPos += step;
                moveProgress += step;
            }
            else {
                state = State::TURNING_LEFT;
            }
            break;
        case State::TURNING_LEFT:
            animDirection = Directions::LEFT;
            state = State::MOVING_LEFT;
            moveProgress = 0.0f;
            break;
        case State::MOVING_LEFT:
            if(moveProgress < moveDistance) {
                float moveStep = moveSpeed * deltaTime;
                float remaining = moveDistance - moveProgress;
                float step = (moveStep < remaining) ? moveStep : remaining;
                xPos -= step;
                moveProgress += step;
            }
            else {
                state = State::TURNING_UP;
            }
            break;
        case State::TURNING_UP:
            animDirection = Directions::UP;
            state = State::IDLE;
            idleTimer = 0.0f;
            break;
        case State::IDLE:
            idleTimer += deltaTime;
            if(idleTimer > 5.0f) {
                idleTimer = 0.0f;
                state = State::TURNING_RIGHT;
            }
            break;
        default:
            break;
    }
}

void Chef::render(sf::RenderWindow& window) {
    sf::Event event;
    std::vector<sf::Sprite>* spriteSet = &chefIdleSprites;

    int framesPerAnim = 6;
    if(state == State::MOVING_RIGHT || state == State::MOVING_LEFT) {
        spriteSet = &chefRunSprites;
    }
    int spriteIndex = static_cast<int>(animDirection) * framesPerAnim + animFrame;
    if(texturesLoaded && spriteIndex < spriteSet->size()) {
        sf::Sprite sprite = spriteSet->at(spriteIndex);
        sprite.setPosition(xPos, yPos);
        window.draw(sprite);
        std::cout << "Drawing sprite index: " << spriteIndex << " of " << spriteSet->size() << std::endl;
    }
}