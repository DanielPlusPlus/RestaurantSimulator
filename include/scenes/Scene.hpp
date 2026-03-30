#pragma once

#include <SFML/Graphics.hpp>


class Scene {
protected:
    int scaleFactor;
    float timeElapsed;
public:
    Scene(int scaleFactor) : scaleFactor(scaleFactor), timeElapsed(0.0f) {}
    virtual void update(sf::RenderWindow& window, float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};