/**
 * @file MarchingCubesTestSuite.cpp
 * @author Anton Artyukh (artyukhanton@gmail.com)
 * @date Created May 27, 2019
 * @par Anton Artiukh
 **/

#include "MarchingCubesTestSuite.h"

#include "MarchingCubes.h"
#include "Shapes.h"

#include <gtest/gtest.h>

#include <fstream>


// Generates Obj file in Wavefront format with mesh
static void generateObjFile(const std::vector<SPHAlgorithms::Point3F>& vertices, const std::string& fileName)
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

    for (size_t i = 1u; i <= size; i += 3)
    {
        file << "f " << i << ' ' << i + 1 << ' ' << i + 2 << '\n';
    }

    file.close();
}

namespace SPHAlgorithms
{
namespace TestEnvironment
{

void MarchingCubesTestSuite::generatePawnMesh()
{
    const Point3FVector mesh = SPHAlgorithms::MarchingCubes::generateMesh(Shapes::Pawn);

    ASSERT_EQ(37128u, mesh.size());

    generateObjFile(mesh, "pawn.obj");
}

void MarchingCubesTestSuite::generateBishopMesh()
{
    const Point3FVector mesh = SPHAlgorithms::MarchingCubes::generateMesh(Shapes::Bishop);

    ASSERT_EQ(45552u, mesh.size());

    generateObjFile(mesh, "bishop.obj");
}

} // namespace TestEnvironment
} // namespace SPHAlgorithms

using namespace SPHAlgorithms::TestEnvironment;

TEST(MarchingCubesTestSuite, generatePawnMesh)
{
    MarchingCubesTestSuite::generatePawnMesh();
}

TEST(MarchingCubesTestSuite, generateBishopMesh)
{
    MarchingCubesTestSuite::generateBishopMesh();
}
