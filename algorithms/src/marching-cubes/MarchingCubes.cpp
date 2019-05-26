/**
 * @file MarchingCubes.cpp
 * @author Ihor Lytvyn (litvinigor98@gmail.com)
 * @date Created May 26, 2019
 **/

#include "MarchingCubes.h"
#include "MarchingCubesConfig.h"

#include <fstream>
#include <vector>

namespace SPHAlgorithms
{

struct MarchingCubes::V3
{
    float x, y, z; // x, y, z Cartesian coordinates

    V3()
        : x(0.f)
        , y(0.f)
        , z(0.f)
    {
    }

    V3(float _x, float _y, float _z)
        : x(_x)
        , y(_y)
        , z(_z)
    {
    }
};

void MarchingCubes::generateObj(std::function<float(float, float, float)> f)
{
    std::vector<V3> globalResultVector;

    for (float iX = X_MIN; iX < X_MAX; iX += GRID_CUBE_SIZE)
    {
        for (float iY = Y_MIN; iY < Y_MAX; iY += GRID_CUBE_SIZE)
        {
            for (float iZ = Z_MIN; iZ < Z_MAX; iZ += GRID_CUBE_SIZE)
            {
                // iX, iY, iZ are coordinates of the current vertex in grid_cube
                auto vertices = MarchCube(f, iX, iY, iZ);
                std::copy(vertices.begin(), vertices.end(), std::back_inserter(globalResultVector));
            }
        }
    }

    generateObjFile(globalResultVector, "output.obj");
}
std::vector<MarchingCubes::V3>
MarchingCubes::MarchCube(std::function<float(float, float, float)> f, float fX, float fY, float fZ)
{
    std::vector<V3> resultEdgeVertex;

    float CubeValue[8];

    // Make a local copy of the values at the cube's corners
    for (int iVertex = 0; iVertex < 8; iVertex++)
    {
        CubeValue[iVertex] =
            f(fX + VertexOffset[iVertex][0], fY + VertexOffset[iVertex][1], fZ + VertexOffset[iVertex][2]);
    }

    // Find which vertices are inside of the surface and which are outside
    int iFlagIndex = 0;
    for (int iVertexTest = 0; iVertexTest < 8; iVertexTest++)
    {
        if (CubeValue[iVertexTest] > 0)
        {
            iFlagIndex |= 1 << iVertexTest;
        }
    }

    // Find which edges are intersected by the surface
    int iEdgeFlags = CubeEdgeFlags[iFlagIndex];

    // If the cube is entirely inside or outside of the surface, then there will be no intersections
    if (iEdgeFlags == 0)
    {
        return resultEdgeVertex;
    }

    // Find the point of intersection of the surface with each edge
    // Then find the normal to the surface at those points
    std::vector<V3> EdgeVertex(12);

    for (int iEdge = 0; iEdge < 12; iEdge++)
    {
        // if there is an intersection on this edge
        if (iEdgeFlags & (1 << iEdge))
        {
            EdgeVertex[iEdge].x = fX + (VertexOffset[EdgeConnection[iEdge][0]][0] + GRID_CUBE_SIZE);
            EdgeVertex[iEdge].y = fY + (VertexOffset[EdgeConnection[iEdge][0]][1] + GRID_CUBE_SIZE);
            EdgeVertex[iEdge].z = fZ + (VertexOffset[EdgeConnection[iEdge][0]][2] + GRID_CUBE_SIZE);
        }
    }

    // Draw the triangles that were found.  There can be up to five per cube
    for (int iTriangle = 0; iTriangle < 5; iTriangle++)
    {
        if (TriangleConnectionTable[iFlagIndex][3 * iTriangle] < 0)
        {
            break;
        }

        for (int iCorner = 0; iCorner < 3; iCorner++)
        {
            const int iVertex = TriangleConnectionTable[iFlagIndex][3 * iTriangle + iCorner];
            resultEdgeVertex.push_back(V3(EdgeVertex[iVertex].x, EdgeVertex[iVertex].y, EdgeVertex[iVertex].z));
        }
    }
    return resultEdgeVertex;
}
void MarchingCubes::generateObjFile(const std::vector<V3>& vertices, const std::string& fileName)
{
    std::ofstream file(fileName);
    if (!file)
    {
        return;
    }

    // write vertices
    for (auto const& v : vertices)
    {
        file << "v " << v.x << ' ' << v.y << ' ' << v.z << '\n';
    }

    const size_t size = vertices.size();

    for (size_t i = 1u; i <= size; i += CUBE_DIMENSION)
    {
        file << "f " << i << ' ' << i + 1 << ' ' << i + 2 << '\n';
    }

    file.close();
}
} // namespace SPHAlgorithms
