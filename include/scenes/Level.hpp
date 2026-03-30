#pragma once

#include "Scene.hpp"
#include "../characters/Chef.hpp"


class Level : public Scene {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture wallsTexture;
    sf::Sprite wallsSprite;
    sf::Texture flowersTexture;
    sf::Sprite flowersSprite;
    bool texturesLoaded = false;
    Chef* chef;
    float tileWidth = 16.0f;
    float tileHeight = 16.0f;
    float wallWidth = 6.0f;
public:
    Level(int scaleFactor);
    bool loadTextures(int scaleFactor);
    void update(sf::RenderWindow& window, float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};