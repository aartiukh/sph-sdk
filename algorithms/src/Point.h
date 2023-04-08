/**
 * @file Point.h
 * @author Anton Artyukh (artyukhanton@gmail.com)
 * @date Created Feb 26, 2017
 **/

#ifndef POINT_H_DE836BDF10964E14A5C9BA80FEDE6734
#define POINT_H_DE836BDF10964E14A5C9BA80FEDE6734

#include "Defines.h"

#include <vector>

namespace SPHSDK
{

/**
 * @brief Point2 class defines point in 2D.
 */
template <typename _Tp> class Point2
{
public:
    typedef _Tp value_type;

    Point2();
    Point2(_Tp _x, _Tp _y);
    Point2(const Point2& pt);

    auto calcNormSqr() const;
    auto calcNorm() const;

    Point2& operator=(const Point2& pt);

    _Tp x, y; //< the point coordinates
};

using Point2F = Point2<FLOAT>;

using Point2FVector = std::vector<Point2F>;

/**
 * @brief Point3 class defines point in 3D.
 */

template <typename _Tp> class Point3
{
public:
    typedef _Tp value_type;

    Point3();
    Point3(_Tp _x, _Tp _y, _Tp _z);
    Point3(const Point3& pt);

    auto calcNormSqr() const;
    auto calcNorm() const;

    Point3& operator=(const Point3& pt);

    _Tp x, y, z; //< the point coordinates
};

using Point3F = Point3<FLOAT>;

using Point3FVector = std::vector<Point3F>;

} // namespace SPHSDK

#include "Point.hpp"

#endif // POINT_H_DE836BDF10964E14A5C9BA80FEDE6734
