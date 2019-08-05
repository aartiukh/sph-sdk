/**
 * @file NeighboursSearch.hpp
 * @NeighboursSearch class defines neighbours search function
 * @author Anton Artyukh (artyukhanton@gmail.com)
 * @version 0.1
 * @date Created Feb 13, 2017
 * @par Anton Artiukh
 **/

#include "NeighboursSearch.h"

#include <cfloat>
#include <cmath>

namespace SPHAlgorithms
{

template <class T>
NeighboursSearch<T>::NeighboursSearch(const Area& area, double radius, double eps)
    : m_Area(area)
    , m_radius(radius)
    , m_eps(eps)
    , m_boxes(VectorOfSizetVectors())
{
    const Rect rect = m_Area.getBoundingRect();

    m_rectWidth = rect.rightBottom.x - rect.leftTop.x;
    m_rectHeight = rect.rightBottom.y - rect.leftTop.y;

    try
    {
        m_boxesNumber = static_cast<size_t>(m_rectWidth * m_rectHeight / (m_radius * m_radius));
        m_boxes.resize(m_boxesNumber);
        m_nearbyBoxes.resize(m_boxesNumber);
    }
    catch (...)
    {
        throw;
    }

    findNearbyBoxes();
}

template <class T> NeighboursSearch<T>::~NeighboursSearch() = default;

template <class T> void NeighboursSearch<T>::search(T& points)
{
    for (size_t i = 0; i < points.size(); i++)
    {
        points[i].neighbours.clear();
    }

    //  1) puts every point from vector of points into the right box

    insertPointsIntoBoxes(points);

    //  2) search

    // a) get the next point from box
    // b) get array of boxes for current box
    // c) check the distance between current point and points from boxes in array + current box
    // d) write 'OK' points to output array, back to a)
    // search inside one box
    for (size_t i = 0; i < m_boxes.size(); i++)
    {
        for (size_t j = 0; j < m_boxes[i].size(); j++)
        {
            for (size_t k = 0; k < m_boxes[i].size(); k++)
            {
                if (j != k)
                {
                    double distanceSqr = pow(points[m_boxes[i][j]].position.x - points[m_boxes[i][k]].position.x, 2) +
                                         pow(points[m_boxes[i][j]].position.y - points[m_boxes[i][k]].position.y, 2);
                    if (distanceSqr <= pow(m_radius, 2))
                        points[m_boxes[i][j]].neighbours.push_back(m_boxes[i][k]);
                }
            }
        }
    }

    // search through the neighbours boxes
    for (size_t i = 0; i < m_boxes.size(); i++)
    {
        for (size_t j = 0; j < m_boxes[i].size(); j++)
        {
            for (size_t k = 0; k < m_nearbyBoxes[i].size(); k++)
            {
                for (size_t q = 0; q < m_boxes[m_nearbyBoxes[i][k]].size(); q++)
                {
                    double distanceSqr =
                        pow(points[m_boxes[i][j]].position.x - points[m_boxes[m_nearbyBoxes[i][k]][q]].position.x, 2) +
                        pow(points[m_boxes[i][j]].position.y - points[m_boxes[m_nearbyBoxes[i][k]][q]].position.y, 2);
                    if (distanceSqr - pow(m_radius, 2) <= DBL_EPSILON)
                        points[m_boxes[i][j]].neighbours.push_back(m_boxes[m_nearbyBoxes[i][k]][q]);
                }
            }
        }
    }
}

template <class T> void NeighboursSearch<T>::insertPointsIntoBoxes(const T& points)
{
    for (size_t i = 0; i < m_boxesNumber; i++) {
        m_boxes[i].clear();
    }

    m_pointsSize = points.size();

    for (size_t i = 0; i < m_pointsSize; i++)
    {
        size_t j = static_cast<size_t>(points[i].position.x / m_radius) +
                   static_cast<size_t>(points[i].position.y / m_radius) *
                   static_cast<size_t>(m_rectWidth / m_radius);

        if (std::abs(points[i].position.x - m_rectWidth) < m_eps)
            --j;

        if (std::abs(points[i].position.y - m_rectHeight) < m_eps)
            j -= static_cast<size_t>(m_rectWidth / m_radius);

        m_boxes[j].push_back(i);
    }
}

template <class T> void NeighboursSearch<T>::findNearbyBoxes()
{
    size_t eqvW = static_cast<size_t>(m_rectWidth / m_radius);
    size_t eqvH = static_cast<size_t>(m_rectHeight / m_radius);

    bool top = false;
    bool left = false;
    bool right = false;
    bool bottom = false;
    bool middle = false;

    for (size_t i = 0; i < m_boxes.size(); i++)
    {
        // bottom
        if (i >= eqvW)
        {
            m_nearbyBoxes[i].push_back(i - eqvW);
            bottom = true;
        }

        // top
        if (i < eqvW * eqvH - eqvW)
        {
            m_nearbyBoxes[i].push_back(i + eqvW);
            top = true;
        }

        // left
        if (i % eqvW != 0)
        {
            m_nearbyBoxes[i].push_back(i - 1);
            left = true;
        }

        // right
        if ((i + 1) % eqvW != 0)
        {
            m_nearbyBoxes[i].push_back(i + 1);
            right = true;
        }

        // all corners
        if (bottom && top && left && right)
        {
            m_nearbyBoxes[i].push_back(i - 1 - eqvW);
            m_nearbyBoxes[i].push_back(i - 1 + eqvW);
            m_nearbyBoxes[i].push_back(i + 1 - eqvW);
            m_nearbyBoxes[i].push_back(i + 1 + eqvW);
            middle = true;
        }

        if (!middle)
        {
            if (bottom && left)
            {
                m_nearbyBoxes[i].push_back(i - 1 - eqvW);
            }

            if (bottom && right)
            {
                m_nearbyBoxes[i].push_back(i + 1 - eqvW);
            }

            if (top && left)
            {
                m_nearbyBoxes[i].push_back(i - 1 + eqvW);
            }

            if (top && right)
            {
                m_nearbyBoxes[i].push_back(i + 1 + eqvW);
            }
        }

        top = false;
        left = false;
        right = false;
        bottom = false;
        middle = false;
    }
}

// ---------------------------

static size_t normalizedCuboidWidth;
static size_t normalizedCuboidLength;
static size_t normalizedCuboidHeight;

template <class T>
NeighboursSearch3D<T>::NeighboursSearch3D(const Volume& volume, double radius, double eps)
    : m_volume(volume)
    , m_radius(radius)
    , m_eps(eps)
    , m_boxes(VectorOfSizetVectors())
    {
        const Cuboid cuboid = m_volume.getBoundingCuboid();

        m_cuboid = cuboid;

        normalizedCuboidWidth = static_cast<size_t>(m_cuboid.width / m_radius);
        normalizedCuboidLength = static_cast<size_t>(m_cuboid.length / m_radius);
        normalizedCuboidHeight = static_cast<size_t>(m_cuboid.height / m_radius);

        m_boxesNumber = static_cast<size_t>(normalizedCuboidWidth *
                                            normalizedCuboidLength *
                                            normalizedCuboidHeight);
        m_boxes.resize(m_boxesNumber);
        m_nearbyBoxes.resize(m_boxesNumber);

        findNearbyBoxes();
    }

template <class T> NeighboursSearch3D<T>::~NeighboursSearch3D() = default;

/**
 * @brief The main method of search.
 * 1. Clear all neighbours;
 * 2. Put every point in box;
 * 3. Look for neighbour points for every point in every box;
 * 4. Look for neighbour points for every point in neighbour boxes;
 */
template <class T> void NeighboursSearch3D<T>::search(T& points)
{
    // 1
    for (size_t i = 0; i < points.size(); i++)
        points[i].neighbours.clear();
    // 2
    insertPointsIntoBoxes(points);
    // 3
    for (size_t boxIndex = 0; boxIndex < m_boxes.size(); boxIndex++)
        for (size_t pointIndex = 0; pointIndex < m_boxes[boxIndex].size(); pointIndex++)
            for (size_t nearbyPointIndex = 0; nearbyPointIndex < m_boxes[boxIndex].size(); nearbyPointIndex++)
                if (pointIndex != nearbyPointIndex)
                {
                    Point3D difference = points[m_boxes[boxIndex][pointIndex]].position -
                                         points[m_boxes[boxIndex][nearbyPointIndex]].position;
                    if (difference.calcNormSqr() <= pow(m_radius, 2))
                        points[m_boxes[boxIndex][pointIndex]].neighbours.push_back(m_boxes[boxIndex][nearbyPointIndex]);
                }
    // 4
    for (size_t boxIndex = 0; boxIndex < m_boxes.size(); boxIndex++)
        for (size_t pointIndex = 0; pointIndex < m_boxes[boxIndex].size(); pointIndex++)
            for (size_t nearbyBoxIndex = 0; nearbyBoxIndex < m_nearbyBoxes[boxIndex].size(); nearbyBoxIndex++)
                for (size_t nearbyPointIndex = 0; nearbyPointIndex < m_boxes[m_nearbyBoxes[boxIndex][nearbyBoxIndex]].size(); nearbyPointIndex++)
                {
                    Point3D difference = points[m_boxes[boxIndex][pointIndex]].position -
                                         points[m_boxes[m_nearbyBoxes[boxIndex][nearbyBoxIndex]][nearbyPointIndex]].position;
                    if (difference.calcNormSqr() - pow(m_radius, 2) <= DBL_EPSILON)
                        points[m_boxes[boxIndex][pointIndex]]
                            .neighbours
                            .push_back(m_boxes[m_nearbyBoxes[boxIndex][nearbyBoxIndex]][nearbyPointIndex]);
                }
}

/**
 * @brief The main idea of numbering is to use height layers.
 * The x-axis is equal to width.
 * The y-axis is equal to length.
 * The z-axis is equal to height.
 *
 * An example of numbering 9x9x9 cuboid with radius 3:
 * ╔════╤════╤════╗     ╔════╤════╤════╗     ╔════╤════╤════╗
 * ║ 18 │ 19 │ 20 ║     ║ 21 │ 22 │ 23 ║     ║ 24 │ 25 │ 26 ║
 * ║  9 │ 10 │ 11 ║     ║ 12 │ 13 │ 14 ║     ║ 15 │ 16 │ 17 ║
 * ║  0 │  1 │  2 ║     ║  3 │  4 │  5 ║     ║  6 │  7 │  8 ║
 * ╚════╧════╧════╝     ╚════╧════╧════╝     ╚════╧════╧════╝
 *
 *     Length 0             Length 1             Length 2
 */
template <class T> void NeighboursSearch3D<T>::insertPointsIntoBoxes(const T& points)
{
    for (size_t i = 0; i < m_boxesNumber; i++)
        m_boxes[i].clear();

    m_pointsSize = points.size();

    for (size_t i = 0; i < m_pointsSize; i++)
    {
        // The Formula is created manually using height layers approach

        size_t widthOffset = static_cast<size_t>(points[i].position.x / m_radius);
        size_t lengthOffset = static_cast<size_t>(points[i].position.y / m_radius) *
                              normalizedCuboidWidth;
        size_t heightOffset = static_cast<size_t>(points[i].position.z / m_radius) *
                              normalizedCuboidLength * normalizedCuboidWidth;

        if (std::abs(points[i].position.x - m_cuboid.width) < m_eps)
            widthOffset -= 1;

        if (std::abs(points[i].position.y - m_cuboid.length) < m_eps)
            lengthOffset -= normalizedCuboidLength;

        if (std::abs(points[i].position.z - m_cuboid.height) < m_eps)
            heightOffset -= normalizedCuboidLength * normalizedCuboidWidth;

        size_t boxIndex = widthOffset + lengthOffset + heightOffset;

        m_boxes[boxIndex].push_back(i);
    }
}

/**
 * @brief This method classifies boxes by types and fills nearby boxes for every box.
 * There are two types of layers: outer and inner;
 * And three types of boxes for every layer: corner, longitual and center.
 *
 * Considering this, there are six types of boxes with fixed amout of neighbours:
 * - outer-corner: 7;
 * - outer-longitual: 11;
 * - outer-center: 17;
 * - inner-corner: 11;
 * - inner-longitual: 17;
 * - inner-center: 26.
 *
 * An example of neighbours amount in 9x9x9 cuboid with radius 3:
 * ╔════╤════╤════╗     ╔════╤════╤════╗     ╔════╤════╤════╗
 * ║  7 │ 11 │  7 ║     ║ 11 │ 17 │ 11 ║     ║  7 │ 11 │  7 ║
 * ║ 11 │ 17 │ 11 ║     ║ 17 │ 26 │ 17 ║     ║ 11 │ 17 │ 11 ║
 * ║  7 │ 11 │  7 ║     ║ 11 │ 17 │ 11 ║     ║  7 │ 11 │  7 ║
 * ╚════╧════╧════╝     ╚════╧════╧════╝     ╚════╧════╧════╝
 *
 *     Length 0             Length 1             Length 2
 */

template <class T> void NeighboursSearch3D<T>::findNearbyBoxes()
{
    for (size_t boxIndex = 0; boxIndex < m_boxes.size(); boxIndex++)
    {
        const SizetVector boxComponents = getComponentsOfBoxIndex(boxIndex);
        BoxType boxType = getBoxType(boxComponents);
        defineNearbyBoxes(boxType, boxComponents, boxIndex);
    }
}

/**
 * @brief This method returns array of components (width, length and height) for box index.
 */

template <class T> SizetVector NeighboursSearch3D<T>::getComponentsOfBoxIndex(const size_t boxIndex)
{
    size_t boxWidth = boxIndex % normalizedCuboidWidth;
    size_t boxHeight = (boxIndex - boxWidth) / (normalizedCuboidWidth * normalizedCuboidLength);
    size_t boxLength = (boxIndex - boxWidth -
                        boxHeight * normalizedCuboidWidth * normalizedCuboidLength) / normalizedCuboidWidth;

    SizetVector components = {boxWidth, boxLength, boxHeight};

    return components;
}

/**
 * @brief This method returns type of box (one of six), using its components (width, length and height).
 */

template <class T> typename NeighboursSearch3D<T>::BoxType NeighboursSearch3D<T>::getBoxType(const SizetVector& components)
{
    if ((components[0] == 0 || components[0] == normalizedCuboidWidth - 1) &&
        (components[1] == 0 || components[1] == normalizedCuboidLength - 1) &&
        (components[2] == 0 || components[2] == normalizedCuboidHeight - 1))
    {
        return outerCorner;
    }

    if ((components[0] != 0 && components[0] != normalizedCuboidWidth - 1) &&
        (components[1] == 0 || components[1] == normalizedCuboidLength - 1) &&
        (components[2] != 0 && components[2] != normalizedCuboidHeight - 1))
    {
        return outerCenter;
    }

    if ((components[1] == 0 || components[1] == normalizedCuboidLength - 1) &&
        (
         ((components[0] != 0 && components[0] != normalizedCuboidWidth - 1) &&
          (components[2] == 0 || components[2] == normalizedCuboidHeight - 1)) ||
         ((components[0] == 0 || components[0] == normalizedCuboidWidth - 1) &&
          (components[2] != 0 && components[2] != normalizedCuboidHeight - 1))
         )
        )
    {
        return outerLongitual;
    }

    if ((components[0] == 0 || components[0] == normalizedCuboidWidth - 1) &&
        (components[1] != 0 && components[1] != normalizedCuboidLength - 1) &&
        (components[2] == 0 || components[2] == normalizedCuboidHeight - 1))
    {
        return innerCorner;
    }

    if ((components[0] != 0 && components[0] != normalizedCuboidWidth - 1) &&
        (components[1] != 0 && components[1] != normalizedCuboidLength - 1) &&
        (components[2] != 0 && components[2] != normalizedCuboidHeight - 1))
    {
        return innerCenter;
    }

    if ((components[1] != 0 && components[1] != normalizedCuboidLength - 1) &&
        (
         ((components[0] != 0 && components[0] != normalizedCuboidWidth - 1) &&
          (components[2] == 0 || components[2] == normalizedCuboidHeight - 1)) ||
         ((components[0] == 0 || components[0] == normalizedCuboidWidth - 1) &&
          (components[2] != 0 && components[2] != normalizedCuboidHeight - 1))
         )
        )
    {
        return innerLongitual;
    }

	return innerLongitual;
}

/**
 * @brief This method defines for box its neighbours, using box conmonents and type.
 */

template <class T> void NeighboursSearch3D<T>::defineNearbyBoxes(const NeighboursSearch3D<T>::BoxType boxType,
                                                                 const SizetVector& components,
                                                                 const size_t boxIndex)
{
    bool isLeft     = components[0] == 0;
    bool isRight    = components[0] == normalizedCuboidWidth - 1;
    bool isBack     = components[1] == 0;
//  bool isFront    = components[1] == normalizedCuboidLength - 1; // commented as not used
    bool isBottom   = components[2] == 0;
    bool isTop      = components[2] == normalizedCuboidHeight - 1;

    switch (boxType) {
        case outerCorner:
            addNearbyBoxesFor(isLeft, isRight, isTop, isBottom, components, boxIndex);
            isBack ? addForBack(boxIndex) : addForFront(boxIndex);

            break;

        case outerCenter:
            addForCenter(components, boxIndex);
            isBack ? addForBack(boxIndex) : addForFront(boxIndex);

            break;

        case outerLongitual:
            addNearbyBoxesFor(isLeft, isRight, isTop, isBottom, components, boxIndex);
            isBack ? addForBack(boxIndex) : addForFront(boxIndex);

            break;

        case innerCorner:
            addNearbyBoxesFor(isLeft, isRight, isTop, isBottom, components, boxIndex);
            addForMiddle(boxIndex);

            break;

        case innerCenter:
            addForCenter(components, boxIndex);
            addForMiddle(boxIndex);

            break;

        case innerLongitual:
            addNearbyBoxesFor(isLeft, isRight, isTop, isBottom, components, boxIndex);
            addForMiddle(boxIndex);

            break;
    }
}

template <class T> void NeighboursSearch3D<T>:: addNearbyBoxesFor(const bool isLeft,
                                                                  const bool isRight,
                                                                  const bool isTop,
                                                                  const bool isBottom,
                                                                  const SizetVector& components,
                                                                  const size_t boxIndex)
{
    if (isLeft && isBottom) {
        addForBottomLeft(components, boxIndex);
        return;
    }

    if (isRight && isBottom) {
        addForBottomRight(components, boxIndex);
        return;
    }

    if (isLeft && isTop) {
        addForTopLeft(components, boxIndex);
        return;
    }

    if (isRight && isTop) {
        addForTopRight(components, boxIndex);
        return;
    }

    if (isLeft) {
        addForLeft(components, boxIndex);
        return;
    }

    if (isRight) {
        addForRight(components, boxIndex);
        return;
    }

    if (isBottom) {
        addForBottom(components, boxIndex);
        return;
    }

    if (isTop) {
        addForTop(components, boxIndex);
        return;
    }
}

template <class T> void NeighboursSearch3D<T>:: addForTopLeft(const SizetVector& /*components*/,
                                                              const size_t boxIndex)
{
    // addRight
    m_nearbyBoxes[boxIndex].push_back(boxIndex + 1);
    // addBotom
    m_nearbyBoxes[boxIndex].push_back(boxIndex - normalizedCuboidWidth * normalizedCuboidLength);
    // addBottomRight
    m_nearbyBoxes[boxIndex].push_back(boxIndex - normalizedCuboidWidth * normalizedCuboidLength + 1);
}

template <class T> void NeighboursSearch3D<T>:: addForTopRight(const SizetVector& /*components*/,
                                                               const size_t boxIndex)
{
    // addLeft
    m_nearbyBoxes[boxIndex].push_back(boxIndex - 1);
    // addBotom
    m_nearbyBoxes[boxIndex].push_back(boxIndex - normalizedCuboidWidth * normalizedCuboidLength);
    // addBottomLeft
    m_nearbyBoxes[boxIndex].push_back(boxIndex - normalizedCuboidWidth * normalizedCuboidLength - 1);
}

template <class T> void NeighboursSearch3D<T>:: addForBottomLeft(const SizetVector& /*components*/,
                                                                 const size_t boxIndex)
{
    // addRight
    m_nearbyBoxes[boxIndex].push_back(boxIndex + 1);
    // addTop
    m_nearbyBoxes[boxIndex].push_back(boxIndex + normalizedCuboidWidth * normalizedCuboidLength);
    // addTopRight
    m_nearbyBoxes[boxIndex].push_back(boxIndex + normalizedCuboidWidth * normalizedCuboidLength + 1);
}

template <class T> void NeighboursSearch3D<T>:: addForBottomRight(const SizetVector& /*components*/,
                                                                  const size_t boxIndex)
{
    // addLeft
    m_nearbyBoxes[boxIndex].push_back(boxIndex - 1);
    // addTop
    m_nearbyBoxes[boxIndex].push_back(boxIndex + normalizedCuboidWidth * normalizedCuboidLength);
    // addTopLeft
    m_nearbyBoxes[boxIndex].push_back(boxIndex + normalizedCuboidWidth * normalizedCuboidLength - 1);
}

template <class T> void NeighboursSearch3D<T>:: addForCenter(const SizetVector& /*components*/,
                                                             const size_t boxIndex)
{
    // addRight
    m_nearbyBoxes[boxIndex].push_back(boxIndex + 1);
    // addLeft
    m_nearbyBoxes[boxIndex].push_back(boxIndex - 1);
    // addTop
    m_nearbyBoxes[boxIndex].push_back(boxIndex + normalizedCuboidWidth * normalizedCuboidLength);
    // addBottom
    m_nearbyBoxes[boxIndex].push_back(boxIndex - normalizedCuboidWidth * normalizedCuboidLength);
    // addTopRight
    m_nearbyBoxes[boxIndex].push_back(boxIndex + normalizedCuboidWidth * normalizedCuboidLength + 1);
    // addTopLeft
    m_nearbyBoxes[boxIndex].push_back(boxIndex + normalizedCuboidWidth * normalizedCuboidLength - 1);
    // addBottomRight
    m_nearbyBoxes[boxIndex].push_back(boxIndex - normalizedCuboidWidth * normalizedCuboidLength + 1);
    // addBottomLeft
    m_nearbyBoxes[boxIndex].push_back(boxIndex - normalizedCuboidWidth * normalizedCuboidLength - 1);
}

template <class T> void NeighboursSearch3D<T>:: addForLeft(const SizetVector& /*components*/,
                                                           const size_t boxIndex)
{
    // addRight
    m_nearbyBoxes[boxIndex].push_back(boxIndex + 1);
    // addTop
    m_nearbyBoxes[boxIndex].push_back(boxIndex + normalizedCuboidWidth * normalizedCuboidLength);
    // addBottom
    m_nearbyBoxes[boxIndex].push_back(boxIndex - normalizedCuboidWidth * normalizedCuboidLength);
    // addTopRight
    m_nearbyBoxes[boxIndex].push_back(boxIndex + normalizedCuboidWidth * normalizedCuboidLength + 1);
    // addBottomRight
    m_nearbyBoxes[boxIndex].push_back(boxIndex - normalizedCuboidWidth * normalizedCuboidLength + 1);
}

template <class T> void NeighboursSearch3D<T>:: addForRight(const SizetVector& /*components*/,
                                                            const size_t boxIndex)
{
    // addLeft
    m_nearbyBoxes[boxIndex].push_back(boxIndex - 1);
    // addTop
    m_nearbyBoxes[boxIndex].push_back(boxIndex + normalizedCuboidWidth * normalizedCuboidLength);
    // addBottom
    m_nearbyBoxes[boxIndex].push_back(boxIndex - normalizedCuboidWidth * normalizedCuboidLength);
    // addTopLeft
    m_nearbyBoxes[boxIndex].push_back(boxIndex + normalizedCuboidWidth * normalizedCuboidLength - 1);
    // addBottomLeft
    m_nearbyBoxes[boxIndex].push_back(boxIndex - normalizedCuboidWidth * normalizedCuboidLength - 1);
}

template <class T> void NeighboursSearch3D<T>:: addForTop(const SizetVector& /*components*/,
                                                          const size_t boxIndex)
{
    // addRight
    m_nearbyBoxes[boxIndex].push_back(boxIndex + 1);
    // addLeft
    m_nearbyBoxes[boxIndex].push_back(boxIndex - 1);
    // addBottom
    m_nearbyBoxes[boxIndex].push_back(boxIndex - normalizedCuboidWidth * normalizedCuboidLength);
    // addBottomRight
    m_nearbyBoxes[boxIndex].push_back(boxIndex - normalizedCuboidWidth * normalizedCuboidLength + 1);
    // addBottomLeft
    m_nearbyBoxes[boxIndex].push_back(boxIndex - normalizedCuboidWidth * normalizedCuboidLength - 1);
}

template <class T> void NeighboursSearch3D<T>:: addForBottom(const SizetVector& /*components*/,
                                                             const size_t boxIndex)
{
    // addRight
    m_nearbyBoxes[boxIndex].push_back(boxIndex + 1);
    // addLeft
    m_nearbyBoxes[boxIndex].push_back(boxIndex - 1);
    // addTop
    m_nearbyBoxes[boxIndex].push_back(boxIndex + normalizedCuboidWidth * normalizedCuboidLength);
    // addTopRight
    m_nearbyBoxes[boxIndex].push_back(boxIndex + normalizedCuboidWidth * normalizedCuboidLength + 1);
    // addTopLeft
    m_nearbyBoxes[boxIndex].push_back(boxIndex + normalizedCuboidWidth * normalizedCuboidLength - 1);
}

template <class T> void NeighboursSearch3D<T>:: addForBack(const size_t boxIndex)
{
    SizetVector nearbyBoxes = m_nearbyBoxes[boxIndex];
    nearbyBoxes.push_back(boxIndex);

    for (size_t i = 0u; i < nearbyBoxes.size(); i++) {
        nearbyBoxes[i] += normalizedCuboidWidth;
        m_nearbyBoxes[boxIndex].push_back(nearbyBoxes[i]);
    }
}

template <class T> void NeighboursSearch3D<T>:: addForFront(const size_t boxIndex)
{
    SizetVector nearbyBoxes = m_nearbyBoxes[boxIndex];
    nearbyBoxes.push_back(boxIndex);

    for (size_t i = 0u; i < nearbyBoxes.size(); i++) {
        nearbyBoxes[i] -= normalizedCuboidWidth;
        m_nearbyBoxes[boxIndex].push_back(nearbyBoxes[i]);
    }
}

template <class T> void NeighboursSearch3D<T>:: addForMiddle(const size_t boxIndex)
{
    // TODO: Debug
    SizetVector nearbyBoxes = m_nearbyBoxes[boxIndex];
    nearbyBoxes.push_back(boxIndex);

    addForBack(boxIndex);

    for (size_t i = 0u; i < nearbyBoxes.size(); i++) {
        nearbyBoxes[i] -= normalizedCuboidWidth;
        m_nearbyBoxes[boxIndex].push_back(nearbyBoxes[i]);
    }
}

} // namespace SPHAlgorithms
