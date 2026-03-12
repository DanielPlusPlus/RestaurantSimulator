#pragma once

#include "Scene.hpp"
#include "../characters/Client.hpp"

class Level : public Scene {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture wallsTexture;
    sf::Sprite wallsSprite;
    sf::Texture flowersTexture;
    sf::Sprite flowersSprite;
    bool texturesLoaded = false;
    Client* client;
public:
    Level(int scaleFactor);
    bool loadTextures(int scaleFactor);
    void update(sf::RenderWindow& window, float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};