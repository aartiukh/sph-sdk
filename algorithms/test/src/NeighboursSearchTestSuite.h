/**
* @file NeighboursSearchTestSuite.h
* @NeighboursSearchTestSuite class defines neighbours search test suite
* @author Anton Artyukh (artyukhanton@gmail.com)
* @version 0.1
* @date Created Feb 13, 2017
* @par Anton Artiukh
**/

#ifndef NEIGHBOURS_SEARCH_TEST_SUITE_H_96192C2023784EE0B4976A48A1A8779B
#define NEIGHBOURS_SEARCH_TEST_SUITE_H_96192C2023784EE0B4976A48A1A8779B

#include "Defines.h"
#include "Point.h"
#include "Area.h"

namespace SPHSDK
{

struct Rect;

namespace TestEnvironment
{

class NeighboursSearchTestSuite
{
public:

    /// NeighboursSearch::search() tests

    static void searchInOneBox();

    static void searchInDifferentBoxesRightBottom();

    static void searchInDifferentBoxesLeftBottom();

    static void searchInDifferentBoxesRightTop();

    static void searchInDifferentBoxesLeftTop();

    static void searchInDifferentBoxesRightSide();

    static void searchInDifferentBoxesLeftSide();

    static void searchInDifferentBoxesCenterBottom();

    static void searchInDifferentBoxesCenterTop();

    static void searchInCornerOfBoxesCenter();

    static void searchInCornerOfBoxesCorners();

    //-------------------------------------------------

    static void searchInOneBox3D();

    static void searchInDifferentBoxesCenterBack3D();

    static void searchInDifferentBoxesCenterMiddle3D();

    /// NeighboursSearch::insertPointsIntoBoxes() tests
    static void insertPointsIntoBoxesCornerPoints();

    static void insertPointsIntoBoxesBorderPoints();

    static void insertPointsIntoBoxesInnerPoints();

    static void insertPointsIntoBoxesCenterBoxFrame();

    static void insertPointsIntoBoxesInnerFrame();

    static void insertPointsIntoBoxesTopRightBox();

    static void insertPointsIntoBoxesTopLeftBox();

    static void insertPointsIntoBoxesBottomLeftBox();

    static void insertPointsIntoBoxesBottomRightBox();

    static void insertPointsIntoBoxesBottomCenterBox();

    static void insertPointsIntoBoxesLeftCenterBox();

    static void insertPointsIntoBoxesTopCenterBox();

    static void insertPointsIntoBoxesRightCenterBox();

    static void insertPointsIntoBoxesBottomLineBox();

    static void insertPointsIntoBoxesLeftLineBox();

    static void insertPointsIntoBoxesTopLineBox();

    static void insertPointsIntoBoxesRightLineBox();

    static void insertPointsIntoBoxes3x2();

    static void insertPointsIntoBoxes4x2();

    static void insertPointsIntoBoxes2x4();

    static void insertPointsIntoBoxes8x3();

    static void insertPointsIntoBoxes9x6();

    /// NeighboursSearch::findNearByBoxes() tests
    static void findNearbyBoxesTwoByTwo();

    static void findNearbyBoxesFourByTwo();

    static void findNearbyBoxesFourByFour();

    static void findNearbyBoxesFourByThree();

    static void findNearbyBoxesThreeByThree();

private:

    struct TestPoint
    {
        TestPoint(Point2F _position) : position(_position) {}

        Point2F position;

        SizetVector neighbours;
    };

    struct TestPoint3F
    {
        TestPoint3F(Point3F _position) : position(_position) {}

        Point3F position;

        SizetVector neighbours;
    };

    using TestPoints = std::vector<TestPoint>;
    using TestPoints3D = std::vector<TestPoint3F>;

    static void testSearch(/*in*/ const Rect& areaRect,
                           /*in*/ FLOAT radius,
                           /*in*/ FLOAT accuracy,
                           /*in*/ TestPoints &points,
                           /*in*/ const SizetVector& expectedBoxSizes,
                           /*in*/ const VectorOfSizetVectors& expectedNeighbours);

    static void testInsert(/*in*/ const Rect& areaRect,
                           /*in*/ FLOAT radius,
                           /*in*/ FLOAT accuracy,
                           /*in*/ TestPoints& points,
                           /*in*/ const SizetVector& expectedBoxSizes,
                           /*in*/ const VectorOfSizetVectors& expectedPointsInBoxes);

    static void testSearch3D(const Cuboid&               cuboid,
                           FLOAT                      radius,
                           FLOAT                      accuracy,
                           TestPoints3D&               points,
                           const SizetVector&          expectedBoxSizes,
                           const VectorOfSizetVectors& expectedBoxNeighbours,
                           const VectorOfSizetVectors& expectedPointNeighbours);

    static void testInsert3D(const Cuboid&               cuboid,
                           FLOAT                      radius,
                           FLOAT                      accuracy,
                           TestPoints3D&               points,
                           const SizetVector&          expectedBoxSizes,
                           const VectorOfSizetVectors& expectedPointsInBoxes);

};

} // namespace TestEnvironment
} // namespace SPHSDK

#endif // NEIGHBOURS_SEARCH_TEST_SUITE_H_96192C2023784EE0B4976A48A1A8779B
