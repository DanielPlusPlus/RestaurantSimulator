#pragma once

#include "structures/Positions.hpp"
#include "structures/CharactersTexturesPaths.hpp"
#include "enums/DirectionsEnum.hpp"

#include <SFML/Graphics.hpp>


class Character {
protected:
    Positions startPositions;
    Positions positions;
public:
    Character(Positions positions) : startPositions(positions), positions(positions) {}
    virtual ~Character() = default;
    float getXPos() {
        return positions.xPos; 
    };
    float getYPos() {
        return positions.yPos; 
    };
    virtual float getSortY() {
        return positions.yPos;
    }
    virtual void render(sf::RenderWindow* window) = 0;
};