#pragma once

struct PathNode {
    int x, y;
    PathNode* parent;
    
    PathNode(int x, int y, PathNode* parent = nullptr) : x(x), y(y), parent(parent) {}
};