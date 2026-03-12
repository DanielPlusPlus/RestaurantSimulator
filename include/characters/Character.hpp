#pragma once

#include <SFML/Graphics.hpp>

class Character {
protected:
    int scaleFactor;
    float timeElapsed;
public:
    Character(int scaleFactor) : scaleFactor(scaleFactor), timeElapsed(0.0f) {}
    virtual void update(sf::RenderWindow& window, float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};