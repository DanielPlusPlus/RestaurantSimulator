#pragma once

#include "Positions.hpp"


struct TwoChairsTablesPositions {
    Positions leftChairPositions;
    Positions rightChairPositions;
    Positions leftChairEnterPositions;
    Positions rightChairEnterPositions;
    TwoChairsTablesPositions(
        float leftChairXPos, float leftChairYPos,
        float rightChairXPos, float rightChairYPos,
        float leftChairEnterXPos, float leftChairEnterYPos,
        float rightChairEnterXPos, float rightChairEnterYPos
    ) : leftChairPositions{leftChairXPos, leftChairYPos}, 
        rightChairPositions{rightChairXPos, rightChairYPos},
        leftChairEnterPositions{leftChairEnterXPos, leftChairEnterYPos},
        rightChairEnterPositions{rightChairEnterXPos, rightChairEnterYPos} {}
};