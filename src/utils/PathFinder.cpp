#include "utils/PathFinder.hpp"
#include "scenes/Level.hpp"

#include <queue>
#include <set>
#include <algorithm>


PathFinder::PathFinder(Level* level) : level(level) {}

std::vector<Positions> PathFinder::findPath(Positions start, Positions destination, 
                                            float tileWidth, float tileHeight) {
    std::vector<Positions> path;
    
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
                
                if(isWalkable(checkPixelX, checkPixelY, level)) {
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