#pragma once

#include "ChairPositionsAndDirections.hpp"


struct FourChairsTablesPositions {
    ChairPositionsAndDirections downLeftChairPositionsAndDirections;
    ChairPositionsAndDirections downRightChairPositionsAndDirections;
    ChairPositionsAndDirections upLeftChairPositionsAndDirections;
    ChairPositionsAndDirections upRightChairPositionsAndDirections;
    FourChairsTablesPositions(
        float downLeftChairXPos, float downLeftChairYPos,
        float downRightChairXPos, float downRightChairYPos,
        float upLeftChairXPos, float upLeftChairYPos,
        float upRightChairXPos, float upRightChairYPos,
        float downLeftChairEnterXPos, float downLeftChairEnterYPos,
        float downRightChairEnterXPos, float downRightChairEnterYPos,
        float upLeftChairEnterXPos, float upLeftChairEnterYPos,
        float upRightChairEnterXPos, float upRightChairEnterYPos
    ) : downLeftChairPositionsAndDirections{Positions{downLeftChairXPos, downLeftChairYPos}, 
                                           Positions{downLeftChairEnterXPos, downLeftChairEnterYPos}, 
                                           Directions::LEFT, Directions::DOWN},
        downRightChairPositionsAndDirections{Positions{downRightChairXPos, downRightChairYPos}, 
                                            Positions{downRightChairEnterXPos, 
                                            downRightChairEnterYPos}, 
                                            Directions::RIGHT, Directions::DOWN},
        upLeftChairPositionsAndDirections{Positions{upLeftChairXPos, upLeftChairYPos}, 
                                         Positions{upLeftChairEnterXPos, upLeftChairEnterYPos}, 
                                         Directions::LEFT, Directions::UP},
        upRightChairPositionsAndDirections{Positions{upRightChairXPos, upRightChairYPos}, 
                                          Positions{upRightChairEnterXPos, upRightChairEnterYPos}, 
                                          Directions::RIGHT, Directions::UP} {}
};