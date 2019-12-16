/**
* @file Area.h
* @author Anton Artyukh (artyukhanton@gmail.com)
* @date Created Feb 26, 2017
**/

#ifndef AREA_H_43C34465A6ED4DB9B9F2F4C3937BF5DC
#define AREA_H_43C34465A6ED4DB9B9F2F4C3937BF5DC

#include "Point.h"

namespace SPHAlgorithms
{

// TODO move to common and to separate class
struct Rect
{
    Point2D leftTop;

    Point2D rightBottom;

    Rect() :
        leftTop( Point2D{0., 0.} ),
        rightBottom( Point2D{0., 0.} ) {}

    Rect(const Point2D& leftTop_, const Point2D& rightBotom_) :
        leftTop(leftTop_),
        rightBottom(rightBotom_) {}
};

/**
* @brief Cuboid class defines cube.
*/
struct Cuboid
{
    Point3D startingPoint;
    double width, length, height; // x, y, z axis

    Cuboid() :
        startingPoint( Point3D{0., 0., 0.} ),
        width(0.),
        length(0.),
        height(0.) {}

    Cuboid(const Point3D& _startingPoint, const double _width, const double _length, const double _height) :
        startingPoint(_startingPoint),
        width(_width),
        length(_length),
        height(_height) {}
};

/**
* @brief Area class defines area.
*/
class Area
{
public:

    Area();

    Area(const Rect& rect);

    ~Area();

    double areaFunction(double x, double y);

    Rect getBoundingRect() const;

    bool isInsideArea(const Point2D& point);

private:

    Rect m_boundingRect;
};

/**
* @brief Volume class defines volume.
* The x-axis is equal to width.
* The y-axis is equal to length.
* The z-axis is equal to height.
*/
class Volume
{
public:

    Volume();
    Volume(const Cuboid& cube);

    ~Volume();

    Cuboid getBoundingCuboid() const;

private:

    Cuboid m_boundingCuboid;

};

} //SPHAlgorithms

#endif // AREA_H_43C34465A6ED4DB9B9F2F4C3937BF5DC
