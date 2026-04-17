#pragma once

#include "ChairPositionsAndDirections.hpp"


struct TwoChairsTablesPositions {
    ChairPositionsAndDirections leftChairPositionsAndDirections;
    ChairPositionsAndDirections rightChairPositionsAndDirections;
    TwoChairsTablesPositions(
        float leftChairXPos, float leftChairYPos,
        float rightChairXPos, float rightChairYPos,
        float leftChairEnterXPos, float leftChairEnterYPos,
        float rightChairEnterXPos, float rightChairEnterYPos
    ) : leftChairPositionsAndDirections{Positions{leftChairXPos, leftChairYPos}, 
                                       Positions{leftChairEnterXPos, leftChairEnterYPos}, 
                                       Directions::LEFT, Directions::DOWN},
        rightChairPositionsAndDirections{Positions{rightChairXPos, rightChairYPos}, 
                                        Positions{rightChairEnterXPos, 
                                        rightChairEnterYPos}, 
                                        Directions::RIGHT, Directions::DOWN} {}
};