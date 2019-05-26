/**
* @file ROperations.cpp
* @author Anton Artiukh (artyukhanton@gmail.com)
* @date Created May 05, 2019
**/

#include "ROperations.h"

#include <cassert>
#include <cmath>

namespace SPHAlgorithms
{

float ROperations::conjunction(float x, float y)
{
    return x + y - std::sqrt(x * x + y * y);
}

float ROperations::disjunction(float x, float y)
{
    return x + y + std::sqrt(x * x + y * y);
}

} //SPHAlgorithms
