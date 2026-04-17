#pragma once

#include "Positions.hpp"
#include "enums/DirectionsEnum.hpp"


struct ChairPositionsAndDirections {
    Positions chairPositions;
    Positions enterChairPositions;
    enum Directions chairHorizontalDirection;
    enum Directions chairVerticalDirection;
};