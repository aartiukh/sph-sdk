/**
* @file ROperations.h
* @author Anton Artiukh (artyukhanton@gmail.com)
* @date Created May 05, 2019
**/

#include "ROperations.h"

#include <cassert>
#include <cmath>

namespace SPHAlgorithms
{

double ROperations::conjunction(double x, double y)
{
    return x + y - std::sqrt(x * x + y * y);
}

double ROperations::disjunction(double x, double y)
{
    return x + y + std::sqrt(x * x + y * y);
}

} //SPHAlgorithms
