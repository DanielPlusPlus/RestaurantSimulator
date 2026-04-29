#include "utils/PathFinder.hpp"
#include "scenes/Level.hpp"

#include <queue>
#include <set>
#include <algorithm>


PathFinder::PathFinder(Level* level) : level(level) {}

std::vector<Positions> PathFinder::findPath(Positions start, Positions destination, 
                                            float tileWidth, float tileHeight) {
    std::vector<Positions> path;

    float halfTileHeight = tileHeight / 2.0f;
    auto resolveWalkableY = [&](float xPos, float yPos, float& resolvedY) {
        Positions checkPos{xPos, yPos};
        if(level->isValidPositions(checkPos)) {
            resolvedY = yPos;
            return true;
        }
        Positions offsetPos{xPos, yPos - halfTileHeight};
        if(level->isValidPositions(offsetPos)) {
            resolvedY = offsetPos.yPos;
            return true;
        }
        return false;
    };
    
    int startX = static_cast<int>(start.xPos / tileWidth);
    int startY = static_cast<int>(start.yPos / tileHeight);
    int destX = static_cast<int>(destination.xPos / tileWidth);
    int destY = static_cast<int>(destination.yPos / tileHeight);
    
    std::queue<PathNode*> queue;
    std::set<std::pair<int, int>> visited;
    std::vector<PathNode*> allNodes;
    
    PathNode* startNode = new PathNode(startX, startY);
    allNodes.push_back(startNode);
    queue.push(startNode);
    visited.insert({startX, startY});
    
    PathNode* endNode = nullptr;
    
    int directions[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    
    while(!queue.empty() && endNode == nullptr) {
        PathNode* current = queue.front();
        queue.pop();
        
        if(current->x == destX && current->y == destY) {
            endNode = current;
            break;
        }
        
        for(int i = 0; i < 4; i++) {
            int newX = current->x + directions[i][0];
            int newY = current->y + directions[i][1];
            
            if(visited.find({newX, newY}) == visited.end()) {
                float checkPixelX = newX * tileWidth + tileWidth / 2;
                float checkPixelY = newY * tileHeight + tileHeight / 2;
                float resolvedY = checkPixelY;

                if(resolveWalkableY(checkPixelX, checkPixelY, resolvedY)) {
                    visited.insert({newX, newY});
                    PathNode* newNode = new PathNode(newX, newY, current);
                    allNodes.push_back(newNode);
                    queue.push(newNode);
                }
            }
        }
    }

    if(endNode != nullptr) {
        PathNode* current = endNode;
        while(current != nullptr) {
            Positions pos;
            pos.xPos = current->x * tileWidth + tileWidth / 2;
            pos.yPos = current->y * tileHeight + tileHeight / 2;
            if(!level->isValidPositions(pos)) {
                Positions offsetPos{pos.xPos, pos.yPos - halfTileHeight};
                if(level->isValidPositions(offsetPos)) {
                    pos.yPos = offsetPos.yPos;
                }
            }
            path.push_back(pos);
            current = current->parent;
        }
        std::reverse(path.begin(), path.end());

        if(!path.empty()) {
            path.back() = destination;
        }
    }

    for(PathNode* node : allNodes) {
        delete node;
    }
    
    return path;
}

bool PathFinder::isWalkable(float x, float y, Level* level) {
    Positions checkPos{x, y};
    return level->isValidPositions(checkPos);
}