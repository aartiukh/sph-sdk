/**
 * @file ROperations.hpp
 * @author Anton Artiukh (artyukhanton@gmail.com)
 * @date Created May 05, 2019
 **/

#include <cassert>
#include <cmath>

namespace SPHAlgorithms
{

template <class T> T ROperations::conjunction(T x, T y)
{
    return x + y - std::sqrt(x * x + y * y);
}

template <class T> T ROperations::disjunction(T x, T y)
{
    return x + y + std::sqrt(x * x + y * y);
}

} // namespace SPHAlgorithms
