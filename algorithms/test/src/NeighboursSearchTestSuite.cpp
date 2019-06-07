/**
 * @file NeighboursSearchTestSuite.cpp
 * @NeighboursSearchTestSuite class defines neighbours search test suite
 * @author Anton Artyukh (artyukhanton@gmail.com)
 * @version 0.1
 * @date Created Feb 13, 2017
 * @par Anton Artiukh
 **/

#include "NeighboursSearchTestSuite.h"

#include "Area.h"
#include "NeighboursSearch.h"
#include <stdexcept>

#include <gtest/gtest.h>

namespace SPHAlgorithms
{
namespace TestEnvironment
{

void NeighboursSearchTestSuite::testSearch(const Rect&                 areaRect,
                                           double                      radius,
                                           double                      accuracy,
                                           TestPoints&                 points,
                                           const SizetVector&          expectedBoxSizes,
                                           const VectorOfSizetVectors& expectedNeighbours)
{
    ASSERT_EQ(points.size(), expectedNeighbours.size());

    const Area                   area(areaRect);
    NeighboursSearch<TestPoints> ns(area, radius, accuracy);

    ns.search(points);

    const size_t boxesSize = ns.m_boxes.size();
    ASSERT_EQ(expectedBoxSizes.size(), boxesSize);

    for (size_t i = 0u; i < boxesSize; ++i)
    {
        EXPECT_EQ(expectedBoxSizes[i], ns.m_boxes[i].size());
    }

    for (size_t i = 0u; i < points.size(); ++i)
    {
        EXPECT_EQ(expectedNeighbours[i], points[i].neighbours);
    }
}

void NeighboursSearchTestSuite::testInsert(const Rect&                 areaRect,
                                           double                      radius,
                                           double                      accuracy,
                                           TestPoints&                 points,
                                           const SizetVector&          expectedBoxSizes,
                                           const VectorOfSizetVectors& expectedPointsInBoxes)
{
    const Area                   area(areaRect);
    NeighboursSearch<TestPoints> ns(area, radius, accuracy);

    ns.insertPointsIntoBoxes(points);
    const VectorOfSizetVectors& actualPointsInBoxes = ns.m_boxes;

    const size_t boxesSize = ns.m_boxes.size();
    ASSERT_EQ(expectedBoxSizes.size(), boxesSize);

    for (size_t i = 0u; i < boxesSize; ++i)
    {
        EXPECT_EQ(expectedBoxSizes[i], ns.m_boxes[i].size());
    }

    size_t sum = 0u;

    for (size_t i = 0u; i < actualPointsInBoxes.size(); ++i)
    {
        sum += actualPointsInBoxes[i].size();
    }

    ASSERT_EQ(ns.m_pointsSize, sum);
    EXPECT_EQ(expectedPointsInBoxes, actualPointsInBoxes);
}

//----------------------------------

void NeighboursSearchTestSuite::testSearch3D(const Cuboid&             cuboid,
                                           double                      radius,
                                           double                      accuracy,
                                           TestPoints3D&               points,
                                           const SizetVector&          expectedBoxSizes,
                                           const VectorOfSizetVectors& expectedBoxNeighbours,
                                           const VectorOfSizetVectors& expectedPointNeighbours)
{
    ASSERT_EQ(points.size(), expectedPointNeighbours.size());

    const Volume volume(cuboid);

    NeighboursSearch3D<TestPoints3D> ns(volume, radius, accuracy);

    ASSERT_EQ(ns.m_boxes.size(), expectedBoxNeighbours.size());

    ns.search(points);

    const size_t boxesSize = ns.m_boxes.size();
    ASSERT_EQ(expectedBoxSizes.size(), boxesSize);

    for (size_t i = 0u; i < boxesSize; ++i)
        EXPECT_EQ(expectedBoxSizes[i], ns.m_boxes[i].size());

    for (size_t i = 0u; i < boxesSize; ++i)
        EXPECT_EQ(expectedBoxNeighbours[i], ns.m_nearbyBoxes[i]);

    for (size_t i = 0u; i < points.size(); ++i)
        EXPECT_EQ(expectedPointNeighbours[i], points[i].neighbours);
}

void NeighboursSearchTestSuite::testInsert3D(const Cuboid&               cuboid,
                                             double                      radius,
                                             double                      accuracy,
                                             TestPoints3D&               points,
                                             const SizetVector&          expectedBoxSizes,
                                             const VectorOfSizetVectors& expectedPointsInBoxes)
{
    const Volume volume(cuboid);
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

/// NeighboursSearch::search() tests

void NeighboursSearchTestSuite::searchInOneBox()
{
    TestPoints points = {Point2D(0.5, 0.5), Point2D(0.6, 0.6), Point2D(0.7, 0.7)};

    testSearch(Rect(Point2D(0., 0.), Point2D(1.0, 1.0)), // areaRect
               0.5,                                      // radius
               0.001,                                    // accuracy
               points,                                   // points
               {0, 0, 0, 3},                             // expectedBoxSizes
               {{1, 2}, {0, 2}, {0, 1}});                // expectedNeighbours
}

void NeighboursSearchTestSuite::searchInDifferentBoxesRightBottom()
{
    TestPoints points = {Point2D(3.5, 0.5), Point2D(2.5, 0.5), Point2D(2.5, 1.5), Point2D(3.5, 1.5)};

    testSearch(Rect(Point2D(0., 0.), Point2D(4.0, 4.0)),         // areaRect
               1.0,                                              // radius
               0.001,                                            // accuracy
               points,                                           // points
               {0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // expectedBoxSizes
               {{3, 1}, {2, 0}, {1, 3}, {0, 2}});                // expectedNeighbours
}

void NeighboursSearchTestSuite::searchInDifferentBoxesLeftBottom()
{
    TestPoints points = {Point2D(0.5, 0.5), Point2D(1.5, 0.5), Point2D(0.5, 1.5), Point2D(1.5, 1.5)};

    testSearch(Rect(Point2D(0., 0.), Point2D(4.0, 4.0)),         // areaRect
               1.0,                                              // radius
               0.001,                                            // accuracy
               points,                                           // points
               {1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // expectedBoxSizes
               {{2, 1}, {3, 0}, {0, 3}, {1, 2}});                // expectedNeighbours
}

void NeighboursSearchTestSuite::searchInDifferentBoxesRightTop()
{
    TestPoints points = {Point2D(3.5, 3.5), Point2D(2.5, 3.5), Point2D(2.5, 2.5), Point2D(3.5, 2.5)};

    testSearch(Rect(Point2D(0., 0.), Point2D(4.0, 4.0)),         // areaRect
               1.0,                                              // radius
               0.001,                                            // accuracy
               points,                                           // points
               {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1}, // expectedBoxSizes
               {{3, 1}, {2, 0}, {1, 3}, {0, 2}});                // expectedNeighbours
}

void NeighboursSearchTestSuite::searchInDifferentBoxesLeftTop()
{
    TestPoints points = {Point2D(0.5, 3.5), Point2D(1.5, 3.5), Point2D(0.5, 2.5), Point2D(1.5, 2.5)};

    testSearch(Rect(Point2D(0., 0.), Point2D(4.0, 4.0)),         // areaRect
               1.0,                                              // radius
               0.001,                                            // accuracy
               points,                                           // points
               {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0}, // expectedBoxSizes
               {{2, 1}, {3, 0}, {0, 3}, {1, 2}});                // expectedNeighbours
}

void NeighboursSearchTestSuite::searchInDifferentBoxesRightSide()
{
    TestPoints points = {Point2D(3.5, 2.5), Point2D(3.5, 3.5), Point2D(2.5, 3.5),
                         Point2D(2.5, 2.5), Point2D(2.5, 1.5), Point2D(3.5, 1.5)};

    testSearch(Rect(Point2D(0., 0.), Point2D(4.0, 4.0)),                // areaRect
               1.0,                                                     // radius
               0.001,                                                   // accuracy
               points,                                                  // points
               {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1},        // expectedBoxSizes
               {{5, 1, 3}, {0, 2}, {3, 1}, {4, 2, 0}, {3, 5}, {0, 4}}); // expectedNeighbours
}

void NeighboursSearchTestSuite::searchInDifferentBoxesLeftSide()
{
    TestPoints points = {Point2D(0.5, 2.5), Point2D(0.5, 3.5), Point2D(1.5, 3.5),
                         Point2D(1.5, 2.5), Point2D(1.5, 1.5), Point2D(0.5, 1.5)};

    testSearch(Rect(Point2D(0., 0.), Point2D(4.0, 4.0)),                // areaRect
               1.0,                                                     // radius
               0.001,                                                   // accuracy
               points,                                                  // points
               {0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},        // expectedBoxSizes
               {{5, 1, 3}, {0, 2}, {3, 1}, {4, 2, 0}, {3, 5}, {0, 4}}); // expectedNeighbours
}

void NeighboursSearchTestSuite::searchInDifferentBoxesCenterBottom()
{
    TestPoints points = {Point2D(1.5, 0.5), Point2D(0.5, 0.5), Point2D(0.5, 1.5),
                         Point2D(1.5, 1.5), Point2D(2.5, 1.5), Point2D(2.5, 0.5)};

    testSearch(Rect(Point2D(0., 0.), Point2D(4.0, 4.0)),                // areaRect
               1.0,                                                     // radius
               0.001,                                                   // accuracy
               points,                                                  // points
               {1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},        // expectedBoxSizes
               {{3, 1, 5}, {2, 0}, {1, 3}, {0, 2, 4}, {5, 3}, {4, 0}}); // expectedNeighbours
}

void NeighboursSearchTestSuite::searchInDifferentBoxesCenterTop()
{
    TestPoints points = {Point2D(1.5, 3.5), Point2D(0.5, 3.5), Point2D(0.5, 2.5),
                         Point2D(1.5, 2.5), Point2D(2.5, 2.5), Point2D(2.5, 3.5)};

    testSearch(Rect(Point2D(0., 0.), Point2D(4.0, 4.0)),                // areaRect
               1.0,                                                     // radius
               0.001,                                                   // accuracy
               points,                                                  // points
               {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0},        // expectedBoxSizes
               {{3, 1, 5}, {2, 0}, {1, 3}, {0, 2, 4}, {5, 3}, {4, 0}}); // expectedNeighbours
}

void NeighboursSearchTestSuite::searchInCornerOfBoxesCenter()
{
    TestPoints points = {Point2D(1.0, 1.0), Point2D(1.0, 2.0), Point2D(1.0, 0.0), Point2D(0.0, 1.0), Point2D(2.0, 1.0)};

    testSearch(Rect(Point2D(0., 0.), Point2D(2.0, 2.0)), // areaRect
               1.0,                                      // radius
               0.001,                                    // accuracy
               points,                                   // points
               {0, 1, 1, 3},                             // expectedBoxSizes
               {{1, 4, 2, 3}, {0}, {0}, {0}, {0}});      // expectedNeighbours
}

void NeighboursSearchTestSuite::searchInCornerOfBoxesCorners()
{
    TestPoints points = {Point2D(0., 0.), Point2D(0., 1.), Point2D(0., 2.), Point2D(1., 2.),
                         Point2D(2., 2.), Point2D(2., 1.), Point2D(2., 0.), Point2D(1., 0.)};

    testSearch(Rect(Point2D(0., 0.), Point2D(2.0, 2.0)),                          // areaRect
               1.0,                                                               // radius
               0.001,                                                             // accuracy
               points,                                                            // points
               {1, 2, 2, 3},                                                      // expectedBoxSizes
               {{1, 7}, {2, 0}, {1, 3}, {4, 2}, {3, 5}, {4, 6}, {7, 5}, {6, 0}}); // expectedNeighbours
}

//-------------------------------------------------

void NeighboursSearchTestSuite::searchInOneBox3D()
{
    TestPoints3D points = { Point3D(0.5, 0.5, 0.5),
                            Point3D(0.6, 0.6, 0.6),
                            Point3D(0.7, 0.7, 0.7) };

    testSearch3D(Cuboid(Point3D(0., 0., 0.), 1.0, 1.0, 1.0),  // areaRect
                 0.5,                                         // radius
                 0.001,                                       // accuracy
                 points,                                      // points
                 { 0, 0, 0, 0,
                   0, 0, 0, 3
                 },                     // expectedBoxSizes
                 { { 1, 4, 5, 3, 6, 7, 2 },
                   { 0, 5, 4, 2, 7, 6, 3 },
                   { 3, 6, 7, 1, 4, 5, 0 },
                   { 2, 7, 6, 0, 5, 4, 1 },
                   { 5, 0, 1, 7, 2, 3, 6 },
                   { 4, 1, 0, 6, 3, 2, 7 },
                   { 7, 2, 3, 5, 0, 1, 4 },
                   { 6, 3, 2, 4, 1, 0, 5 }
                 },                     // expectedBoxNeighbours
                 { {1, 2},
                   {0, 2},
                   {0, 1}
                 } );                   // expectedNeighbours
}

void NeighboursSearchTestSuite::searchInDifferentBoxesCenterBack3D()
{
    TestPoints3D points = { Point3D(0.75, 0.25, 0.75),   // 10
                            Point3D(0.45, 0.25, 0.75),   // 9
                            Point3D(0.75, 0.25, 0.45),   // 1
                            Point3D(1.05, 0.25, 0.75),   // 11
                            Point3D(0.75, 0.25, 1.05),   // 19
                            Point3D(0.75, 0.75, 0.75) }; // 13

    testSearch3D(Cuboid(Point3D(0., 0., 0.), 1.5, 1.5, 1.5),  // areaRect
                 0.5,                                         // radius
                 0.001,                                       // accuracy
                 points,                                      // points
                 { 0, 1, 0, 0, 0, 0, 0, 0, 0,
                   1, 1, 1, 0, 1, 0, 0, 0, 0,
                   0, 1, 0, 0, 0, 0, 0, 0, 0
                 },                   // expectedBoxSizes
                 { { 1, 9, 10, 4, 12, 13, 3 },
                   { 2, 0, 10, 11, 9, 5, 3, 13, 14, 12, 4 },
                   { 1, 11, 10, 4, 14, 13, 5 },
                   { 4, 12, 13, 7, 15, 16, 6, 1, 9, 10, 0 },
                   { 5, 3, 13, 14, 12, 8, 6, 16, 17, 15, 7, 2, 0, 10, 11, 9, 1 },
                   { 4, 14, 13, 7, 17, 16, 8, 1, 11, 10, 2 },
                   { 7, 15, 16, 4, 12, 13, 3 },
                   { 8, 6, 16, 17, 15, 5, 3, 13, 14, 12, 4 },
                   { 7, 17, 16, 4, 14, 13, 5 },
                   { 10, 18, 0, 19, 1, 13, 21, 3, 22, 4, 12 },
                   { 11, 9, 19, 1, 20, 18, 2, 0, 14, 12, 22, 4, 23, 21, 5, 3, 13 },
                   { 10, 20, 2, 19, 1, 13, 23, 5, 22, 4, 14 },
                   { 13, 21, 3, 22, 4, 16, 24, 6, 25, 7, 15, 10, 18, 0, 19, 1, 9 },
                   { 14, 12, 22, 4, 23, 21, 5, 3, 17, 15, 25, 7, 26, 24, 8, 6, 16, 11, 9, 19, 1, 20, 18, 2, 0, 10 },
                   { 13, 23, 5, 22, 4, 16, 26, 8, 25, 7, 17, 10, 20, 2, 19, 1, 11 },
                   { 16, 24, 6, 25, 7, 13, 21, 3, 22, 4, 12 },
                   { 17, 15, 25, 7, 26, 24, 8, 6, 14, 12, 22, 4, 23, 21, 5, 3, 13 },
                   { 16, 26, 8, 25, 7, 13, 23, 5, 22, 4, 14 },
                   { 19, 9, 10, 22, 12, 13, 21 },
                   { 20, 18, 10, 11, 9, 23, 21, 13, 14, 12, 22 },
                   { 19, 11, 10, 22, 14, 13, 23 },
                   { 22, 12, 13, 25, 15, 16, 24, 19, 9, 10, 18 },
                   { 23, 21, 13, 14, 12, 26, 24, 16, 17, 15, 25, 20, 18, 10, 11, 9, 19 },
                   { 22, 14, 13, 25, 17, 16, 26, 19, 11, 10, 20 },
                   { 25, 15, 16, 22, 12, 13, 21 },
                   { 26, 24, 16, 17, 15, 23, 21, 13, 14, 12, 22 },
                   { 25, 17, 16, 22, 14, 13, 23 }
                 },                     // expectedBoxNeighbours
                 { { 3, 1, 4, 2, 5 },
                   { 0, 4, 2 },
                   { 0, 3, 1 },
                   { 0, 4, 2 },
                   { 0, 3, 1 },
                   { 0 }
                 } );                   // expectedNeighbours
}

void NeighboursSearchTestSuite::searchInDifferentBoxesCenterMiddle3D()
{
    TestPoints3D points = { Point3D(0.15, 0.35, 0.15),   // 33
                            Point3D(0.2, 0.35, 0.15),    // 34
                            Point3D(0.09, 0.35, 0.15),   // 32
                            Point3D(0.15, 0.35, 0.2),    // 53
                            Point3D(0.15, 0.35, 0.09),   // 13
                            Point3D(0.2, 0.29, 0.2),     // 50
                            Point3D(0.09, 0.29, 0.09),   // 8
                            Point3D(0.09, 0.41, 0.2),    // 56
                            Point3D(0.2, 0.41, 0.09) };  // 18
    testSearch3D(Cuboid(Point3D(0., 0., 0.), 0.4, 0.5, 0.3001),  // areaRect
                 0.1,                                         // radius
                 0.001,                                       // accuracy
                 points,                                      // points
                 { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0
                 },  // expectedBoxSizes
                 {   { 1, 20, 21, 5, 24, 25, 4 },
                     { 2, 0, 21, 22, 20, 6, 4, 25, 26, 24, 5 },
                     { 3, 1, 22, 23, 21, 7, 5, 26, 27, 25, 6 },
                     { 2, 23, 22, 6, 27, 26, 7 },
                     { 5, 24, 25, 9, 28, 29, 8, 1, 20, 21, 0 },
                     { 6, 4, 25, 26, 24, 10, 8, 29, 30, 28, 9, 2, 0, 21, 22, 20, 1 },
                     { 7, 5, 26, 27, 25, 11, 9, 30, 31, 29, 10, 3, 1, 22, 23, 21, 2 },
                     { 6, 27, 26, 10, 31, 30, 11, 2, 23, 22, 3 },
                     { 9, 28, 29, 13, 32, 33, 12, 5, 24, 25, 4 },
                     { 10, 8, 29, 30, 28, 14, 12, 33, 34, 32, 13, 6, 4, 25, 26, 24, 5 },
                     { 11, 9, 30, 31, 29, 15, 13, 34, 35, 33, 14, 7, 5, 26, 27, 25, 6 },
                     { 10, 31, 30, 14, 35, 34, 15, 6, 27, 26, 7 },
                     { 13, 32, 33, 17, 36, 37, 16, 9, 28, 29, 8 },
                     { 14, 12, 33, 34, 32, 18, 16, 37, 38, 36, 17, 10, 8, 29, 30, 28, 9 },
                     { 15, 13, 34, 35, 33, 19, 17, 38, 39, 37, 18, 11, 9, 30, 31, 29, 10 },
                     { 14, 35, 34, 18, 39, 38, 19, 10, 31, 30, 11 },
                     { 17, 36, 37, 13, 32, 33, 12 },
                     { 18, 16, 37, 38, 36, 14, 12, 33, 34, 32, 13 },
                     { 19, 17, 38, 39, 37, 15, 13, 34, 35, 33, 14 },
                     { 18, 39, 38, 14, 35, 34, 15 },
                     { 21, 40, 0, 41, 1, 25, 44, 4, 45, 5, 24 },
                     { 22, 20, 41, 1, 42, 40, 2, 0, 26, 24, 45, 5, 46, 44, 6, 4, 25 },
                     { 23, 21, 42, 2, 43, 41, 3, 1, 27, 25, 46, 6, 47, 45, 7, 5, 26 },
                     { 22, 43, 3, 42, 2, 26, 47, 7, 46, 6, 27 },
                     { 25, 44, 4, 45, 5, 29, 48, 8, 49, 9, 28, 21, 40, 0, 41, 1, 20 },
                     { 26, 24, 45, 5, 46, 44, 6, 4, 30, 28, 49, 9, 50, 48, 10, 8, 29, 22, 20, 41, 1, 42, 40, 2, 0, 21 },
                     { 27, 25, 46, 6, 47, 45, 7, 5, 31, 29, 50, 10, 51, 49, 11, 9, 30, 23, 21, 42, 2, 43, 41, 3, 1, 22 },
                     { 26, 47, 7, 46, 6, 30, 51, 11, 50, 10, 31, 22, 43, 3, 42, 2, 23 },
                     { 29, 48, 8, 49, 9, 33, 52, 12, 53, 13, 32, 25, 44, 4, 45, 5, 24 },
                     { 30, 28, 49, 9, 50, 48, 10, 8, 34, 32, 53, 13, 54, 52, 14, 12, 33, 26, 24, 45, 5, 46, 44, 6, 4, 25 },
                     { 31, 29, 50, 10, 51, 49, 11, 9, 35, 33, 54, 14, 55, 53, 15, 13, 34, 27, 25, 46, 6, 47, 45, 7, 5, 26 },
                     { 30, 51, 11, 50, 10, 34, 55, 15, 54, 14, 35, 26, 47, 7, 46, 6, 27 },
                     { 33, 52, 12, 53, 13, 37, 56, 16, 57, 17, 36, 29, 48, 8, 49, 9, 28 },
                     { 34, 32, 53, 13, 54, 52, 14, 12, 38, 36, 57, 17, 58, 56, 18, 16, 37, 30, 28, 49, 9, 50, 48, 10, 8, 29 },
                     { 35, 33, 54, 14, 55, 53, 15, 13, 39, 37, 58, 18, 59, 57, 19, 17, 38, 31, 29, 50, 10, 51, 49, 11, 9, 30 },
                     { 34, 55, 15, 54, 14, 38, 59, 19, 58, 18, 39, 30, 51, 11, 50, 10, 31 },
                     { 37, 56, 16, 57, 17, 33, 52, 12, 53, 13, 32 },
                     { 38, 36, 57, 17, 58, 56, 18, 16, 34, 32, 53, 13, 54, 52, 14, 12, 33 },
                     { 39, 37, 58, 18, 59, 57, 19, 17, 35, 33, 54, 14, 55, 53, 15, 13, 34 },
                     { 38, 59, 19, 58, 18, 34, 55, 15, 54, 14, 35 },
                     { 41, 20, 21, 45, 24, 25, 44 },
                     { 42, 40, 21, 22, 20, 46, 44, 25, 26, 24, 45 },
                     { 43, 41, 22, 23, 21, 47, 45, 26, 27, 25, 46 },
                     { 42, 23, 22, 46, 27, 26, 47 },
                     { 45, 24, 25, 49, 28, 29, 48, 41, 20, 21, 40 },
                     { 46, 44, 25, 26, 24, 50, 48, 29, 30, 28, 49, 42, 40, 21, 22, 20, 41 },
                     { 47, 45, 26, 27, 25, 51, 49, 30, 31, 29, 50, 43, 41, 22, 23, 21, 42 },
                     { 46, 27, 26, 50, 31, 30, 51, 42, 23, 22, 43 },
                     { 49, 28, 29, 53, 32, 33, 52, 45, 24, 25, 44 },
                     { 50, 48, 29, 30, 28, 54, 52, 33, 34, 32, 53, 46, 44, 25, 26, 24, 45 },
                     { 51, 49, 30, 31, 29, 55, 53, 34, 35, 33, 54, 47, 45, 26, 27, 25, 46 },
                     { 50, 31, 30, 54, 35, 34, 55, 46, 27, 26, 47 },
                     { 53, 32, 33, 57, 36, 37, 56, 49, 28, 29, 48 },
                     { 54, 52, 33, 34, 32, 58, 56, 37, 38, 36, 57, 50, 48, 29, 30, 28, 49 },
                     { 55, 53, 34, 35, 33, 59, 57, 38, 39, 37, 58, 51, 49, 30, 31, 29, 50 },
                     { 54, 35, 34, 58, 39, 38, 59, 50, 31, 30, 51 },
                     { 57, 36, 37, 53, 32, 33, 52 },
                     { 58, 56, 37, 38, 36, 54, 52, 33, 34, 32, 53 },
                     { 59, 57, 38, 39, 37, 55, 53, 34, 35, 33, 54 },
                     { 58, 39, 38, 54, 35, 34, 55 }
                 },   // expectedBoxNeighbours
                 { { 1, 2, 3, 4, 7, 8, 5 },
                   { 0, 3, 4, 8, 5 },
                   { 0, 3, 4, 7, 6 },
                   { 0, 1, 2, 7, 5 },
                   { 0, 1, 2, 8, 6 },
                   { 3, 1, 0 },
                   { 4, 2 },
                   { 3, 2, 0 },
                   { 4, 1, 0 }
                 } );                    // expectedNeighbours
}

/// NeighboursSearch::insertPointsIntoBoxes() tests

void NeighboursSearchTestSuite::insertPointsIntoBoxesCornerPoints()
{
    TestPoints points = {Point2D(0.0, 0.0), Point2D(2.0, 0.0), Point2D(4.0, 0.0), Point2D(0.0, 2.0), Point2D(0.0, 4.0),
                         Point2D(2.0, 2.0), Point2D(2.0, 4.0), Point2D(4.0, 2.0), Point2D(4.0, 4.0)};

    testInsert(Rect(Point2D(0., 0.), Point2D(4.0, 4.0)), // areaRect
               2.0,                                      // radius
               0.001,                                    // accuracy
               points,                                   // points
               {1, 2, 2, 4},                             // expectedBoxSizes
               {{0}, {1, 2}, {3, 4}, {5, 6, 7, 8}});     // expectedPointsInBoxes
}

void NeighboursSearchTestSuite::insertPointsIntoBoxesBorderPoints()
{
    TestPoints points = {Point2D(0.0, 1.0), Point2D(0.0, 3.0), Point2D(1.0, 4.0), Point2D(3.0, 4.0),
                         Point2D(4.0, 3.0), Point2D(4.0, 1.0), Point2D(3.0, 0.0), Point2D(1.0, 0.0)};

    testInsert(Rect(Point2D(0., 0.), Point2D(4.0, 4.0)), // areaRect
               2.0,                                      // radius
               0.001,                                    // accuracy
               points,                                   // points
               {2, 2, 2, 2},                             // expectedBoxSizes
               {{0, 7}, {5, 6}, {1, 2}, {3, 4}});        // expectedPointsInBoxes
}

void NeighboursSearchTestSuite::insertPointsIntoBoxesInnerPoints()
{
    TestPoints points = {Point2D(0.5, 0.5), Point2D(1.0, 1.0), Point2D(1.5, 1.5), Point2D(2.5, 0.5), Point2D(3.0, 1.0),
                         Point2D(3.5, 1.5), Point2D(4.5, 0.5), Point2D(5.0, 1.0), Point2D(5.5, 1.5), Point2D(0.5, 2.5),
                         Point2D(1.0, 3.0), Point2D(1.5, 3.5), Point2D(2.5, 2.5), Point2D(3.0, 3.0), Point2D(3.5, 3.5),
                         Point2D(4.5, 2.5), Point2D(5.0, 3.0), Point2D(5.5, 3.5), Point2D(0.5, 4.5), Point2D(1.0, 5.0),
                         Point2D(1.5, 5.5), Point2D(2.5, 4.5), Point2D(3.0, 5.0), Point2D(3.5, 5.5), Point2D(4.5, 4.5),
                         Point2D(5.0, 5.0), Point2D(5.5, 5.5)};

    testInsert(Rect(Point2D(0., 0.), Point2D(6.0, 6.0)), // areaRect
               2.0,                                      // radius
               0.001,                                    // accuracy
               points,                                   // points
               {3, 3, 3, 3, 3, 3, 3, 3, 3},              // expectedBoxSizes
               {{0, 1, 2},
                {3, 4, 5},
                {6, 7, 8},
                {9, 10, 11},
                {12, 13, 14},
                {15, 16, 17},
                {18, 19, 20},
                {21, 22, 23},
                {24, 25, 26}}); // expectedPointsInBoxes
}

void NeighboursSearchTestSuite::insertPointsIntoBoxesCenterBoxFrame()
{
    TestPoints points = {Point2D(2.0, 2.0), Point2D(2.5, 2.5),       Point2D(3.0, 3.0),      Point2D(3.5, 3.5),
                         Point2D(4.0, 4.0), Point2D(2.0001, 2.0001), Point2D(2.0, 4.0),      Point2D(2.5, 3.5),
                         Point2D(3.5, 2.5), Point2D(4.0, 2.0),       Point2D(2.5, 3.0),      Point2D(3.5, 3.0),
                         Point2D(3.0, 3.5), Point2D(3.0, 2.5),       Point2D(2.5, 2.0),      Point2D(3.0, 2.0),
                         Point2D(3.5, 2.0), Point2D(2.5, 4.0),       Point2D(3.0, 4.0),      Point2D(3.5, 4.0),
                         Point2D(2.0, 2.5), Point2D(2.0, 3.0),       Point2D(2.0, 3.5),      Point2D(4.0, 2.5),
                         Point2D(4.0, 3.0), Point2D(4.0, 3.5),       Point2D(3.9999, 3.9999)};

    testInsert(Rect(Point2D(0., 0.), Point2D(6.0, 6.0)), // areaRect
               2.0,                                      // radius
               0.001,                                    // accuracy
               points,                                   // points
               {0, 0, 0, 0, 18, 4, 0, 4, 1},             // expectedBoxSizes
               {{},
                {},
                {},
                {},
                {0, 1, 2, 3, 5, 7, 8, 10, 11, 12, 13, 14, 15, 16, 20, 21, 22, 26},
                {9, 23, 24, 25},
                {},
                {6, 17, 18, 19},
                {4}}); // expectedPointsInBoxes
}

void NeighboursSearchTestSuite::insertPointsIntoBoxesInnerFrame()
{
    TestPoints points = {Point2D(0.5, 2.0), Point2D(1.0, 2.0), Point2D(1.5, 2.0), Point2D(2.5, 2.0), Point2D(3.0, 2.0),
                         Point2D(3.5, 2.0), Point2D(4.5, 2.0), Point2D(5.0, 2.0), Point2D(5.5, 2.0), Point2D(0.5, 4.0),
                         Point2D(1.0, 4.0), Point2D(1.5, 4.0), Point2D(2.5, 4.0), Point2D(3.0, 4.0), Point2D(3.5, 4.0),
                         Point2D(4.5, 4.0), Point2D(5.0, 4.0), Point2D(5.5, 4.0), Point2D(2.0, 0.5), Point2D(2.0, 1.0),
                         Point2D(2.0, 1.5), Point2D(2.0, 2.5), Point2D(2.0, 3.0), Point2D(2.0, 3.5), Point2D(2.0, 4.5),
                         Point2D(2.0, 5.0), Point2D(2.0, 5.5), Point2D(4.0, 0.5), Point2D(4.0, 1.0), Point2D(4.0, 1.5),
                         Point2D(4.0, 2.5), Point2D(4.0, 3.0), Point2D(4.0, 3.5), Point2D(4.0, 4.5), Point2D(4.0, 5.0),
                         Point2D(4.0, 5.5)};

    testInsert(Rect(Point2D(0., 0.), Point2D(6.0, 6.0)), // areaRect
               2.0,                                      // radius
               0.001,                                    // accuracy
               points,                                   // points
               {0, 3, 3, 3, 6, 6, 3, 6, 6},              // expectedBoxSizes
               {{},
                {18, 19, 20},
                {27, 28, 29},
                {0, 1, 2},
                {3, 4, 5, 21, 22, 23},
                {6, 7, 8, 30, 31, 32},
                {9, 10, 11},
                {12, 13, 14, 24, 25, 26},
                {15, 16, 17, 33, 34, 35}}); // expectedPointsInBoxes
}

void NeighboursSearchTestSuite::insertPointsIntoBoxesTopRightBox()
{
    TestPoints points = {Point2D(4.0, 4.0), Point2D(4.5, 4.0), Point2D(5.0, 4.0), Point2D(5.5, 4.0), Point2D(6.0, 4.0),
                         Point2D(4.0, 4.5), Point2D(4.5, 4.5), Point2D(5.0, 4.5), Point2D(5.5, 4.5), Point2D(6.0, 4.5),
                         Point2D(4.0, 5.0), Point2D(4.5, 5.0), Point2D(5.0, 5.0), Point2D(5.5, 5.0), Point2D(6.0, 5.0),
                         Point2D(4.0, 5.5), Point2D(4.5, 5.5), Point2D(5.0, 5.5), Point2D(5.5, 5.5), Point2D(6.0, 5.5),
                         Point2D(4.0, 6.0), Point2D(4.5, 6.0), Point2D(5.0, 6.0), Point2D(5.5, 6.0), Point2D(6.0, 6.0)};

    testInsert(
        Rect(Point2D(0., 0.), Point2D(6.0, 6.0)), // areaRect
        2.0,                                      // radius
        0.001,                                    // accuracy
        points,                                   // points
        {0, 0, 0, 0, 0, 0, 0, 0, 25},             // expectedBoxSizes
        {{}, {}, {}, {}, {}, {}, {}, {}, {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12,
                                          13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24}}); // expectedPointsInBoxes
}

void NeighboursSearchTestSuite::insertPointsIntoBoxesTopLeftBox()
{
    TestPoints points = {Point2D(0.0, 4.0), Point2D(0.5, 4.0), Point2D(1.0, 4.0), Point2D(1.5, 4.0), Point2D(2.0, 4.0),
                         Point2D(0.0, 4.5), Point2D(0.5, 4.5), Point2D(1.0, 4.5), Point2D(1.5, 4.5), Point2D(2.0, 4.5),
                         Point2D(0.0, 5.0), Point2D(0.5, 5.0), Point2D(1.0, 5.0), Point2D(1.5, 5.0), Point2D(2.0, 5.0),
                         Point2D(0.0, 5.5), Point2D(0.5, 5.5), Point2D(1.0, 5.5), Point2D(1.5, 5.5), Point2D(2.0, 5.5),
                         Point2D(0.0, 6.0), Point2D(0.5, 6.0), Point2D(1.0, 6.0), Point2D(1.5, 6.0), Point2D(2.0, 6.0)};

    testInsert(Rect(Point2D(0., 0.), Point2D(6.0, 6.0)), // areaRect
               2.0,                                      // radius
               0.001,                                    // accuracy
               points,                                   // points
               {0, 0, 0, 0, 0, 0, 20, 5, 0},             // expectedBoxSizes
               {{},
                {},
                {},
                {},
                {},
                {},
                {0, 1, 2, 3, 5, 6, 7, 8, 10, 11, 12, 13, 15, 16, 17, 18, 20, 21, 22, 23},
                {4, 9, 14, 19, 24},
                {}}); // expectedPointsInBoxes
}

void NeighboursSearchTestSuite::insertPointsIntoBoxesBottomLeftBox()
{
    TestPoints points = {Point2D(0.0, 0.0), Point2D(0.5, 0.0), Point2D(1.0, 0.0), Point2D(1.5, 0.0), Point2D(2.0, 0.0),
                         Point2D(0.0, 0.5), Point2D(0.5, 0.5), Point2D(1.0, 0.5), Point2D(1.5, 0.5), Point2D(2.0, 0.5),
                         Point2D(0.0, 1.0), Point2D(0.5, 1.0), Point2D(1.0, 1.0), Point2D(1.5, 1.0), Point2D(2.0, 1.0),
                         Point2D(0.0, 1.5), Point2D(0.5, 1.5), Point2D(1.0, 1.5), Point2D(1.5, 1.5), Point2D(2.0, 1.5),
                         Point2D(0.0, 2.0), Point2D(0.5, 2.0), Point2D(1.0, 2.0), Point2D(1.5, 2.0), Point2D(2.0, 2.0)};

    testInsert(Rect(Point2D(0., 0.), Point2D(6.0, 6.0)), // areaRect
               2.0,                                      // radius
               0.001,                                    // accuracy
               points,                                   // points
               {16, 4, 0, 4, 1, 0, 0, 0, 0},             // expectedBoxSizes
               {{0, 1, 2, 3, 5, 6, 7, 8, 10, 11, 12, 13, 15, 16, 17, 18},
                {4, 9, 14, 19},
                {},
                {20, 21, 22, 23},
                {24},
                {},
                {},
                {},
                {}}); // expectedPointsInBoxes
}

void NeighboursSearchTestSuite::insertPointsIntoBoxesBottomRightBox()
{
    TestPoints points = {Point2D(4.0, 0.0), Point2D(4.5, 0.0), Point2D(5.0, 0.0), Point2D(5.5, 0.0), Point2D(6.0, 0.0),
                         Point2D(4.0, 0.5), Point2D(4.5, 0.5), Point2D(5.0, 0.5), Point2D(5.5, 0.5), Point2D(6.0, 0.5),
                         Point2D(4.0, 1.0), Point2D(4.5, 1.0), Point2D(5.0, 1.0), Point2D(5.5, 1.0), Point2D(6.0, 1.0),
                         Point2D(4.0, 1.5), Point2D(4.5, 1.5), Point2D(5.0, 1.5), Point2D(5.5, 1.5), Point2D(6.0, 1.5),
                         Point2D(4.0, 2.0), Point2D(4.5, 2.0), Point2D(5.0, 2.0), Point2D(5.5, 2.0), Point2D(6.0, 2.0)};

    testInsert(Rect(Point2D(0., 0.), Point2D(6.0, 6.0)), // areaRect
               2.0,                                      // radius
               0.001,                                    // accuracy
               points,                                   // points
               {0, 0, 20, 0, 0, 5, 0, 0, 0},             // expectedBoxSizes
               {{},
                {},
                {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19},
                {},
                {},
                {20, 21, 22, 23, 24},
                {},
                {},
                {}}); // expectedPointsInBoxes
}

void NeighboursSearchTestSuite::insertPointsIntoBoxesBottomCenterBox()
{
    TestPoints points = {Point2D(2.0, 0.0), Point2D(2.5, 0.0), Point2D(3.0, 0.0), Point2D(3.5, 0.0), Point2D(4.0, 0.0),
                         Point2D(2.0, 0.5), Point2D(2.5, 0.5), Point2D(3.0, 0.5), Point2D(3.5, 0.5), Point2D(4.0, 0.5),
                         Point2D(2.0, 1.0), Point2D(2.5, 1.0), Point2D(3.0, 1.0), Point2D(3.5, 1.0), Point2D(4.0, 1.0),
                         Point2D(2.0, 1.5), Point2D(2.5, 1.5), Point2D(3.0, 1.5), Point2D(3.5, 1.5), Point2D(4.0, 1.5),
                         Point2D(2.0, 2.0), Point2D(2.5, 2.0), Point2D(3.0, 2.0), Point2D(3.5, 2.0), Point2D(4.0, 2.0)};

    testInsert(Rect(Point2D(0., 0.), Point2D(6.0, 6.0)), // areaRect
               2.0,                                      // radius
               0.001,                                    // accuracy
               points,                                   // points
               {0, 16, 4, 0, 4, 1, 0, 0, 0},             // expectedBoxSizes
               {{},
                {0, 1, 2, 3, 5, 6, 7, 8, 10, 11, 12, 13, 15, 16, 17, 18},
                {4, 9, 14, 19},
                {},
                {20, 21, 22, 23},
                {24},
                {},
                {},
                {}}); // expectedPointsInBoxes
}

void NeighboursSearchTestSuite::insertPointsIntoBoxesLeftCenterBox()
{
    TestPoints points = {Point2D(0.0, 2.0), Point2D(0.5, 2.0), Point2D(1.0, 2.0), Point2D(1.5, 2.0), Point2D(2.0, 2.0),
                         Point2D(0.0, 2.5), Point2D(0.5, 2.5), Point2D(1.0, 2.5), Point2D(1.5, 2.5), Point2D(2.0, 2.5),
                         Point2D(0.0, 3.0), Point2D(0.5, 3.0), Point2D(1.0, 3.0), Point2D(1.5, 3.0), Point2D(2.0, 3.0),
                         Point2D(0.0, 3.5), Point2D(0.5, 3.5), Point2D(1.0, 3.5), Point2D(1.5, 3.5), Point2D(2.0, 3.5),
                         Point2D(0.0, 4.0), Point2D(0.5, 4.0), Point2D(1.0, 4.0), Point2D(1.5, 4.0), Point2D(2.0, 4.0)};

    testInsert(Rect(Point2D(0., 0.), Point2D(6.0, 6.0)), // areaRect
               2.0,                                      // radius
               0.001,                                    // accuracy
               points,                                   // points
               {0, 0, 0, 16, 4, 0, 4, 1, 0},             // expectedBoxSizes
               {{},
                {},
                {},
                {0, 1, 2, 3, 5, 6, 7, 8, 10, 11, 12, 13, 15, 16, 17, 18},
                {4, 9, 14, 19},
                {},
                {20, 21, 22, 23},
                {24},
                {}}); // expectedPointsInBoxes
}

void NeighboursSearchTestSuite::insertPointsIntoBoxesTopCenterBox()
{
    TestPoints points = {Point2D(2.0, 4.0), Point2D(2.5, 4.0), Point2D(3.0, 4.0), Point2D(3.5, 4.0), Point2D(4.0, 4.0),
                         Point2D(2.0, 4.5), Point2D(2.5, 4.5), Point2D(3.0, 4.5), Point2D(3.5, 4.5), Point2D(4.0, 4.5),
                         Point2D(2.0, 5.0), Point2D(2.5, 5.0), Point2D(3.0, 5.0), Point2D(3.5, 5.0), Point2D(4.0, 5.0),
                         Point2D(2.0, 5.5), Point2D(2.5, 5.5), Point2D(3.0, 5.5), Point2D(3.5, 5.5), Point2D(4.0, 5.5),
                         Point2D(2.0, 6.0), Point2D(2.5, 6.0), Point2D(3.0, 6.0), Point2D(3.5, 6.0), Point2D(4.0, 6.0)};

    testInsert(Rect(Point2D(0., 0.), Point2D(6.0, 6.0)), // areaRect
               2.0,                                      // radius
               0.001,                                    // accuracy
               points,                                   // points
               {0, 0, 0, 0, 0, 0, 0, 20, 5},             // expectedBoxSizes
               {{},
                {},
                {},
                {},
                {},
                {},
                {},
                {0, 1, 2, 3, 5, 6, 7, 8, 10, 11, 12, 13, 15, 16, 17, 18, 20, 21, 22, 23},
                {4, 9, 14, 19, 24}}); // expectedPointsInBoxes
}

void NeighboursSearchTestSuite::insertPointsIntoBoxesRightCenterBox()
{
    TestPoints points = {Point2D(4.0, 2.0), Point2D(4.5, 2.0), Point2D(5.0, 2.0), Point2D(5.5, 2.0), Point2D(6.0, 2.0),
                         Point2D(4.0, 2.5), Point2D(4.5, 2.5), Point2D(5.0, 2.5), Point2D(5.5, 2.5), Point2D(6.0, 2.5),
                         Point2D(4.0, 3.0), Point2D(4.5, 3.0), Point2D(5.0, 3.0), Point2D(5.5, 3.0), Point2D(6.0, 3.0),
                         Point2D(4.0, 3.5), Point2D(4.5, 3.5), Point2D(5.0, 3.5), Point2D(5.5, 3.5), Point2D(6.0, 3.5),
                         Point2D(4.0, 4.0), Point2D(4.5, 4.0), Point2D(5.0, 4.0), Point2D(5.5, 4.0), Point2D(6.0, 4.0)};

    testInsert(Rect(Point2D(0., 0.), Point2D(6.0, 6.0)), // areaRect
               2.0,                                      // radius
               0.001,                                    // accuracy
               points,                                   // points
               {0, 0, 0, 0, 0, 20, 0, 0, 5},             // expectedBoxSizes
               {{},
                {},
                {},
                {},
                {},
                {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19},
                {},
                {},
                {20, 21, 22, 23, 24}}); // expectedPointsInBoxes
}

void NeighboursSearchTestSuite::insertPointsIntoBoxesBottomLineBox()
{
    TestPoints points = {Point2D(0.0, 0.0), Point2D(1.0, 0.0), Point2D(2.0, 0.0), Point2D(3.0, 0.0), Point2D(4.0, 0.0),
                         Point2D(5.0, 0.0), Point2D(6.0, 0.0), Point2D(0.0, 1.0), Point2D(1.0, 1.0), Point2D(2.0, 1.0),
                         Point2D(3.0, 1.0), Point2D(4.0, 1.0), Point2D(5.0, 1.0), Point2D(6.0, 1.0), Point2D(0.0, 2.0),
                         Point2D(1.0, 2.0), Point2D(2.0, 2.0), Point2D(3.0, 2.0), Point2D(4.0, 2.0), Point2D(5.0, 2.0),
                         Point2D(6.0, 2.0), Point2D(0.5, 0.5), Point2D(1.5, 0.5), Point2D(2.5, 0.5), Point2D(3.5, 0.5),
                         Point2D(4.5, 0.5), Point2D(5.5, 0.5), Point2D(0.5, 1.5), Point2D(1.5, 1.5), Point2D(2.5, 1.5),
                         Point2D(3.5, 1.5), Point2D(4.5, 1.5), Point2D(5.5, 1.5)};

    testInsert(Rect(Point2D(0., 0.), Point2D(6.0, 6.0)), // areaRect
               2.0,                                      // radius
               0.001,                                    // accuracy
               points,                                   // points
               {8, 8, 10, 2, 2, 3, 0, 0, 0},             // expectedBoxSizes
               {{0, 1, 7, 8, 21, 22, 27, 28},
                {2, 3, 9, 10, 23, 24, 29, 30},
                {4, 5, 6, 11, 12, 13, 25, 26, 31, 32},
                {14, 15},
                {16, 17},
                {18, 19, 20},
                {},
                {},
                {}}); // expectedPointsInBoxes
}

void NeighboursSearchTestSuite::insertPointsIntoBoxesLeftLineBox()
{
    TestPoints points = {Point2D(0.0, 0.0), Point2D(0.0, 1.0), Point2D(0.0, 2.0), Point2D(0.0, 3.0), Point2D(0.0, 4.0),
                         Point2D(0.0, 5.0), Point2D(0.0, 6.0), Point2D(1.0, 0.0), Point2D(1.0, 1.0), Point2D(1.0, 2.0),
                         Point2D(1.0, 3.0), Point2D(1.0, 4.0), Point2D(1.0, 5.0), Point2D(1.0, 6.0), Point2D(2.0, 0.0),
                         Point2D(2.0, 1.0), Point2D(2.0, 2.0), Point2D(2.0, 3.0), Point2D(2.0, 4.0), Point2D(2.0, 5.0),
                         Point2D(2.0, 6.0), Point2D(0.5, 0.5), Point2D(0.5, 1.5), Point2D(0.5, 2.5), Point2D(0.5, 3.5),
                         Point2D(0.5, 4.5), Point2D(0.5, 5.5), Point2D(1.5, 0.5), Point2D(1.5, 1.5), Point2D(1.5, 2.5),
                         Point2D(1.5, 3.5), Point2D(1.5, 4.5), Point2D(1.5, 5.5)};

    testInsert(Rect(Point2D(0., 0.), Point2D(6.0, 6.0)), // areaRect
               2.0,                                      // radius
               0.001,                                    // accuracy
               points,                                   // points
               {8, 2, 0, 8, 2, 0, 10, 3, 0},             // expectedBoxSizes
               {{0, 1, 7, 8, 21, 22, 27, 28},
                {14, 15},
                {},
                {2, 3, 9, 10, 23, 24, 29, 30},
                {16, 17},
                {},
                {4, 5, 6, 11, 12, 13, 25, 26, 31, 32},
                {18, 19, 20},
                {}}); // expectedPointsInBoxes
}

void NeighboursSearchTestSuite::insertPointsIntoBoxesTopLineBox()
{
    TestPoints points = {Point2D(0.0, 4.0), Point2D(1.0, 4.0), Point2D(2.0, 4.0), Point2D(3.0, 4.0), Point2D(4.0, 4.0),
                         Point2D(5.0, 4.0), Point2D(6.0, 4.0), Point2D(0.0, 5.0), Point2D(1.0, 5.0), Point2D(2.0, 5.0),
                         Point2D(3.0, 5.0), Point2D(4.0, 5.0), Point2D(5.0, 5.0), Point2D(6.0, 5.0), Point2D(0.0, 6.0),
                         Point2D(1.0, 6.0), Point2D(2.0, 6.0), Point2D(3.0, 6.0), Point2D(4.0, 6.0), Point2D(5.0, 6.0),
                         Point2D(6.0, 6.0), Point2D(0.5, 4.5), Point2D(1.5, 4.5), Point2D(2.5, 4.5), Point2D(3.5, 4.5),
                         Point2D(4.5, 4.5), Point2D(5.5, 4.5), Point2D(0.5, 5.5), Point2D(1.5, 5.5), Point2D(2.5, 5.5),
                         Point2D(3.5, 5.5), Point2D(4.5, 5.5), Point2D(5.5, 5.5)};

    testInsert(Rect(Point2D(0., 0.), Point2D(6.0, 6.0)), // areaRect
               2.0,                                      // radius
               0.001,                                    // accuracy
               points,                                   // points
               {0, 0, 0, 0, 0, 0, 10, 10, 13},           // expectedBoxSizes
               {{},
                {},
                {},
                {},
                {},
                {},
                {0, 1, 7, 8, 14, 15, 21, 22, 27, 28},
                {2, 3, 9, 10, 16, 17, 23, 24, 29, 30},
                {4, 5, 6, 11, 12, 13, 18, 19, 20, 25, 26, 31, 32}}); // expectedPointsInBoxes
}

void NeighboursSearchTestSuite::insertPointsIntoBoxesRightLineBox()
{
    TestPoints points = {Point2D(4.0, 0.0), Point2D(4.0, 1.0), Point2D(4.0, 2.0), Point2D(4.0, 3.0), Point2D(4.0, 4.0),
                         Point2D(4.0, 5.0), Point2D(4.0, 6.0), Point2D(5.0, 0.0), Point2D(5.0, 1.0), Point2D(5.0, 2.0),
                         Point2D(5.0, 3.0), Point2D(5.0, 4.0), Point2D(5.0, 5.0), Point2D(5.0, 6.0), Point2D(6.0, 0.0),
                         Point2D(6.0, 1.0), Point2D(6.0, 2.0), Point2D(6.0, 3.0), Point2D(6.0, 4.0), Point2D(6.0, 5.0),
                         Point2D(6.0, 6.0), Point2D(4.5, 0.5), Point2D(4.5, 1.5), Point2D(4.5, 2.5), Point2D(4.5, 3.5),
                         Point2D(4.5, 4.5), Point2D(4.5, 5.5), Point2D(5.5, 0.5), Point2D(5.5, 1.5), Point2D(5.5, 2.5),
                         Point2D(5.5, 3.5), Point2D(5.5, 4.5), Point2D(5.5, 5.5)};

    testInsert(Rect(Point2D(0., 0.), Point2D(6.0, 6.0)), // areaRect
               2.0,                                      // radius
               0.001,                                    // accuracy
               points,                                   // points
               {0, 0, 10, 0, 0, 10, 0, 0, 13},           // expectedBoxSizes
               {{},
                {},
                {0, 1, 7, 8, 14, 15, 21, 22, 27, 28},
                {},
                {},
                {2, 3, 9, 10, 16, 17, 23, 24, 29, 30},
                {},
                {},
                {4, 5, 6, 11, 12, 13, 18, 19, 20, 25, 26, 31, 32}}); // expectedPointsInBoxes
}

void NeighboursSearchTestSuite::insertPointsIntoBoxes3x2()
{
    TestPoints points = {Point2D(0.0, 0.0), Point2D(1.0, 0.0), Point2D(2.0, 0.0), Point2D(3.0, 0.0), Point2D(0.0, 1.0),
                         Point2D(1.0, 1.0), Point2D(2.0, 1.0), Point2D(3.0, 1.0), Point2D(0.0, 2.0), Point2D(1.0, 2.0),
                         Point2D(2.0, 2.0), Point2D(3.0, 2.0), Point2D(0.5, 0.5), Point2D(1.5, 0.5), Point2D(2.5, 0.5),
                         Point2D(0.5, 1.5), Point2D(1.5, 1.5), Point2D(2.5, 1.5)};

    testInsert(Rect(Point2D(0.0, 0.0), Point2D(3.0, 2.0)),                                  // areaRect
               1.0,                                                                         // radius
               0.001,                                                                       // accuracy
               points,                                                                      // points
               {2, 2, 3, 3, 3, 5},                                                          // expectedBoxSizes
               {{0, 12}, {1, 13}, {2, 3, 14}, {4, 8, 15}, {5, 9, 16}, {6, 7, 10, 11, 17}}); // expectedPointsInBoxes
}

void NeighboursSearchTestSuite::insertPointsIntoBoxes4x2()
{
    TestPoints points = {Point2D(0.0, 0.0), Point2D(1.0, 0.0), Point2D(2.0, 0.0), Point2D(3.0, 0.0), Point2D(4.0, 0.0),
                         Point2D(0.0, 1.0), Point2D(1.0, 1.0), Point2D(2.0, 1.0), Point2D(3.0, 1.0), Point2D(4.0, 1.0),
                         Point2D(0.0, 2.0), Point2D(1.0, 2.0), Point2D(2.0, 2.0), Point2D(3.0, 2.0), Point2D(4.0, 2.0),
                         Point2D(0.5, 0.5), Point2D(1.5, 0.5), Point2D(2.5, 0.5), Point2D(3.5, 0.5), Point2D(0.5, 1.5),
                         Point2D(1.5, 1.5), Point2D(2.5, 1.5), Point2D(3.5, 1.5)};

    testInsert(Rect(Point2D(0.0, 0.0), Point2D(4.0, 2.0)), // areaRect
               1.0,                                        // radius
               0.001,                                      // accuracy
               points,                                     // points
               {2, 2, 2, 3, 3, 3, 3, 5},                   // expectedBoxSizes
               {{0, 15},
                {1, 16},
                {2, 17},
                {3, 4, 18},
                {5, 10, 19},
                {6, 11, 20},
                {7, 12, 21},
                {8, 9, 13, 14, 22}}); // expectedPointsInBoxes
}

void NeighboursSearchTestSuite::insertPointsIntoBoxes2x4()
{
    TestPoints points = {Point2D(0.0, 0.0), Point2D(1.0, 0.0), Point2D(2.0, 0.0), Point2D(0.0, 1.0), Point2D(1.0, 1.0),
                         Point2D(2.0, 1.0), Point2D(0.0, 2.0), Point2D(1.0, 2.0), Point2D(2.0, 2.0), Point2D(0.0, 3.0),
                         Point2D(1.0, 3.0), Point2D(2.0, 3.0), Point2D(0.0, 4.0), Point2D(1.0, 4.0), Point2D(2.0, 4.0),
                         Point2D(0.5, 0.5), Point2D(1.5, 0.5), Point2D(0.5, 1.5), Point2D(1.5, 1.5), Point2D(0.5, 2.5),
                         Point2D(1.5, 2.5), Point2D(0.5, 3.5), Point2D(1.5, 3.5)};

    testInsert(Rect(Point2D(0.0, 0.0), Point2D(2.0, 4.0)), // areaRect
               1.0,                                        // radius
               0.001,                                      // accuracy
               points,                                     // points
               {2, 3, 2, 3, 2, 3, 3, 5},                   // expectedBoxSizes
               {{0, 15},
                {1, 2, 16},
                {3, 17},
                {4, 5, 18},
                {6, 19},
                {7, 8, 20},
                {9, 12, 21},
                {10, 11, 13, 14, 22}}); // expectedPointsInBoxes
}

void NeighboursSearchTestSuite::insertPointsIntoBoxes8x3()
{
    TestPoints points = {
        Point2D(0.0, 0.0), Point2D(1.0, 0.0), Point2D(2.0, 0.0), Point2D(3.0, 0.0), Point2D(4.0, 0.0),
        Point2D(5.0, 0.0), Point2D(6.0, 0.0), Point2D(7.0, 0.0), Point2D(8.0, 0.0), Point2D(0.0, 1.0),
        Point2D(1.0, 1.0), Point2D(2.0, 1.0), Point2D(3.0, 1.0), Point2D(4.0, 1.0), Point2D(5.0, 1.0),
        Point2D(6.0, 1.0), Point2D(7.0, 1.0), Point2D(8.0, 1.0), Point2D(0.0, 2.0), Point2D(1.0, 2.0),
        Point2D(2.0, 2.0), Point2D(3.0, 2.0), Point2D(4.0, 2.0), Point2D(5.0, 2.0), Point2D(6.0, 2.0),
        Point2D(7.0, 2.0), Point2D(8.0, 2.0), Point2D(0.0, 3.0), Point2D(1.0, 3.0), Point2D(2.0, 3.0),
        Point2D(3.0, 3.0), Point2D(4.0, 3.0), Point2D(5.0, 3.0), Point2D(6.0, 3.0), Point2D(7.0, 3.0),
        Point2D(8.0, 3.0), Point2D(0.5, 0.5), Point2D(1.5, 0.5), Point2D(2.5, 0.5), Point2D(3.5, 0.5),
        Point2D(4.5, 0.5), Point2D(5.5, 0.5), Point2D(6.5, 0.5), Point2D(7.5, 0.5), Point2D(0.5, 1.5),
        Point2D(1.5, 1.5), Point2D(2.5, 1.5), Point2D(3.5, 1.5), Point2D(4.5, 1.5), Point2D(5.5, 1.5),
        Point2D(6.5, 1.5), Point2D(7.5, 1.5), Point2D(0.5, 2.5), Point2D(1.5, 2.5), Point2D(2.5, 2.5),
        Point2D(3.5, 2.5), Point2D(4.5, 2.5), Point2D(5.5, 2.5), Point2D(6.5, 2.5), Point2D(7.5, 2.5),
    };

    testInsert(Rect(Point2D(0.0, 0.0), Point2D(8.0, 3.0)),                               // areaRect
               1.0,                                                                      // radius
               0.001,                                                                    // accuracy
               points,                                                                   // points
               {2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 5}, // expectedBoxSizes
               {{0, 36},      {1, 37},      {2, 38},      {3, 39},
                {4, 40},      {5, 41},      {6, 42},      {7, 8, 43},
                {9, 44},      {10, 45},     {11, 46},     {12, 47},
                {13, 48},     {14, 49},     {15, 50},     {16, 17, 51},
                {18, 27, 52}, {19, 28, 53}, {20, 29, 54}, {21, 30, 55},
                {22, 31, 56}, {23, 32, 57}, {24, 33, 58}, {25, 26, 34, 35, 59}}); // expectedPointsInBoxes
}

void NeighboursSearchTestSuite::insertPointsIntoBoxes9x6()
{
    TestPoints points = {Point2D(0.0, 0.0), Point2D(1.0, 0.0), Point2D(2.0, 0.0), Point2D(3.0, 0.0), Point2D(4.0, 0.0),
                         Point2D(5.0, 0.0), Point2D(6.0, 0.0), Point2D(7.0, 0.0), Point2D(8.0, 0.0), Point2D(9.0, 0.0),
                         Point2D(0.0, 1.0), Point2D(1.0, 1.0), Point2D(2.0, 1.0), Point2D(3.0, 1.0), Point2D(4.0, 1.0),
                         Point2D(5.0, 1.0), Point2D(6.0, 1.0), Point2D(7.0, 1.0), Point2D(8.0, 1.0), Point2D(9.0, 1.0),
                         Point2D(0.0, 2.0), Point2D(1.0, 2.0), Point2D(2.0, 2.0), Point2D(3.0, 2.0), Point2D(4.0, 2.0),
                         Point2D(5.0, 2.0), Point2D(6.0, 2.0), Point2D(7.0, 2.0), Point2D(8.0, 2.0), Point2D(9.0, 2.0),
                         Point2D(0.0, 3.0), Point2D(1.0, 3.0), Point2D(2.0, 3.0), Point2D(3.0, 3.0), Point2D(4.0, 3.0),
                         Point2D(5.0, 3.0), Point2D(6.0, 3.0), Point2D(7.0, 3.0), Point2D(8.0, 3.0), Point2D(9.0, 3.0),
                         Point2D(0.0, 4.0), Point2D(1.0, 4.0), Point2D(2.0, 4.0), Point2D(3.0, 4.0), Point2D(4.0, 4.0),
                         Point2D(5.0, 4.0), Point2D(6.0, 4.0), Point2D(7.0, 4.0), Point2D(8.0, 4.0), Point2D(9.0, 4.0),
                         Point2D(0.0, 5.0), Point2D(1.0, 5.0), Point2D(2.0, 5.0), Point2D(3.0, 5.0), Point2D(4.0, 5.0),
                         Point2D(5.0, 5.0), Point2D(6.0, 5.0), Point2D(7.0, 5.0), Point2D(8.0, 5.0), Point2D(9.0, 5.0),
                         Point2D(0.0, 6.0), Point2D(1.0, 6.0), Point2D(2.0, 6.0), Point2D(3.0, 6.0), Point2D(4.0, 6.0),
                         Point2D(5.0, 6.0), Point2D(6.0, 6.0), Point2D(7.0, 6.0), Point2D(8.0, 6.0), Point2D(9.0, 6.0),

                         Point2D(0.5, 0.5), Point2D(1.5, 0.5), Point2D(2.5, 0.5), Point2D(3.5, 0.5), Point2D(4.5, 0.5),
                         Point2D(5.5, 0.5), Point2D(6.5, 0.5), Point2D(7.5, 0.5), Point2D(8.5, 0.5), Point2D(0.5, 1.5),
                         Point2D(1.5, 1.5), Point2D(2.5, 1.5), Point2D(3.5, 1.5), Point2D(4.5, 1.5), Point2D(5.5, 1.5),
                         Point2D(6.5, 1.5), Point2D(7.5, 1.5), Point2D(8.5, 1.5), Point2D(0.5, 2.5), Point2D(1.5, 2.5),
                         Point2D(2.5, 2.5), Point2D(3.5, 2.5), Point2D(4.5, 2.5), Point2D(5.5, 2.5), Point2D(6.5, 2.5),
                         Point2D(7.5, 2.5), Point2D(8.5, 2.5), Point2D(0.5, 3.5), Point2D(1.5, 3.5), Point2D(2.5, 3.5),
                         Point2D(3.5, 3.5), Point2D(4.5, 3.5), Point2D(5.5, 3.5), Point2D(6.5, 3.5), Point2D(7.5, 3.5),
                         Point2D(8.5, 3.5), Point2D(0.5, 4.5), Point2D(1.5, 4.5), Point2D(2.5, 4.5), Point2D(3.5, 4.5),
                         Point2D(4.5, 4.5), Point2D(5.5, 4.5), Point2D(6.5, 4.5), Point2D(7.5, 4.5), Point2D(8.5, 4.5),
                         Point2D(0.5, 5.5), Point2D(1.5, 5.5), Point2D(2.5, 5.5), Point2D(3.5, 5.5), Point2D(4.5, 5.5),
                         Point2D(5.5, 5.5), Point2D(6.5, 5.5), Point2D(7.5, 5.5), Point2D(8.5, 5.5)};

    testInsert(Rect(Point2D(0.0, 0.0), Point2D(9.0, 6.0)), // areaRect
               1.0,                                        // radius
               0.001,                                      // accuracy
               points,                                     // points
               {2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 3,
                2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5}, // expectedBoxSizes
               {{0, 70},       {1, 71},       {2, 72},
                {3, 73},       {4, 74},       {5, 75},
                {6, 76},       {7, 77},       {8, 9, 78},
                {10, 79},      {11, 80},      {12, 81},
                {13, 82},      {14, 83},      {15, 84},
                {16, 85},      {17, 86},      {18, 19, 87},
                {20, 88},      {21, 89},      {22, 90},
                {23, 91},      {24, 92},      {25, 93},
                {26, 94},      {27, 95},      {28, 29, 96},
                {30, 97},      {31, 98},      {32, 99},
                {33, 100},     {34, 101},     {35, 102},
                {36, 103},     {37, 104},     {38, 39, 105},
                {40, 106},     {41, 107},     {42, 108},
                {43, 109},     {44, 110},     {45, 111},
                {46, 112},     {47, 113},     {48, 49, 114},
                {50, 60, 115}, {51, 61, 116}, {52, 62, 117},
                {53, 63, 118}, {54, 64, 119}, {55, 65, 120},
                {56, 66, 121}, {57, 67, 122}, {58, 59, 68, 69, 123}}); // expectedPointsInBoxes
}

/// NeighboursSearch::findNearByBoxes() tests

void NeighboursSearchTestSuite::findNearbyBoxesTwoByTwo()
{
    Rect rect(Point2D(0., 0.), Point2D(4.0, 4.0));
    Area area(rect);

    const VectorOfSizetVectors expectedNearbyBoxes = {{2, 1, 3}, {3, 0, 2}, {0, 3, 1}, {1, 2, 0}};

    NeighboursSearch<Point2DVector> ns(area, 2.0, 0.001);

    ASSERT_EQ(ns.m_boxes.size(), ns.m_nearbyBoxes.size())
        << "The amount of boxes have to be equal in m_boxes and m_nearbyBoxes";

    for (size_t i = 0u; i < ns.m_nearbyBoxes.size(); i++)
        ASSERT_EQ(expectedNearbyBoxes[i].size(), ns.m_nearbyBoxes[i].size());

    for (size_t i = 0u; i < ns.m_nearbyBoxes.size(); i++)
        EXPECT_EQ(expectedNearbyBoxes[i], ns.m_nearbyBoxes[i]);
}

void NeighboursSearchTestSuite::findNearbyBoxesFourByTwo()
{
    Rect rect(Point2D(0., 0.), Point2D(2.0, 4.0));
    Area area(rect);

    const VectorOfSizetVectors expectedNearbyBoxes = {
        {2, 1, 3}, {3, 0, 2}, {0, 4, 3, 1, 5}, {1, 5, 2, 0, 4}, {2, 6, 5, 3, 7}, {3, 7, 4, 2, 6}, {4, 7, 5}, {5, 6, 4}};

    NeighboursSearch<Point2DVector> ns(area, 1.0, 0.001);

    ASSERT_EQ(ns.m_boxes.size(), ns.m_nearbyBoxes.size())
        << "The amount of boxes have to be equal in m_boxes and m_nearbyBoxes";

    for (size_t i = 0u; i < ns.m_nearbyBoxes.size(); i++)
        ASSERT_EQ(expectedNearbyBoxes[i].size(), ns.m_nearbyBoxes[i].size());

    for (size_t i = 0u; i < ns.m_nearbyBoxes.size(); i++)
        EXPECT_EQ(expectedNearbyBoxes[i], ns.m_nearbyBoxes[i]);
}

void NeighboursSearchTestSuite::findNearbyBoxesFourByFour()
{
    Rect rect(Point2D(0., 0.), Point2D(4.0, 4.0));
    Area area(rect);

    const VectorOfSizetVectors expectedNearbyBoxes = {{4, 1, 5},
                                                      {5, 0, 2, 4, 6},
                                                      {6, 1, 3, 5, 7},
                                                      {7, 2, 6},
                                                      {0, 8, 5, 1, 9},
                                                      {1, 9, 4, 6, 0, 8, 2, 10},
                                                      {2, 10, 5, 7, 1, 9, 3, 11},
                                                      {3, 11, 6, 2, 10},
                                                      {4, 12, 9, 5, 13},
                                                      {5, 13, 8, 10, 4, 12, 6, 14},
                                                      {6, 14, 9, 11, 5, 13, 7, 15},
                                                      {7, 15, 10, 6, 14},
                                                      {8, 13, 9},
                                                      {9, 12, 14, 8, 10},
                                                      {10, 13, 15, 9, 11},
                                                      {11, 14, 10}};

    NeighboursSearch<Point2DVector> ns(area, 1.0, 0.001);

    ASSERT_EQ(ns.m_boxes.size(), ns.m_nearbyBoxes.size())
        << "The amount of boxes have to be equal in m_boxes and m_nearbyBoxes";

    for (size_t i = 0u; i < ns.m_nearbyBoxes.size(); i++)
        ASSERT_EQ(expectedNearbyBoxes[i].size(), ns.m_nearbyBoxes[i].size());

    for (size_t i = 0u; i < ns.m_nearbyBoxes.size(); i++)
        EXPECT_EQ(expectedNearbyBoxes[i], ns.m_nearbyBoxes[i]);
}

void NeighboursSearchTestSuite::findNearbyBoxesFourByThree()
{
    Rect rect(Point2D(0., 0.), Point2D(3.0, 4.0));
    Area area(rect);

    const VectorOfSizetVectors expectedNearbyBoxes = {{3, 1, 4},
                                                      {4, 0, 2, 3, 5},
                                                      {5, 1, 4},
                                                      {0, 6, 4, 1, 7},
                                                      {1, 7, 3, 5, 0, 6, 2, 8},
                                                      {2, 8, 4, 1, 7},
                                                      {3, 9, 7, 4, 10},
                                                      {4, 10, 6, 8, 3, 9, 5, 11},
                                                      {5, 11, 7, 4, 10},
                                                      {6, 10, 7},
                                                      {7, 9, 11, 6, 8},
                                                      {8, 10, 7}};

    NeighboursSearch<Point2DVector> ns(area, 1.0, 0.001);

    EXPECT_EQ(ns.m_boxes.size(), ns.m_nearbyBoxes.size())
        << "The amount of boxes have to be equal in m_boxes and m_nearbyBoxes";

    for (size_t i = 0u; i < ns.m_nearbyBoxes.size(); i++)
        EXPECT_EQ(expectedNearbyBoxes[i].size(), ns.m_nearbyBoxes[i].size());

    for (size_t i = 0u; i < ns.m_nearbyBoxes.size(); i++)
        EXPECT_EQ(expectedNearbyBoxes[i], ns.m_nearbyBoxes[i]);
}

void NeighboursSearchTestSuite::findNearbyBoxesThreeByThree()
{
    Rect rect(Point2D(0., 0.), Point2D(6.0, 6.0));
    Area area(rect);

    const VectorOfSizetVectors expectedNearbyBoxes = {{3, 1, 4},       {4, 0, 2, 3, 5},          {5, 1, 4},
                                                      {0, 6, 4, 1, 7}, {1, 7, 3, 5, 0, 6, 2, 8}, {2, 8, 4, 1, 7},
                                                      {3, 7, 4},       {4, 6, 8, 3, 5},          {5, 7, 4}};

    NeighboursSearch<Point2DVector> ns(area, 2.0, 0.001);

    ASSERT_EQ(ns.m_boxes.size(), ns.m_nearbyBoxes.size())
        << "The amount of boxes have to be equal in m_boxes and m_nearbyBoxes";

    for (size_t i = 0u; i < ns.m_nearbyBoxes.size(); i++)
        ASSERT_EQ(expectedNearbyBoxes[i].size(), ns.m_nearbyBoxes[i].size());

    for (size_t i = 0u; i < ns.m_nearbyBoxes.size(); i++)
        EXPECT_EQ(expectedNearbyBoxes[i], ns.m_nearbyBoxes[i]);
}

} // namespace TestEnvironment
} // namespace SPHAlgorithms

using namespace SPHAlgorithms::TestEnvironment;

TEST(NeighboursSearchTestSuite, searchOneBox)
{
    NeighboursSearchTestSuite::searchInOneBox();
}

TEST(NeighboursSearchTestSuite, searchInDifferentBoxesRightBottom)
{
    NeighboursSearchTestSuite::searchInDifferentBoxesRightBottom();
}

TEST(NeighboursSearchTestSuite, searchInDifferentBoxesLeftBottom)
{
    NeighboursSearchTestSuite::searchInDifferentBoxesLeftBottom();
}

TEST(NeighboursSearchTestSuite, searchInDifferentBoxesRightTop)
{
    NeighboursSearchTestSuite::searchInDifferentBoxesRightTop();
}

TEST(NeighboursSearchTestSuite, searchInDifferentBoxesLeftTop)
{
    NeighboursSearchTestSuite::searchInDifferentBoxesLeftTop();
}

TEST(NeighboursSearchTestSuite, searchInDifferentBoxesRightSide)
{
    NeighboursSearchTestSuite::searchInDifferentBoxesRightSide();
}

TEST(NeighboursSearchTestSuite, searchInDifferentBoxesLeftSide)
{
    NeighboursSearchTestSuite::searchInDifferentBoxesLeftSide();
}

TEST(NeighboursSearchTestSuite, searchInDifferentBoxesCenterBottom)
{
    NeighboursSearchTestSuite::searchInDifferentBoxesCenterBottom();
}

TEST(NeighboursSearchTestSuite, searchInDifferentBoxesCenterTop)
{
    NeighboursSearchTestSuite::searchInDifferentBoxesCenterTop();
}

TEST(NeighboursSearchTestSuite, searchInCornerOfBoxesCenter)
{
    NeighboursSearchTestSuite::searchInCornerOfBoxesCenter();
}

TEST(NeighboursSearchTestSuite, searchInCornerOfBoxesCorners)
{
    NeighboursSearchTestSuite::searchInCornerOfBoxesCorners();
}

//-------------------------------------------------

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

//-------------------------------------------------

TEST(NeighboursSearchTestSuite, insertPointsIntoBoxesCornerPoints)
{
    NeighboursSearchTestSuite::insertPointsIntoBoxesCornerPoints();
}

TEST(NeighboursSearchTestSuite, insertPointsIntoBoxesBorderPoints)
{
    NeighboursSearchTestSuite::insertPointsIntoBoxesBorderPoints();
}

TEST(NeighboursSearchTestSuite, insertPointsIntoBoxesInnerPoints)
{
    NeighboursSearchTestSuite::insertPointsIntoBoxesInnerPoints();
}

TEST(NeighboursSearchTestSuite, insertPointsIntoBoxesCenterBoxFrame)
{
    NeighboursSearchTestSuite::insertPointsIntoBoxesCenterBoxFrame();
}

TEST(NeighboursSearchTestSuite, insertPointsIntoBoxesInnerFrame)
{
    NeighboursSearchTestSuite::insertPointsIntoBoxesInnerFrame();
}

TEST(NeighboursSearchTestSuite, insertPointsIntoBoxesTopRightBox)
{
    NeighboursSearchTestSuite::insertPointsIntoBoxesTopRightBox();
}

TEST(NeighboursSearchTestSuite, insertPointsIntoBoxesTopLeftBox)
{
    NeighboursSearchTestSuite::insertPointsIntoBoxesTopLeftBox();
}

TEST(NeighboursSearchTestSuite, insertPointsIntoBoxesBottomLeftBox)
{
    NeighboursSearchTestSuite::insertPointsIntoBoxesBottomLeftBox();
}

TEST(NeighboursSearchTestSuite, insertPointsIntoBoxesBottomRightBox)
{
    NeighboursSearchTestSuite::insertPointsIntoBoxesBottomRightBox();
}

TEST(NeighboursSearchTestSuite, insertPointsIntoBoxesBottomCenterBox)
{
    NeighboursSearchTestSuite::insertPointsIntoBoxesBottomCenterBox();
}

TEST(NeighboursSearchTestSuite, insertPointsIntoBoxesLeftCenterBox)
{
    NeighboursSearchTestSuite::insertPointsIntoBoxesLeftCenterBox();
}

TEST(NeighboursSearchTestSuite, insertPointsIntoBoxesTopCenterBox)
{
    NeighboursSearchTestSuite::insertPointsIntoBoxesTopCenterBox();
}

TEST(NeighboursSearchTestSuite, insertPointsIntoBoxesRightCenterBox)
{
    NeighboursSearchTestSuite::insertPointsIntoBoxesRightCenterBox();
}

TEST(NeighboursSearchTestSuite, insertPointsIntoBoxesBottomLineBox)
{
    NeighboursSearchTestSuite::insertPointsIntoBoxesBottomLineBox();
}

TEST(NeighboursSearchTestSuite, insertPointsIntoBoxesLeftLineBox)
{
    NeighboursSearchTestSuite::insertPointsIntoBoxesLeftLineBox();
}

TEST(NeighboursSearchTestSuite, insertPointsIntoBoxesTopLineBox)
{
    NeighboursSearchTestSuite::insertPointsIntoBoxesTopLineBox();
}

TEST(NeighboursSearchTestSuite, insertPointsIntoBoxesRightLineBox)
{
    NeighboursSearchTestSuite::insertPointsIntoBoxesRightLineBox();
}

TEST(NeighboursSearchTestSuite, insertPointsIntoBoxes3x2)
{
    NeighboursSearchTestSuite::insertPointsIntoBoxes3x2();
}

TEST(NeighboursSearchTestSuite, insertPointsIntoBoxes4x2)
{
    NeighboursSearchTestSuite::insertPointsIntoBoxes4x2();
}

TEST(NeighboursSearchTestSuite, insertPointsIntoBoxes2x4)
{
    NeighboursSearchTestSuite::insertPointsIntoBoxes2x4();
}

TEST(NeighboursSearchTestSuite, insertPointsIntoBoxes8x3)
{
    NeighboursSearchTestSuite::insertPointsIntoBoxes8x3();
}

TEST(NeighboursSearchTestSuite, insertPointsIntoBoxes9x6)
{
    NeighboursSearchTestSuite::insertPointsIntoBoxes9x6();
}

TEST(NeighboursSearchTestSuite, findNearbyBoxesTwoByTwo)
{
    NeighboursSearchTestSuite::findNearbyBoxesTwoByTwo();
}

TEST(NeighboursSearchTestSuite, findNearbyBoxesFourByTwo)
{
    NeighboursSearchTestSuite::findNearbyBoxesFourByTwo();
}

TEST(NeighboursSearchTestSuite, findNearbyBoxesFourByFour)
{
    NeighboursSearchTestSuite::findNearbyBoxesFourByFour();
}

TEST(NeighboursSearchTestSuite, findNearbyBoxesFourByThree)
{
    NeighboursSearchTestSuite::findNearbyBoxesFourByThree();
}

TEST(NeighboursSearchTestSuite, findNearbyBoxesThreeByThree)
{
    NeighboursSearchTestSuite::findNearbyBoxesThreeByThree();
}
