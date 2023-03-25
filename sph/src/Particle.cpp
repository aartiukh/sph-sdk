/**
* @file Particle.cpp
* @author Anton Artyukh (artyukhanton@gmail.com)
* @date Created May 21, 2017
**/

#include "Particle.h"

namespace SPHSDK
{

Particle::Particle() :
    position(SPHAlgorithms::Point3F()),
    radius(0.0),
    density(0.0),
    pressure(0.0),
    mass(0.0),
    supportRadius(0.0),
    velocity(SPHAlgorithms::Point3F()),
    acceleration(SPHAlgorithms::Point3F()),
    fGravity(SPHAlgorithms::Point3F()),
    fSurfaceTension(SPHAlgorithms::Point3F()),
    fViscosity(SPHAlgorithms::Point3F()),
    fPressure(SPHAlgorithms::Point3F()),
    fExternal(SPHAlgorithms::Point3F()),
    fInternal(SPHAlgorithms::Point3F()),
    fTotal(SPHAlgorithms::Point3F())
{
}

Particle::Particle(const SPHAlgorithms::Point3F& position, double radius) :
    position(position),
    radius(radius),
    density(0.0),
    pressure(0.0),
    mass(0.0),
    supportRadius(0.0),
    velocity(SPHAlgorithms::Point3F()),
    acceleration(SPHAlgorithms::Point3F()),
    fGravity(SPHAlgorithms::Point3F()),
    fSurfaceTension(SPHAlgorithms::Point3F()),
    fViscosity(SPHAlgorithms::Point3F()),
    fPressure(SPHAlgorithms::Point3F()),
    fExternal(SPHAlgorithms::Point3F()),
    fInternal(SPHAlgorithms::Point3F()),
    fTotal(SPHAlgorithms::Point3F())
{
}

} // SPHSDK
