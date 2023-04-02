/**
* @file Area.h
* @author Anton Artyukh (artyukhanton@gmail.com)
* @date Created Feb 26, 2017
**/

#ifndef AREA_H_43C34465A6ED4DB9B9F2F4C3937BF5DC
#define AREA_H_43C34465A6ED4DB9B9F2F4C3937BF5DC

#include "Point.h"

namespace SPHSDK
{

struct Rect
{
    Point2F leftTop;

    Point2F rightBottom;

    Rect() :
        leftTop(Point2F()),
        rightBottom(Point2F()) {}

    Rect(const Point2F& leftTop_, const Point2F& rightBotom_) :
        leftTop(leftTop_),
        rightBottom(rightBotom_) {}
};

/**
* @brief Cuboid class defines cube.
*/
struct Cuboid
{
    Point3F startingPoint;
    FLOAT width, length, height; // x, y, z axis

    Cuboid() :
        startingPoint(Point3F()),
        width(0.),
        length(0.),
        height(0.) {}

    Cuboid(const Point3F& _startingPoint, const FLOAT _width, const FLOAT _length, const FLOAT _height) :
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

    explicit Area(const Rect& rect);

    ~Area() = default;

    FLOAT areaFunction(FLOAT x, FLOAT y);

    Rect getBoundingRect() const;

    bool isInsideArea(const Point2F& point);

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

    explicit Volume(const Cuboid& cube);

    ~Volume() = default;

    Cuboid getBoundingCuboid() const;

private:

    Cuboid m_boundingCuboid;

};

} // SPHSDK

#endif // AREA_H_43C34465A6ED4DB9B9F2F4C3937BF5DC
