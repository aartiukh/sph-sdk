/**
 * @file MarchingCubes.cpp
 * @author Ihor Lytvyn (litvinigor98@gmail.com)
 * @date Created May 26, 2019
 **/

#include "MarchingCubes.h"
#include "MarchingCubesConfig.h"
#include "Point.h"

#include <fstream>
#include <vector>

namespace SPHAlgorithms
{

void MarchingCubes::generateObj(std::function<float(float, float, float)> f)
{
    std::vector<Point3D> resultMesh;

    for (float iX = X_MIN; iX < X_MAX; iX += GRID_CUBE_SIZE)
    {
        for (float iY = Y_MIN; iY < Y_MAX; iY += GRID_CUBE_SIZE)
        {
            for (float iZ = Z_MIN; iZ < Z_MAX; iZ += GRID_CUBE_SIZE)
            {
                // iX, iY, iZ are coordinates of the current vertex in grid_cube
                auto vertices = MarchCube(f, iX, iY, iZ);
                std::copy(vertices.begin(), vertices.end(), std::back_inserter(resultMesh));
            }
        }
    }

    generateObjFile(resultMesh, "output.obj");
}

std::vector<Point3D> MarchingCubes::getFunctionMesh(std::function<float(float, float, float)> f)
{
	std::vector<Point3D> resultMesh;

	for (float iX = X_MIN; iX < X_MAX; iX += GRID_CUBE_SIZE)
	{
		for (float iY = Y_MIN; iY < Y_MAX; iY += GRID_CUBE_SIZE)
		{
			for (float iZ = Z_MIN; iZ < Z_MAX; iZ += GRID_CUBE_SIZE)
			{
				// iX, iY, iZ are coordinates of the current vertex in grid_cube
				auto vertices = MarchCube(f, iX, iY, iZ);
				std::copy(vertices.begin(), vertices.end(), std::back_inserter(resultMesh));
			}
		}
	}
	return resultMesh;
}

float adapt(float fValue1, float fValue2)
{
    const float fDelta = fValue2 - fValue1;

    if (std::abs(fDelta) < 0.0001f)
    {
        return 0.5f;
    }

    return -fValue1 / fDelta;
}

std::vector<Point3D>
MarchingCubes::MarchCube(std::function<float(float, float, float)> f, float fX, float fY, float fZ)
{
	// vector with all triangles found
    std::vector<Point3D> resultTrianglesMesh;

    float CubeValue[8];

    // Evaluate value of the cube vertex at each point
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
        return resultTrianglesMesh;
    }

	// Points of intersection of the surface with each edge 
    std::vector<Point3D> EdgeVertex(12);

	// Find points of intersection on each edge
	findPointIntersection(EdgeVertex, iEdgeFlags, CubeValue, fX, fY, fZ);

    // Fill the triangles that were found.  There can be up to five per cube
	fillFoundTriangles(resultTrianglesMesh, EdgeVertex, iFlagIndex);

    return resultTrianglesMesh;
}

// Generates Obj file in Wavefront format with mesh
void MarchingCubes::generateObjFile(const std::vector<Point3D>& vertices, const std::string& fileName)
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

void MarchingCubes::fillFoundTriangles(std::vector<Point3D> resultEdgeVertex, const std::vector<Point3D> EdgeVertex, const int iFlagIndex)
{
	for (int iTriangle = 0; iTriangle < 5; iTriangle++)
	{
		if (TriangleConnectionTable[iFlagIndex][3 * iTriangle] < 0)
		{
			break;
		}

		for (int iCorner = 0; iCorner < 3; iCorner++)
		{
			const int iVertex = TriangleConnectionTable[iFlagIndex][3 * iTriangle + iCorner];
			resultEdgeVertex.push_back(Point3D(EdgeVertex[iVertex].x, EdgeVertex[iVertex].y, EdgeVertex[iVertex].z));
		}
	}
}
void MarchingCubes::findPointIntersection(std::vector<Point3D> EdgeVertex, const int iEdgeFlags, const float CubeValue[], const float fX, const float fY, const float fZ)
{
	for (int iEdge = 0; iEdge < 12; iEdge++)
	{
		// if there is an intersection on this edge
		if (iEdgeFlags & (1 << iEdge))
		{
			// Find the two vertices specified by this edge, and interpolate them according to adapt
			const int v0 = EdgeConnection[iEdge][0];
			const int v1 = EdgeConnection[iEdge][1];

			const float f0 = CubeValue[v0];
			const float f1 = CubeValue[v1];

			const float t0 = 1.f - adapt(f0, f1);
			const float t1 = 1.f - t0;

			EdgeVertex[iEdge].x = fX + VertexOffset[v0][0] * t0 + VertexOffset[v1][0] * t1;
			EdgeVertex[iEdge].y = fY + VertexOffset[v0][1] * t0 + VertexOffset[v1][1] * t1;
			EdgeVertex[iEdge].z = fZ + VertexOffset[v0][2] * t0 + VertexOffset[v1][2] * t1;
		}
	}
}
} // namespace SPHAlgorithms
