/**
 * @file MarchingCubes.h
 * @author Ihor Lytvyn (litvinigor98@gmail.com)
 * @date Created May 26, 2019
 **/

#ifndef MARCHING_CUBES_H_43C34465A6ED4DB9B9F2F4C3937BF5DC
#define MARCHING_CUBES_H_43C34465A6ED4DB9B9F2F4C3937BF5DC

#include "Point.h"

#include <functional>

namespace SPHAlgorithms
{

/**
 * @brief MarchingCubes class implements Marching Cubes algorithm.
 */
class MarchingCubes
{

public:
    /**
     * @brief Generates triangles mesh from function
     * @param f    The function that represents the domain equation
     */
    static Point3FVector generateMesh(std::function<float(float, float, float)> f);

private:
    static Point3FVector MarchingCube(std::function<float(float, float, float)> f, float fX, float fY, float fZ);

    static void
    fillFoundTriangles(Point3FVector& resultEdgeVertex, const Point3FVector& EdgeVertex, const int iFlagIndex);

    static Point3FVector findPointIntersection(
        const int iEdgeFlags, const float CubeValue[], const float fX, const float fY, const float fZ);

    static int determineFlag(const float CubeValue[]);
};

} // namespace SPHAlgorithms

#endif // MARCHING_CUBES_H_43C34465A6ED4DB9B9F2F4C3937BF5DC
