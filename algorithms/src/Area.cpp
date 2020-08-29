/**
* @file Area.cpp
* @author Anton Artyukh (artyukhanton@gmail.com)
* @date Created Feb 26, 2017
**/

#include "Area.h"

namespace SPHAlgorithms
{

// TODO: implement

Area::Area() : m_boundingRect(Rect())
{
}

Area::Area(const Rect& rect) : m_boundingRect(rect)
{
}

Rect Area::getBoundingRect() const
{
    return m_boundingRect;
}

bool Area::isInsideArea(const Point2D& /*point*/)
{
    return false;
}

// ---------------------------

Volume::Volume() :
    m_boundingCuboid(Cuboid()) {}

Volume::Volume(const Cuboid& cube) :
    m_boundingCuboid(cube) {}

Cuboid Volume::getBoundingCuboid() const
{
    return m_boundingCuboid;
}

} //SPHAlgorithms
