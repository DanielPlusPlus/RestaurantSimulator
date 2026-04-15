#pragma once

#include "Positions.hpp"


struct FourChairsTablesPositions {
    Positions downLeftChairPositions;
    Positions downRightChairPositions;
    Positions upLeftChairPositions;
    Positions upRightChairPositions;
    Positions downLeftChairEnterPositions;
    Positions downRightChairEnterPositions;
    Positions upLeftChairEnterPositions;
    Positions upRightChairEnterPositions;
    FourChairsTablesPositions(
        float downLeftChairXPos, float downLeftChairYPos,
        float downRightChairXPos, float downRightChairYPos,
        float upLeftChairXPos, float upLeftChairYPos,
        float upRightChairXPos, float upRightChairYPos,
        float downLeftChairEnterXPos, float downLeftChairEnterYPos,
        float downRightChairEnterXPos, float downRightChairEnterYPos,
        float upLeftChairEnterXPos, float upLeftChairEnterYPos,
        float upRightChairEnterXPos, float upRightChairEnterYPos
    ) : downLeftChairPositions{downLeftChairXPos, downLeftChairYPos}, 
        downRightChairPositions{downRightChairXPos, downRightChairYPos},
        upLeftChairPositions{upLeftChairXPos, upLeftChairYPos}, 
        upRightChairPositions{upRightChairXPos, upRightChairYPos},
        downLeftChairEnterPositions{downLeftChairEnterXPos, downLeftChairEnterYPos},
        downRightChairEnterPositions{downRightChairEnterXPos, downRightChairEnterYPos},
        upLeftChairEnterPositions{upLeftChairEnterXPos, upLeftChairEnterYPos},
        upRightChairEnterPositions{upRightChairEnterXPos, upRightChairEnterYPos} {}
};