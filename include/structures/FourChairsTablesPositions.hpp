#pragma once

#include "ChairPosition.hpp"


struct FourChairsTablesPositions {
    ChairPosition chair1;
    ChairPosition chair2;
    ChairPosition chair3;
    ChairPosition chair4;
    FourChairsTablesPositions(
        float chair1XPos, float chair1YPos,
        float chair2XPos, float chair2YPos,
        float chair3XPos, float chair3YPos,
        float chair4XPos, float chair4YPos
    ) : chair1{chair1XPos, chair1YPos}, chair2{chair2XPos, chair2YPos},
        chair3{chair3XPos, chair3YPos}, chair4{chair4XPos, chair4YPos} {}
};