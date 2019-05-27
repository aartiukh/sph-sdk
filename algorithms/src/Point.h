/**
* @file Point.h
* @author Anton Artyukh (artyukhanton@gmail.com)
* @date Created Feb 26, 2017
**/

#ifndef POINT_H_DE836BDF10964E14A5C9BA80FEDE6734
#define POINT_H_DE836BDF10964E14A5C9BA80FEDE6734

#include <vector>

namespace SPHAlgorithms
{

/**
* @brief Point2 class defines point in 2D.
*/
template<typename _Tp> class Point2
{
public:
    typedef _Tp value_type;

    Point2();
    Point2(_Tp _x, _Tp _y);
    Point2(const Point2& pt);

    auto calcNormSqr() const;
    auto calcNorm() const;

    Point2& operator = (const Point2& pt);

    _Tp x, y; //< the point coordinates
};

using Point2D = Point2<double>;
using Point2F = Point2<float>;
using Point2I = Point2<int>;

using Point2DVector = std::vector<Point2D>;
using Point2FVector = std::vector<Point2F>;
using Point2IVector = std::vector<Point2I>;

/**
* @brief Point3 class defines point in 3D.
*/

template<typename _Tp> class Point3
{
public:
    typedef _Tp value_type;

    Point3();
    Point3(double _x, double _y, double _z);
	Point3(float _x, float _y, float _z);
    Point3(const Point3& pt);

    auto calcNormSqr() const;
    auto calcNorm() const;

    Point3& operator = (const Point3& pt);

    _Tp x, y, z; //< the point coordinates
};

using Point3D = Point3<double>;
using Point3F = Point3<float>;

using Point3DVector = std::vector<Point3D>;
using Point3FVector = std::vector<Point3F>;

} //SPHAlgorithms

#include "Point.hpp"

#endif // POINT_H_DE836BDF10964E14A5C9BA80FEDE6734
