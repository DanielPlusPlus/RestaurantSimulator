#pragma once

#include "Positions.hpp"


struct FourChairsTablesPositions {
    Positions downLeftChair;
    Positions downRightChair;
    Positions upLeftChair;
    Positions upRightChair;
    FourChairsTablesPositions(
        float downLeftChairXPos, float downLeftChairYPos,
        float downRightChairXPos, float downRightChairYPos,
        float upLeftChairXPos, float upLeftChairYPos,
        float upRightChairXPos, float upRightChairYPos
    ) : downLeftChair{downLeftChairXPos, downLeftChairYPos}, 
        downRightChair{downRightChairXPos, downRightChairYPos},
        upLeftChair{upLeftChairXPos, upLeftChairYPos}, 
        upRightChair{upRightChairXPos, upRightChairYPos} {}
};