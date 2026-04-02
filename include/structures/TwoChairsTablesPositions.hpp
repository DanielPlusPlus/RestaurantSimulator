#pragma once

#include "ChairPosition.hpp"


struct TwoChairsTablesPositions {
    ChairPosition chair1;
    ChairPosition chair2;
    TwoChairsTablesPositions(
        float chair1XPos, float chair1YPos,
        float chair2XPos, float chair2YPos
    ) : chair1{chair1XPos, chair1YPos}, chair2{chair2XPos, chair2YPos} {}
};