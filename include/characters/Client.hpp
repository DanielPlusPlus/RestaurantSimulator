#pragma once

#include "Character.hpp"

class Client : public Character {
private:
    sf::Texture adamIdleTexture;
    sf::Texture adamRunTexture;
    sf::Texture adamSitTexture;
    std::vector<sf::Sprite> adamIdleSprites;
    std::vector<sf::Sprite> adamRunSprites;
    std::vector<sf::Sprite> adamSitSprites;
    bool texturesLoaded = false;
    int animFrame = 0;
    float animTime = 0.0f;
    int animDirection = 0;
public:
    Client(int scaleFactor);
    bool loadTextures(int scaleFactor);
    void update(sf::RenderWindow& window, float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};