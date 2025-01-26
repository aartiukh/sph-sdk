/**
 * @file NeighboursSearchTestSuite.cpp
 * @author Anton Artiukh
 * @date Created Feb 13, 2017
 **/

#include "NeighboursSearchTestSuite.h"

#include "Area.h"
#include "NSBruteForce.h"
#include "NSBruteForceImproved.h"
#include "NeighboursSearch.h"

#include <stdexcept>

#include <gtest/gtest.h>

namespace SPHSDK
{
namespace TestEnvironment
{

void NeighboursSearchTestSuite::testSearch3D(
    const Cuboid&               cuboid,
    FLOAT                       radius,
    FLOAT                       accuracy,
    TestPoints3D&               points,
    const SizetVector&          expectedBoxSizes,
    const VectorOfSizetVectors& expectedBoxNeighbours,
    VectorOfSizetVectors        expectedPointNeighbours)
{
    ASSERT_EQ(points.size(), expectedPointNeighbours.size());

    for (size_t i = 0u; i < expectedPointNeighbours.size(); ++i)
    {
        std::sort(expectedPointNeighbours[i].begin(), expectedPointNeighbours[i].end());
    }

    const Volume volume(cuboid);

    {
        NeighboursSearch3D<TestPoints3D> ns(volume, radius, accuracy);

        ASSERT_EQ(ns.m_boxes.size(), expectedBoxNeighbours.size());

        ns.search(points);

        const size_t boxesSize = ns.m_boxes.size();
        ASSERT_EQ(expectedBoxSizes.size(), boxesSize);

        for (size_t i = 0u; i < boxesSize; ++i)
        {
            EXPECT_EQ(expectedBoxSizes[i], ns.m_boxes[i].size());
        }

        for (size_t i = 0u; i < boxesSize; ++i)
        {
            EXPECT_EQ(expectedBoxNeighbours[i], ns.m_nearbyBoxes[i]);
        }

        for (size_t i = 0u; i < points.size(); ++i)
        {
            std::sort(points[i].neighbours.begin(), points[i].neighbours.end());
            EXPECT_EQ(expectedPointNeighbours[i], points[i].neighbours);
        }
    }

    for (size_t i = 0u; i < points.size(); ++i)
    {
        points[i].neighbours.clear();
    }

    {
        NSBruteForce<TestPoints3D> ns(volume, radius, accuracy);

        ns.search(points);

        for (size_t i = 0u; i < points.size(); ++i)
        {
            std::sort(points[i].neighbours.begin(), points[i].neighbours.end());
            EXPECT_EQ(expectedPointNeighbours[i], points[i].neighbours);
        }
    }

    for (size_t i = 0u; i < points.size(); ++i)
    {
        points[i].neighbours.clear();
    }

    {
        NSBruteForceImproved<TestPoints3D> ns(volume, radius, accuracy);

        ns.search(points);

        for (size_t i = 0u; i < points.size(); ++i)
        {
            std::sort(points[i].neighbours.begin(), points[i].neighbours.end());
            EXPECT_EQ(expectedPointNeighbours[i], points[i].neighbours);
        }
    }
}

void NeighboursSearchTestSuite::testInsert3D(
    const Cuboid&               cuboid,
    FLOAT                       radius,
    FLOAT                       accuracy,
    TestPoints3D&               points,
    const SizetVector&          expectedBoxSizes,
    const VectorOfSizetVectors& expectedPointsInBoxes)
{
    const Volume                     volume(cuboid);
    NeighboursSearch3D<TestPoints3D> ns(volume, radius, accuracy);

    ns.insertPointsIntoBoxes(points);
    const VectorOfSizetVectors& actualPointsInBoxes = ns.m_boxes;

    const size_t boxesSize = ns.m_boxes.size();
    ASSERT_EQ(expectedBoxSizes.size(), boxesSize);

    for (size_t i = 0u; i < boxesSize; ++i)
        EXPECT_EQ(expectedBoxSizes[i], ns.m_boxes[i].size());

    size_t sum = 0u;

    for (size_t i = 0u; i < actualPointsInBoxes.size(); ++i)
        sum += actualPointsInBoxes[i].size();

    ASSERT_EQ(ns.m_pointsSize, sum);
    EXPECT_EQ(expectedPointsInBoxes, actualPointsInBoxes);
}

void NeighboursSearchTestSuite::searchInOneBox3D()
{
    const auto  cuboid = Cuboid(Point3F(0., 0., 0.), 1.0, 1.0, 1.0);
    const FLOAT radius = 0.5;
    const FLOAT accuracy = 0.001;

    TestPoints3D points = {Point3F(0.5, 0.5, 0.5), Point3F(0.6, 0.6, 0.6), Point3F(0.7, 0.7, 0.7)};

    const SizetVector    expectedBoxSizes = {0, 0, 0, 0, 0, 0, 0, 3};
    VectorOfSizetVectors expectedBoxNeighbours = {
        {1, 4, 5, 3, 6, 7, 2},
        {0, 5, 4, 2, 7, 6, 3},
        {3, 6, 7, 1, 4, 5, 0},
        {2, 7, 6, 0, 5, 4, 1},
        {5, 0, 1, 7, 2, 3, 6},
        {4, 1, 0, 6, 3, 2, 7},
        {7, 2, 3, 5, 0, 1, 4},
        {6, 3, 2, 4, 1, 0, 5}};

    VectorOfSizetVectors expectedNeighbours = {{1, 2}, {0, 2}, {0, 1}};

    testSearch3D(cuboid, radius, accuracy, points, expectedBoxSizes, expectedBoxNeighbours, expectedNeighbours);
}

void NeighboursSearchTestSuite::searchInDifferentBoxesCenterBack3D()
{
    const auto  cuboid = Cuboid(Point3F(0., 0., 0.), 1.5, 1.5, 1.5);
    const FLOAT radius = 0.5;
    const FLOAT accuracy = 0.001;

    TestPoints3D points = {
        Point3F(0.75, 0.25, 0.75),
        Point3F(0.45, 0.25, 0.75),
        Point3F(0.75, 0.25, 0.45),
        Point3F(1.05, 0.25, 0.75),
        Point3F(0.75, 0.25, 1.05),
        Point3F(0.75, 0.75, 0.75)};

    const SizetVector expectedBoxSizes = {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1,
                                          0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0};

    VectorOfSizetVectors expectedBoxNeighbours = {
        {1, 9, 10, 4, 12, 13, 3},
        {2, 0, 10, 11, 9, 5, 3, 13, 14, 12, 4},
        {1, 11, 10, 4, 14, 13, 5},
        {4, 12, 13, 7, 15, 16, 6, 1, 9, 10, 0},
        {5, 3, 13, 14, 12, 8, 6, 16, 17, 15, 7, 2, 0, 10, 11, 9, 1},
        {4, 14, 13, 7, 17, 16, 8, 1, 11, 10, 2},
        {7, 15, 16, 4, 12, 13, 3},
        {8, 6, 16, 17, 15, 5, 3, 13, 14, 12, 4},
        {7, 17, 16, 4, 14, 13, 5},
        {10, 18, 0, 19, 1, 13, 21, 3, 22, 4, 12},
        {11, 9, 19, 1, 20, 18, 2, 0, 14, 12, 22, 4, 23, 21, 5, 3, 13},
        {10, 20, 2, 19, 1, 13, 23, 5, 22, 4, 14},
        {13, 21, 3, 22, 4, 16, 24, 6, 25, 7, 15, 10, 18, 0, 19, 1, 9},
        {14, 12, 22, 4, 23, 21, 5, 3, 17, 15, 25, 7, 26, 24, 8, 6, 16, 11, 9, 19, 1, 20, 18, 2, 0, 10},
        {13, 23, 5, 22, 4, 16, 26, 8, 25, 7, 17, 10, 20, 2, 19, 1, 11},
        {16, 24, 6, 25, 7, 13, 21, 3, 22, 4, 12},
        {17, 15, 25, 7, 26, 24, 8, 6, 14, 12, 22, 4, 23, 21, 5, 3, 13},
        {16, 26, 8, 25, 7, 13, 23, 5, 22, 4, 14},
        {19, 9, 10, 22, 12, 13, 21},
        {20, 18, 10, 11, 9, 23, 21, 13, 14, 12, 22},
        {19, 11, 10, 22, 14, 13, 23},
        {22, 12, 13, 25, 15, 16, 24, 19, 9, 10, 18},
        {23, 21, 13, 14, 12, 26, 24, 16, 17, 15, 25, 20, 18, 10, 11, 9, 19},
        {22, 14, 13, 25, 17, 16, 26, 19, 11, 10, 20},
        {25, 15, 16, 22, 12, 13, 21},
        {26, 24, 16, 17, 15, 23, 21, 13, 14, 12, 22},
        {25, 17, 16, 22, 14, 13, 23}};

    VectorOfSizetVectors expectedNeighbours = {{3, 1, 4, 2, 5}, {0, 4, 2}, {0, 3, 1}, {0, 4, 2}, {0, 3, 1}, {0}};

    testSearch3D(cuboid, radius, accuracy, points, expectedBoxSizes, expectedBoxNeighbours, expectedNeighbours);
}

void NeighboursSearchTestSuite::searchInDifferentBoxesCenterMiddle3D()
{
    const auto  cuboid = Cuboid(Point3F(0., 0., 0.), 0.4, 0.5, 0.3001);
    const FLOAT radius = 0.1;
    const FLOAT accuracy = 0.001;

    TestPoints3D points = {
        Point3F(0.15, 0.35, 0.15),
        Point3F(0.2, 0.35, 0.15),
        Point3F(0.09, 0.35, 0.15),
        Point3F(0.15, 0.35, 0.2),
        Point3F(0.15, 0.35, 0.09),
        Point3F(0.2, 0.29, 0.2),
        Point3F(0.09, 0.29, 0.09),
        Point3F(0.09, 0.41, 0.2),
        Point3F(0.2, 0.41, 0.09)};

    const SizetVector expectedBoxSizes = {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0,
                                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0,
                                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0};

    VectorOfSizetVectors expectedBoxNeighbours = {
        {1, 20, 21, 5, 24, 25, 4},
        {2, 0, 21, 22, 20, 6, 4, 25, 26, 24, 5},
        {3, 1, 22, 23, 21, 7, 5, 26, 27, 25, 6},
        {2, 23, 22, 6, 27, 26, 7},
        {5, 24, 25, 9, 28, 29, 8, 1, 20, 21, 0},
        {6, 4, 25, 26, 24, 10, 8, 29, 30, 28, 9, 2, 0, 21, 22, 20, 1},
        {7, 5, 26, 27, 25, 11, 9, 30, 31, 29, 10, 3, 1, 22, 23, 21, 2},
        {6, 27, 26, 10, 31, 30, 11, 2, 23, 22, 3},
        {9, 28, 29, 13, 32, 33, 12, 5, 24, 25, 4},
        {10, 8, 29, 30, 28, 14, 12, 33, 34, 32, 13, 6, 4, 25, 26, 24, 5},
        {11, 9, 30, 31, 29, 15, 13, 34, 35, 33, 14, 7, 5, 26, 27, 25, 6},
        {10, 31, 30, 14, 35, 34, 15, 6, 27, 26, 7},
        {13, 32, 33, 17, 36, 37, 16, 9, 28, 29, 8},
        {14, 12, 33, 34, 32, 18, 16, 37, 38, 36, 17, 10, 8, 29, 30, 28, 9},
        {15, 13, 34, 35, 33, 19, 17, 38, 39, 37, 18, 11, 9, 30, 31, 29, 10},
        {14, 35, 34, 18, 39, 38, 19, 10, 31, 30, 11},
        {17, 36, 37, 13, 32, 33, 12},
        {18, 16, 37, 38, 36, 14, 12, 33, 34, 32, 13},
        {19, 17, 38, 39, 37, 15, 13, 34, 35, 33, 14},
        {18, 39, 38, 14, 35, 34, 15},
        {21, 40, 0, 41, 1, 25, 44, 4, 45, 5, 24},
        {22, 20, 41, 1, 42, 40, 2, 0, 26, 24, 45, 5, 46, 44, 6, 4, 25},
        {23, 21, 42, 2, 43, 41, 3, 1, 27, 25, 46, 6, 47, 45, 7, 5, 26},
        {22, 43, 3, 42, 2, 26, 47, 7, 46, 6, 27},
        {25, 44, 4, 45, 5, 29, 48, 8, 49, 9, 28, 21, 40, 0, 41, 1, 20},
        {26, 24, 45, 5, 46, 44, 6, 4, 30, 28, 49, 9, 50, 48, 10, 8, 29, 22, 20, 41, 1, 42, 40, 2, 0, 21},
        {27, 25, 46, 6, 47, 45, 7, 5, 31, 29, 50, 10, 51, 49, 11, 9, 30, 23, 21, 42, 2, 43, 41, 3, 1, 22},
        {26, 47, 7, 46, 6, 30, 51, 11, 50, 10, 31, 22, 43, 3, 42, 2, 23},
        {29, 48, 8, 49, 9, 33, 52, 12, 53, 13, 32, 25, 44, 4, 45, 5, 24},
        {30, 28, 49, 9, 50, 48, 10, 8, 34, 32, 53, 13, 54, 52, 14, 12, 33, 26, 24, 45, 5, 46, 44, 6, 4, 25},
        {31, 29, 50, 10, 51, 49, 11, 9, 35, 33, 54, 14, 55, 53, 15, 13, 34, 27, 25, 46, 6, 47, 45, 7, 5, 26},
        {30, 51, 11, 50, 10, 34, 55, 15, 54, 14, 35, 26, 47, 7, 46, 6, 27},
        {33, 52, 12, 53, 13, 37, 56, 16, 57, 17, 36, 29, 48, 8, 49, 9, 28},
        {34, 32, 53, 13, 54, 52, 14, 12, 38, 36, 57, 17, 58, 56, 18, 16, 37, 30, 28, 49, 9, 50, 48, 10, 8, 29},
        {35, 33, 54, 14, 55, 53, 15, 13, 39, 37, 58, 18, 59, 57, 19, 17, 38, 31, 29, 50, 10, 51, 49, 11, 9, 30},
        {34, 55, 15, 54, 14, 38, 59, 19, 58, 18, 39, 30, 51, 11, 50, 10, 31},
        {37, 56, 16, 57, 17, 33, 52, 12, 53, 13, 32},
        {38, 36, 57, 17, 58, 56, 18, 16, 34, 32, 53, 13, 54, 52, 14, 12, 33},
        {39, 37, 58, 18, 59, 57, 19, 17, 35, 33, 54, 14, 55, 53, 15, 13, 34},
        {38, 59, 19, 58, 18, 34, 55, 15, 54, 14, 35},
        {41, 20, 21, 45, 24, 25, 44},
        {42, 40, 21, 22, 20, 46, 44, 25, 26, 24, 45},
        {43, 41, 22, 23, 21, 47, 45, 26, 27, 25, 46},
        {42, 23, 22, 46, 27, 26, 47},
        {45, 24, 25, 49, 28, 29, 48, 41, 20, 21, 40},
        {46, 44, 25, 26, 24, 50, 48, 29, 30, 28, 49, 42, 40, 21, 22, 20, 41},
        {47, 45, 26, 27, 25, 51, 49, 30, 31, 29, 50, 43, 41, 22, 23, 21, 42},
        {46, 27, 26, 50, 31, 30, 51, 42, 23, 22, 43},
        {49, 28, 29, 53, 32, 33, 52, 45, 24, 25, 44},
        {50, 48, 29, 30, 28, 54, 52, 33, 34, 32, 53, 46, 44, 25, 26, 24, 45},
        {51, 49, 30, 31, 29, 55, 53, 34, 35, 33, 54, 47, 45, 26, 27, 25, 46},
        {50, 31, 30, 54, 35, 34, 55, 46, 27, 26, 47},
        {53, 32, 33, 57, 36, 37, 56, 49, 28, 29, 48},
        {54, 52, 33, 34, 32, 58, 56, 37, 38, 36, 57, 50, 48, 29, 30, 28, 49},
        {55, 53, 34, 35, 33, 59, 57, 38, 39, 37, 58, 51, 49, 30, 31, 29, 50},
        {54, 35, 34, 58, 39, 38, 59, 50, 31, 30, 51},
        {57, 36, 37, 53, 32, 33, 52},
        {58, 56, 37, 38, 36, 54, 52, 33, 34, 32, 53},
        {59, 57, 38, 39, 37, 55, 53, 34, 35, 33, 54},
        {58, 39, 38, 54, 35, 34, 55}};

    VectorOfSizetVectors expectedNeighbours = {
        {1, 2, 3, 4, 7, 8, 5},
        {0, 3, 4, 8, 5},
        {0, 3, 4, 7, 6},
        {0, 1, 2, 7, 5},
        {0, 1, 2, 8, 6},
        {3, 1, 0},
        {4, 2},
        {3, 2, 0},
        {4, 1, 0}};

    testSearch3D(cuboid, radius, accuracy, points, expectedBoxSizes, expectedBoxNeighbours, expectedNeighbours);
}

} // namespace TestEnvironment
} // namespace SPHSDK

using namespace SPHSDK::TestEnvironment;

TEST(NeighboursSearchTestSuite, searchInOneBox3D)
{
    NeighboursSearchTestSuite::searchInOneBox3D();
}

TEST(NeighboursSearchTestSuite, searchInDifferentBoxesCenterBack3D)
{
    NeighboursSearchTestSuite::searchInDifferentBoxesCenterBack3D();
}

TEST(NeighboursSearchTestSuite, searchInDifferentBoxesCenterMiddle3D)
{
    NeighboursSearchTestSuite::searchInDifferentBoxesCenterMiddle3D();
}
