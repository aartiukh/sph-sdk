/**
* @file Point.hpp
* @author Anton Artyukh (artyukhanton@gmail.com)
* @date Created Feb 26, 2017
**/

#ifndef POINT_HPP_FCE0209B335F4EBB846046447678D096
#define POINT_HPP_FCE0209B335F4EBB846046447678D096

#include "Point.h"
#include <cmath>

namespace SPHAlgorithms
{

template<typename _Tp> inline
    Point2<_Tp>::Point2()
    : x(0),
      y(0) {}

template<typename _Tp> inline
    Point2<_Tp>::Point2(_Tp _x, _Tp _y)
    : x(_x),
      y(_y) {}

template<typename _Tp> inline
    Point2<_Tp>::Point2(const Point2& pt)
    : x(pt.x),
      y(pt.y) {}

template<typename _Tp>
inline auto Point2<_Tp>::calcNormSqr() const
{
    return x * x + y * y;
}

template<typename _Tp>
inline auto Point2<_Tp>::calcNorm() const
{
    return std::sqrt(x * x + y * y);
}

template<typename _Tp> inline
    Point2<_Tp>& Point2<_Tp>::operator = (const Point2& pt)
{
    x = pt.x;
    y = pt.y;

    return *this;
}

template<typename _Tp> static inline
    bool operator == (const Point2<_Tp>& a, const Point2<_Tp>& b)
{
    return a.x == b.x && a.y == b.y;
}

template<typename _Tp> static inline
    bool operator != (const Point2<_Tp>& a, const Point2<_Tp>& b)
{
    return a.x != b.x || a.y != b.y;
}

template<typename _Tp> static inline
    Point2<_Tp> operator *= (Point2<_Tp>& a, const double b)
{
    a.x *= b;
    a.y *= b;
    return a;
}

template<typename _Tp> static inline
    Point2<_Tp> operator += (Point2<_Tp>& a, const Point2<_Tp>& b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

template<typename _Tp> static inline
    Point2<_Tp> operator + (const Point2<_Tp>& a, const Point2<_Tp>& b)
{
    return Point2<_Tp>(static_cast<_Tp>(a.x + b.x), static_cast<_Tp>(a.y + b.y));
}

template<typename _Tp> static inline
    Point2<_Tp> operator - (const Point2<_Tp>& a, const Point2<_Tp>& b)
{
    return Point2<_Tp>(static_cast<_Tp>(a.x - b.x), static_cast<_Tp>(a.y - b.y));
}

template<typename _Tp> static inline
    Point2<_Tp> operator - (const Point2<_Tp>& a)
{
    return Point2<_Tp>(static_cast<_Tp>(-a.x), static_cast<_Tp>(-a.y));
}

template<typename _Tp> static inline
    Point2<_Tp> operator / (const Point2<_Tp>& a, const double b)
{
    return Point2<_Tp>(static_cast<_Tp>(a.x / b), static_cast<_Tp>(a.y / b));
}

template<typename _Tp> static inline
    Point2<_Tp> operator * (const Point2<_Tp>& a, const double b)
{
    return Point2<_Tp>(static_cast<_Tp>(a.x * b), static_cast<_Tp>(a.y * b));
}

// ---------------------------

template<typename _Tp> inline Point3<_Tp>::Point3()
    : x(0),
      y(0),
      z(0) {}

template<typename _Tp> inline Point3<_Tp>::Point3(_Tp _x, _Tp _y, _Tp _z)
    : x(_x),
      y(_y),
      z(_z) {}

template<typename _Tp> inline Point3<_Tp>::Point3(const Point3& pt)
    : x(pt.x),
      y(pt.y),
      z(pt.z) {}

template<typename _Tp> inline auto Point3<_Tp>::calcNormSqr() const
{
    return x * x + y * y + z * z;
}

template<typename _Tp> inline auto Point3<_Tp>::calcNorm() const
{
    return std::sqrt(calcNormSqr());
}

template<typename _Tp> inline Point3<_Tp>& Point3<_Tp>::operator = (const Point3& pt)
{
    x = pt.x;
    y = pt.y;
    z = pt.z;

    return *this;
}

template<typename _Tp> inline bool operator == (const Point3<_Tp>& a, const Point3<_Tp>& b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

template<typename _Tp> inline bool operator != (const Point3<_Tp>& a, const Point3<_Tp>& b)
{
    return a.x != b.x || a.y != b.y || a.z != b.z;
}

template<typename _Tp> inline Point3<_Tp> operator *= (Point3<_Tp>& a, const double b)
{
    a.x *= b;
    a.y *= b;
    a.z *= b;

    return a;
}

template<typename _Tp> inline Point3<_Tp> operator += (Point3<_Tp>& a, const Point3<_Tp>& b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;

    return a;
}

template<typename _Tp> inline Point3<_Tp> operator + (const Point3<_Tp>& a, const Point3<_Tp>& b)
{
    return Point3<_Tp>(a.x + b.x, a.y + b.y, a.z + b.z);
}

template<typename _Tp> inline Point3<_Tp> operator - (const Point3<_Tp>& a, const Point3<_Tp>& b)
{
    return Point3<_Tp>(a.x - b.x, a.y - b.y, a.z - b.z);
}

template<typename _Tp> inline Point3<_Tp> operator - (const Point3<_Tp>& a)
{
    return Point3<_Tp>(-a.x, -a.y, -a.z);
}

template<typename _Tp> inline Point3<_Tp> operator / (const Point3<_Tp> a, const double b)
{
    return Point3<_Tp>(a.x / b, a.y / b, a.z / b);
}

template<typename _Tp> inline Point3<_Tp> operator / (const double b, const Point3<_Tp> a)
{
    return Point3<_Tp>(b / a.x, b / a.y, b / a.z);
}

template<typename _Tp> inline Point3<_Tp> operator * (const Point3<_Tp>& a, const double b)
{
    return Point3<_Tp>(a.x * b, a.y * b, a.z * b);
}

template<typename _Tp> inline Point3<_Tp> operator * (const double b, const Point3<_Tp>& a)
{
    return Point3<_Tp>(b * a.x, b * a.y, b * a.z);
}
} //SPHAlgorithms

#endif // POINT_HPP_FCE0209B335F4EBB846046447678D096
