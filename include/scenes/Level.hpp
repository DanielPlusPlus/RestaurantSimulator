#pragma once

#include "Scene.hpp"
#include "characters/Chef.hpp"
#include "items/DishesManager.hpp"


class Level : public Scene {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture wallsTexture;
    sf::Sprite wallsSprite;
    sf::Texture flowersTexture;
    sf::Sprite flowersSprite;
    bool texturesLoaded = false;
    float tileWidth = 16.0f;
    float tileHeight = 16.0f;
    float wallWidth = 6.0f;
    Chef* chef;
    DishesManager* dishesManager;
public:
    Level(int scaleFactor);
    bool loadTextures(int scaleFactor);
    void update(float deltaTime) override;
    void render(sf::RenderWindow* window) override;
};