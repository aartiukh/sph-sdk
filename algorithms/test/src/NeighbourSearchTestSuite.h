#ifndef NEIGHBOUR_SEARCH_TEST_SUITE_H_96192C2023784EE0B4976A48A1A8779B
#define NEIGHBOUR_SEARCH_TEST_SUITE_H_96192C2023784EE0B4976A48A1A8779B

#include "Area.h"
#include "Defines.h"
#include "Point.h"

namespace SPHSDK
{

struct Rect;

namespace TestEnvironment
{

class NeighbourSearchTestSuite
{
public:
    static void searchAllPointsAreNeighbours();

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
        const Cuboid&        cuboid,
        FLOAT                radius,
        FLOAT                accuracy,
        TestPoints3D&        points,
        VectorOfSizetVectors expectedNeighbours);
};

} // namespace TestEnvironment
} // namespace SPHSDK

#endif // NEIGHBOUR_SEARCH_TEST_SUITE_H_96192C2023784EE0B4976A48A1A8779B
