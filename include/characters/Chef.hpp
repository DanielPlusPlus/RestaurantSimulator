#pragma once

#include "Character.hpp"

class Chef : public Character {
private:
    sf::Texture adamIdleTexture;
    sf::Texture adamRunTexture;
    sf::Texture adamSitTexture;
    std::vector<sf::Sprite> adamIdleSprites;
    std::vector<sf::Sprite> adamRunSprites;
    std::vector<sf::Sprite> adamSitSprites;
    float xPos = 0.0f;
    float yPos = 0.0f;
    float width = 16.0f;
    float height = 32.0f;
    bool texturesLoaded = false;
    int animFrame = 0;
    float animTime = 0.0f;
    int animDirection = 0;
public:
    Chef(int scaleFactor);
    bool loadTextures(int scaleFactor);
    void update(sf::RenderWindow& window, float deltaTime, float tileWidth, 
                float tileHeight, float wallWidth) override;
    void render(sf::RenderWindow& window) override;
};