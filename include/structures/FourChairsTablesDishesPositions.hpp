#pragma once

#include "Positions.hpp"


struct FourChairsTablesDishesPositions {
    Positions downLeftDish;
    Positions downRightDish;
    Positions upLeftDish;
    Positions upRightDish;
    FourChairsTablesDishesPositions(
        float downLeftDishXPos, float downLeftDishYPos,
        float downRightDishXPos, float downRightDishYPos,
        float upLeftDishXPos, float upLeftDishYPos,
        float upRightDishXPos, float upRightDishYPos
    ) : downLeftDish{downLeftDishXPos, downLeftDishYPos}, 
        downRightDish{downRightDishXPos, downRightDishYPos},
        upLeftDish{upLeftDishXPos, upLeftDishYPos}, 
        upRightDish{upRightDishXPos, upRightDishYPos} {}
};