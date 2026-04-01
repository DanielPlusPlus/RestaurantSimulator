#pragma once

#include <SFML/Graphics.hpp>


class Scene {
protected:
    int scaleFactor;
public:
    Scene(int scaleFactor) : scaleFactor(scaleFactor) {}
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow* window) = 0;
};