/**
* @file NeighboursSearch.h
* @author Anton Artyukh (artyukhanton@gmail.com)
* @date Created Feb 13, 2017
**/

#ifndef NEIGHBOURS_SEARCH_H_37DCCF3737274ADE9B6EEF8BF6947A6E
#define NEIGHBOURS_SEARCH_H_37DCCF3737274ADE9B6EEF8BF6947A6E

#include "Point.h"
#include "Defines.h"
#include "Area.h"

namespace SPHAlgorithms
{

namespace TestEnvironment
{
    class NeighboursSearchTestSuite;
} //TestEnvironment

/**
* @brief NeighboursSearch class defines neighbours search function.
* Search method based on region decomposition by boxes
* which have equal size equals to search radius
* Search function finds vector of the same length as input points array
* with indexes of neighbours for each input object.
*/

template <class T>
class NeighboursSearch
{
    friend class TestEnvironment::NeighboursSearchTestSuite;

public:

    explicit NeighboursSearch(const Area& area, double radius, double eps);

    ~NeighboursSearch();

    void search(T& points);

private:

    void insertPointsIntoBoxes(const T& points);

    void findNearbyBoxes();

private:

    Area m_Area;

    double m_radius;

    double m_eps;

    VectorOfSizetVectors m_boxes;

    VectorOfSizetVectors m_nearbyBoxes;

    size_t m_boxesNumber;

    size_t m_pointsSize; // the amount of points

    double m_rectWidth;

    double m_rectHeight;
};

// ---------------------------

template <class T> class NeighboursSearch3D
{
    friend class TestEnvironment::NeighboursSearchTestSuite;
    
public:

    explicit NeighboursSearch3D(const Volume& volume, double radius, double eps);

    ~NeighboursSearch3D();

    void search(T& points);

    enum BoxType { outerCorner, outerLongitual, outerCenter,
                   innerCorner, innerLongitual, innerCenter };

private:

    void insertPointsIntoBoxes(const T& points);

    void findNearbyBoxes();

    SizetVector getComponentsOfBoxIndex(const size_t boxIndex);

    BoxType getBoxType(const SizetVector& components);

    void defineNearbyBoxes(const BoxType boxType,
                           const SizetVector& components,
                           const size_t boxIndex);

    void addNearbyBoxesFor(const bool isLeft,
                           const bool isRight,
                           const bool isTop,
                           const bool isBottom,
                           const SizetVector& components,
                           const size_t boxIndex);

    void addForTopLeft(const SizetVector& components,
                       const size_t boxIndex);
    void addForTopRight(const SizetVector& components,
                        const size_t boxIndex);
    void addForBottomLeft(const SizetVector& components,
                          const size_t boxIndex);
    void addForBottomRight(const SizetVector& components,
                           const size_t boxIndex);

    void addForCenter(const SizetVector& components,
                      const size_t boxIndex);

    void addForLeft(const SizetVector& components,
                    const size_t boxIndex);
    void addForRight(const SizetVector& components,
                     const size_t boxIndex);
    void addForTop(const SizetVector& components,
                   const size_t boxIndex);
    void addForBottom(const SizetVector& components,
                      const size_t boxIndex);

    void addForBack(const size_t boxIndex);
    void addForFront(const size_t boxIndex);
    void addForMiddle(const size_t boxIndex);

private:

    Volume m_volume;

    double m_radius;

    double m_eps;

    VectorOfSizetVectors m_boxes;

    VectorOfSizetVectors m_nearbyBoxes;

    size_t m_boxesNumber;

    size_t m_pointsSize; // the amount of points

    Cuboid m_cuboid;
};
} //SPHAlgorithms

#include "NeighboursSearch.hpp"

#endif // NEIGHBOURS_SEARCH_H_37DCCF3737274ADE9B6EEF8BF6947A6E
