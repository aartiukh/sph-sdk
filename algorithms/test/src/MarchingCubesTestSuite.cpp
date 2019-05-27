/**
 * @file MarchingCubesTestSuite.cpp
 * @author Anton Artyukh (artyukhanton@gmail.com)
 * @date Created May 27, 2019
 * @par Anton Artiukh
 **/

#include "MarchingCubesTestSuite.h"

#include "MarchingCubes.h"
#include "Point.h"
#include "ROperations.h"

#include <gtest/gtest.h>

#include <fstream>
#include <functional>

// function that defines plane boundary
static float pawnEquation(float x, float y, float z)
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
    const std::vector<Point3F> mesh = SPHAlgorithms::MarchingCubes::getFunctionMesh(pawnEquation);

    ASSERT_EQ(37128u, mesh.size());

    generateObjFile(mesh, "pawn.obj");
}

} // namespace TestEnvironment
} // namespace SPHAlgorithms

using namespace SPHAlgorithms::TestEnvironment;

TEST(MarchingCubesTestSuite, generatePawnMesh)
{
    MarchingCubesTestSuite::generatePawnMesh();
}
