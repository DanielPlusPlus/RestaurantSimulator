#pragma once

#include "enums/ScenesEnum.hpp"

#include <SFML/Graphics.hpp>


class Scene {
protected:
    int scaleFactor;
    bool isSceneToChange = false;
    virtual bool loadTextures(int scaleFactor) = 0;
public:
    Scene(int scaleFactor) : scaleFactor(scaleFactor) {}
    virtual ~Scene() {}
    virtual void update(float deltaTime, sf::RenderWindow* window) = 0;
    virtual bool changeScene(enum ScenesEnum* sceneName) = 0;
    virtual void render(sf::RenderWindow* window) = 0;
};