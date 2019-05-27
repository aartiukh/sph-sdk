/**
 * @file Main.cpp
 * @author Ihor Lytvyn (litvinigor98@gmail.com)
 * @date Created May 26, 2019
 **/

#include "MarchingCubes.h"
#include "ROperations.h"

#include <functional>

// function that defines plane boundary
float omega(float x, float y, float z)
{
    using namespace SPHAlgorithms;

    const auto dis = ROperations::disjunction<float>;
    const auto con = ROperations::conjunction<float>;

    const float x_sqr = (x - 1.5f) * (x - 1.5f);
    const float y_sqr = (y - 1.5f) * (y - 1.5f);
    const float z1_sqr = (z - 0.75f) * (z - 0.75f);
    const float z2_sqr = (1.f - z) * (1.f - z);
    const float z3_sqr = (1.25f - z) * (1.25f - z);

    return dis(con(con(0.25f - x_sqr - y_sqr, -20.f * (x_sqr + y_sqr) + 1.f + 10.f * z1_sqr), z * (1.f - z)),
               dis(0.125f - x_sqr - y_sqr - 20.f * z2_sqr, 0.05f - x_sqr - y_sqr - z3_sqr));
}

int main()
{
    SPHAlgorithms::MarchingCubes::generateObj(omega);

    return 0;
}
