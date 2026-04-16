#pragma once

#include "ChairPositionsAndDirection.hpp"


struct FourChairsTablesPositions {
    ChairPositionsAndDirection downLeftChairPositionsAndDirection;
    ChairPositionsAndDirection downRightChairPositionsAndDirection;
    ChairPositionsAndDirection upLeftChairPositionsAndDirection;
    ChairPositionsAndDirection upRightChairPositionsAndDirection;
    FourChairsTablesPositions(
        float downLeftChairXPos, float downLeftChairYPos,
        float downRightChairXPos, float downRightChairYPos,
        float upLeftChairXPos, float upLeftChairYPos,
        float upRightChairXPos, float upRightChairYPos,
        float downLeftChairEnterXPos, float downLeftChairEnterYPos,
        float downRightChairEnterXPos, float downRightChairEnterYPos,
        float upLeftChairEnterXPos, float upLeftChairEnterYPos,
        float upRightChairEnterXPos, float upRightChairEnterYPos
    ) : downLeftChairPositionsAndDirection{Positions{downLeftChairXPos, downLeftChairYPos}, 
                                           Positions{downLeftChairEnterXPos, downLeftChairEnterYPos}, 
                                           Directions::LEFT},
        downRightChairPositionsAndDirection{Positions{downRightChairXPos, downRightChairYPos}, 
                                            Positions{downRightChairEnterXPos, 
                                            downRightChairEnterYPos}, 
                                            Directions::RIGHT},
        upLeftChairPositionsAndDirection{Positions{upLeftChairXPos, upLeftChairYPos}, 
                                         Positions{upLeftChairEnterXPos, upLeftChairEnterYPos}, 
                                         Directions::LEFT},
        upRightChairPositionsAndDirection{Positions{upRightChairXPos, upRightChairYPos}, 
                                          Positions{upRightChairEnterXPos, upRightChairEnterYPos}, 
                                          Directions::RIGHT} {}
};