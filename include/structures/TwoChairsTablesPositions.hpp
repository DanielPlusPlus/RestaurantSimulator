#pragma once

#include "Positions.hpp"


struct TwoChairsTablesPositions {
    Positions leftChair;
    Positions rightChair;
    TwoChairsTablesPositions(
        float leftChairXPos, float leftChairYPos,
        float rightChairXPos, float rightChairYPos
    ) : leftChair{leftChairXPos, leftChairYPos}, 
        rightChair{rightChairXPos, rightChairYPos} {}
};