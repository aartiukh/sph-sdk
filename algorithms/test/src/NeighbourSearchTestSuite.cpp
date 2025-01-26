#include "NeighbourSearchTestSuite.h"

#include "Area.h"
#include "NSBruteForce.h"
#include "NSBruteForceImproved.h"
#include "NSGridBasedOld.h"

#include <gtest/gtest.h>

#include <memory>
#include <vector>

namespace SPHSDK
{
namespace TestEnvironment
{

void NeighbourSearchTestSuite::testSearch(
    const Cuboid&        cuboid,
    FLOAT                radius,
    FLOAT                accuracy,
    TestPoints3D&        points,
    VectorOfSizetVectors expectedNeighbours)
{
    ASSERT_EQ(points.size(), expectedNeighbours.size());

    for (size_t i = 0u; i < expectedNeighbours.size(); ++i)
    {
        std::sort(expectedNeighbours[i].begin(), expectedNeighbours[i].end());
    }

    const Volume volume(cuboid);

    std::vector<std::unique_ptr<NeighbourSearchI<TestPoints3D>>> algorithms;

    algorithms.push_back(std::make_unique<NSBruteForce<TestPoints3D>>(volume, radius, accuracy));
    algorithms.push_back(std::make_unique<NSBruteForceImproved<TestPoints3D>>(volume, radius, accuracy));
    algorithms.push_back(std::make_unique<NSGridBasedOld<TestPoints3D>>(volume, radius, accuracy));

    for (const auto& ns : algorithms)
    {
        ns->search(points);

        for (size_t i = 0u; i < points.size(); ++i)
        {
            std::sort(points[i].neighbours.begin(), points[i].neighbours.end());
            EXPECT_EQ(expectedNeighbours[i], points[i].neighbours);
        }

        for (size_t i = 0u; i < points.size(); ++i)
        {
            points[i].neighbours.clear();
        }
    }
}

void NeighbourSearchTestSuite::searchAllPointsAreNeighbours()
{
    const auto  cuboid = Cuboid(Point3F(0., 0., 0.), 1.0, 1.0, 1.0);
    const FLOAT radius = 0.5;
    const FLOAT accuracy = 0.001;

    TestPoints3D points = {Point3F(0.5, 0.5, 0.5), Point3F(0.6, 0.6, 0.6), Point3F(0.7, 0.7, 0.7)};

    VectorOfSizetVectors expectedNeighbours = {{1, 2}, {0, 2}, {0, 1}};

    testSearch(cuboid, radius, accuracy, points, expectedNeighbours);
}

} // namespace TestEnvironment
} // namespace SPHSDK

using namespace SPHSDK::TestEnvironment;

TEST(NeighbourSearchTestSuite, searchAllPointsAreNeighbours)
{
    NeighbourSearchTestSuite::searchAllPointsAreNeighbours();
}
