#ifndef NEIGHBOUR_SEARCH_H_37DCCF3737274ADE9B6EEF8BF6947A6E
#define NEIGHBOUR_SEARCH_H_37DCCF3737274ADE9B6EEF8BF6947A6E

#include "Area.h"
#include "Defines.h"
#include "NeighbourSearchInterface.h"
#include "Point.h"

namespace SPHSDK
{

namespace TestEnvironment
{
class NSGridBasedOldTestSuite;
} // namespace TestEnvironment

template <class T> class NSGridBasedOld : public NeighbourSearchI<T>
{
    friend class TestEnvironment::NSGridBasedOldTestSuite;

public:
    explicit NSGridBasedOld(const Volume& volume, FLOAT radius, FLOAT eps);

    ~NSGridBasedOld();

    void search(T& points);

    enum BoxType
    {
        outerCorner,
        outerLongitual,
        outerCenter,
        innerCorner,
        innerLongitual,
        innerCenter
    };

private:
    void insertPointsIntoBoxes(const T& points);

    void findNearbyBoxes();

    SizetVector getComponentsOfBoxIndex(const size_t boxIndex);

    BoxType getBoxType(const SizetVector& components);

    void defineNearbyBoxes(const BoxType boxType, const SizetVector& components, const size_t boxIndex);

    void addNearbyBoxesFor(
        const bool         isLeft,
        const bool         isRight,
        const bool         isTop,
        const bool         isBottom,
        const SizetVector& components,
        const size_t       boxIndex);

    void addForTopLeft(const SizetVector& components, const size_t boxIndex);
    void addForTopRight(const SizetVector& components, const size_t boxIndex);
    void addForBottomLeft(const SizetVector& components, const size_t boxIndex);
    void addForBottomRight(const SizetVector& components, const size_t boxIndex);

    void addForCenter(const SizetVector& components, const size_t boxIndex);

    void addForLeft(const SizetVector& components, const size_t boxIndex);
    void addForRight(const SizetVector& components, const size_t boxIndex);
    void addForTop(const SizetVector& components, const size_t boxIndex);
    void addForBottom(const SizetVector& components, const size_t boxIndex);

    void addForBack(const size_t boxIndex);
    void addForFront(const size_t boxIndex);
    void addForMiddle(const size_t boxIndex);

private:
    Volume m_volume;

    FLOAT m_radius;

    FLOAT m_eps;

    VectorOfSizetVectors m_boxes;

    VectorOfSizetVectors m_nearbyBoxes;

    size_t m_boxesNumber;

    size_t m_pointsSize; // the amount of points

    Cuboid m_cuboid;

    size_t m_normalizedCuboidWidth;
    size_t m_normalizedCuboidLength;
    size_t m_normalizedCuboidHeight;
};
} // namespace SPHSDK

#include "NSGridBasedOld.hpp"

#endif // NEIGHBOUR_SEARCH_H_37DCCF3737274ADE9B6EEF8BF6947A6E
