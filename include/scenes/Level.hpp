#pragma once

#include "Scene.hpp"
#include "items/DishesManager.hpp"
#include "interiors/TablesManager.hpp"
#include "characters/CharactersManager.hpp"


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
    DishesManager* dishesManager;
    TablesManager* tablesManager;
    CharactersManager* charactersManager;
public:
    Level(int scaleFactor);
    bool loadTextures(int scaleFactor);
    void update(float deltaTime) override;
    void render(sf::RenderWindow* window) override;
};