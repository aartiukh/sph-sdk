/**
 * @file MarchingCubes.cpp
 * @author Ihor Lytvyn (litvinigor98@gmail.com)
 * @date Created May 26, 2019
 **/

#include "MarchingCubes.h"
#include "MarchingCubesConfig.h"

namespace SPHSDK
{

Point3FVector MarchingCubes::generateMesh(std::function<FLOAT(FLOAT, FLOAT, FLOAT)> f)
{
    Point3FVector mesh;

    for (auto x = X_MIN; x < X_MAX; x += GRID_CUBE_SIZE)
    {
        for (auto y = Y_MIN; y < Y_MAX; y += GRID_CUBE_SIZE)
        {
            for (auto z = Z_MIN; z < Z_MAX; z += GRID_CUBE_SIZE)
            {
                // iX, iY, iZ are coordinates of the current vertex in grid_cube
                const auto vertices = MarchingCube(f, x, y, z);
                std::copy(vertices.begin(), vertices.end(), std::back_inserter(mesh));
            }
        }
    }
    return mesh;
}

static FLOAT adapt(FLOAT a, FLOAT b)
{
    const auto delta = b - a;

    if (std::abs(delta) < MC_PRECISION)
    {
        return static_cast<FLOAT>(0.5);
    }

    return -a / delta;
}

Point3FVector MarchingCubes::MarchingCube(std::function<FLOAT(FLOAT, FLOAT, FLOAT)> f, FLOAT fX, FLOAT fY, FLOAT fZ)
{
    // vector with all triangles found
    Point3FVector trianglesMesh;

    FLOAT CubeValue[CUBE_VERTICES_NUMBER];

    // Evaluate value of the cube vertex at each point
    for (int iVertex = 0; iVertex < CUBE_VERTICES_NUMBER; iVertex++)
    {
        CubeValue[iVertex] =
            f(fX + VertexOffset[iVertex][0], fY + VertexOffset[iVertex][1], fZ + VertexOffset[iVertex][2]);
    }

    // Find which vertices are inside of the surface and which are outside
    int iFlagIndex = determineFlag(CubeValue);

    // Find which edges are intersected by the surface
    int iEdgeFlags = CubeEdgeFlags[iFlagIndex];

    // If the cube is entirely inside or outside of the surface, then there will be no intersections
    if (iEdgeFlags == 0)
    {
        return trianglesMesh;
    }

    // Fill the triangles that were found.  There can be up to five per cube
    fillFoundTriangles(trianglesMesh, findPointIntersection(iEdgeFlags, CubeValue, fX, fY, fZ), iFlagIndex);

    return trianglesMesh;
}

void MarchingCubes::fillFoundTriangles(Point3FVector&       resultEdgeVertex,
                                       const Point3FVector& EdgeVertex,
                                       const int           iFlagIndex)
{
    for (int iTriangle = 0; iTriangle < TRIANGLES_MAX_NUMBER_FOR_ONE_CUBE; iTriangle++)
    {
        if (TriangleConnectionTable[iFlagIndex][TRIANGLES_CORNERS_NUMBER * iTriangle] < 0)
        {
            break;
        }

        for (int iCorner = 0; iCorner < TRIANGLES_CORNERS_NUMBER; iCorner++)
        {
            const int iVertex = TriangleConnectionTable[iFlagIndex][TRIANGLES_CORNERS_NUMBER * iTriangle + iCorner];
            resultEdgeVertex.push_back(Point3(EdgeVertex[iVertex].x, EdgeVertex[iVertex].y, EdgeVertex[iVertex].z));
        }
    }
}

// Find points of intersection on each edge
Point3FVector MarchingCubes::findPointIntersection(
    const int iEdgeFlags, const FLOAT CubeValue[], const FLOAT fX, const FLOAT fY, const FLOAT fZ)
{
    Point3FVector EdgeVertex(12);

    for (int iEdge = 0; iEdge < CUBE_EDGES_NUMBER; iEdge++)
    {
        // if there is an intersection on this edge
        if (iEdgeFlags & (1 << iEdge))
        {
            // Find the two vertices specified by this edge, and interpolate them according to adapt
            const auto v0 = EdgeConnection[iEdge][0];
            const auto v1 = EdgeConnection[iEdge][1];

            const auto f0 = CubeValue[v0];
            const auto f1 = CubeValue[v1];

            const auto t0 = 1 - adapt(f0, f1);
            const auto t1 = 1 - t0;

            EdgeVertex[iEdge].x = fX + VertexOffset[v0][0] * t0 + VertexOffset[v1][0] * t1;
            EdgeVertex[iEdge].y = fY + VertexOffset[v0][1] * t0 + VertexOffset[v1][1] * t1;
            EdgeVertex[iEdge].z = fZ + VertexOffset[v0][2] * t0 + VertexOffset[v1][2] * t1;
        }
    }
    return EdgeVertex;
}
int MarchingCubes::determineFlag(const FLOAT CubeValue[])
{
    int flagIndex = 0;

    for (int iVertexTest = 0; iVertexTest < CUBE_VERTICES_NUMBER; iVertexTest++)
    {
        if (CubeValue[iVertexTest] > 0)
        {
            flagIndex |= 1 << iVertexTest;
        }
    }
    return flagIndex;
}
} // namespace SPHSDK
