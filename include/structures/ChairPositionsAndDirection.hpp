#pragma once

#include "Positions.hpp"
#include "enums/DirectionsEnum.hpp"


struct ChairPositionsAndDirection {
    Positions chairPositions;
    Positions enterChairPositions;
    enum Directions chairDirection;
};