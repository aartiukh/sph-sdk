/**
 * @file MarchingCubes.h
 * @author Ihor Lytvyn (litvinigor98@gmail.com)
 * @date Created May 26, 2019
 **/

#ifndef MARCHING_CUBES_H_43C34465A6ED4DB9B9F2F4C3937BF5DC
#define MARCHING_CUBES_H_43C34465A6ED4DB9B9F2F4C3937BF5DC

#include "Point.h"

#include <functional>

namespace SPHSDK
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
    static Point3FVector generateMesh(std::function<FLOAT(FLOAT, FLOAT, FLOAT)> f);

private:
    static Point3FVector MarchingCube(std::function<FLOAT(FLOAT, FLOAT, FLOAT)> f, FLOAT fX, FLOAT fY, FLOAT fZ);

    static void
    fillFoundTriangles(Point3FVector& resultEdgeVertex, const Point3FVector& EdgeVertex, const int iFlagIndex);

    static Point3FVector findPointIntersection(
        const int iEdgeFlags, const FLOAT CubeValue[], const FLOAT fX, const FLOAT fY, const FLOAT fZ);

    static int determineFlag(const FLOAT CubeValue[]);
};

} // namespace SPHSDK

#endif // MARCHING_CUBES_H_43C34465A6ED4DB9B9F2F4C3937BF5DC
