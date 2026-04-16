#pragma once

#include "ChairPositionsAndDirection.hpp"


struct TwoChairsTablesPositions {
    ChairPositionsAndDirection leftChairPositionsAndDirection;
    ChairPositionsAndDirection rightChairPositionsAndDirection;
    TwoChairsTablesPositions(
        float leftChairXPos, float leftChairYPos,
        float rightChairXPos, float rightChairYPos,
        float leftChairEnterXPos, float leftChairEnterYPos,
        float rightChairEnterXPos, float rightChairEnterYPos
    ) : leftChairPositionsAndDirection{Positions{leftChairXPos, leftChairYPos}, 
                                       Positions{leftChairEnterXPos, leftChairEnterYPos}, 
                                       Directions::LEFT},
        rightChairPositionsAndDirection{Positions{rightChairXPos, rightChairYPos}, 
                                        Positions{rightChairEnterXPos, 
                                        rightChairEnterYPos}, 
                                        Directions::RIGHT} {}
};