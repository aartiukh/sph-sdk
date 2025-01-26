#ifndef NS_GRID_BASED_OLD_TEST_SUITE_H_12192C2023784EE0B4976A48A1A8779B
#define NS_GRID_BASED_OLD_TEST_SUITE_H_12192C2023784EE0B4976A48A1A8779B

#include "Area.h"
#include "Defines.h"
#include "Point.h"

namespace SPHSDK
{

struct Rect;

namespace TestEnvironment
{

class NSGridBasedOldTestSuite
{
public:
    static void searchInOneBox3D();

    static void searchInDifferentBoxesCenterBack3D();

    static void searchInDifferentBoxesCenterMiddle3D();

private:
    struct TestPoint3F
    {
        TestPoint3F(Point3F _position)
            : position(_position)
        {
        }

        Point3F position;

        SizetVector neighbours;
    };

    using TestPoints3D = std::vector<TestPoint3F>;

    static void testSearch(
        const Cuboid&               cuboid,
        FLOAT                       radius,
        FLOAT                       accuracy,
        TestPoints3D&               points,
        const SizetVector&          expectedBoxSizes,
        const VectorOfSizetVectors& expectedBoxNeighbours,
        VectorOfSizetVectors        expectedPointNeighbours);

    static void testInsert(
        const Cuboid&               cuboid,
        FLOAT                       radius,
        FLOAT                       accuracy,
        TestPoints3D&               points,
        const SizetVector&          expectedBoxSizes,
        const VectorOfSizetVectors& expectedPointsInBoxes);
};

} // namespace TestEnvironment
} // namespace SPHSDK

#endif // NS_GRID_BASED_OLD_TEST_SUITE_H_12192C2023784EE0B4976A48A1A8779B
