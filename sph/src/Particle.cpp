/**
* @file Particle.cpp
* @author Anton Artyukh (artyukhanton@gmail.com)
* @date Created May 21, 2017
**/

#include "Particle.h"

namespace SPHSDK
{

Particle::Particle() :
    position(Point3F()),
    radius(0.0),
    density(0.0),
    pressure(0.0),
    mass(0.0),
    supportRadius(0.0),
    velocity(Point3F()),
    acceleration(Point3F()),
    fGravity(Point3F()),
    fSurfaceTension(Point3F()),
    fViscosity(Point3F()),
    fPressure(Point3F()),
    fExternal(Point3F()),
    fInternal(Point3F()),
    fTotal(Point3F())
{
}

Particle::Particle(const Point3F& position, FLOAT radius) :
    position(position),
    radius(radius),
    density(0.0),
    pressure(0.0),
    mass(0.0),
    supportRadius(0.0),
    velocity(Point3F()),
    acceleration(Point3F()),
    fGravity(Point3F()),
    fSurfaceTension(Point3F()),
    fViscosity(Point3F()),
    fPressure(Point3F()),
    fExternal(Point3F()),
    fInternal(Point3F()),
    fTotal(Point3F())
{
}

} // SPHSDK
