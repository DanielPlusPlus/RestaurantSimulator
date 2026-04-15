#pragma once

#include "structures/Positions.hpp"
#include "structures/PathNode.hpp"

#include <vector>


class Level;

class PathFinder {
private:
    Level* level;
public:
    PathFinder(Level* level);
    std::vector<Positions> findPath(Positions start, Positions destination, 
                                    float tileWidth, float tileHeight);
    bool isWalkable(float x, float y, Level* level);
};