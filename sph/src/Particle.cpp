/**
* @file Particle.cpp
* @author Anton Artyukh (artyukhanton@gmail.com)
* @date Created May 21, 2017
**/

#include "Particle.h"

namespace SPHSDK
{

Particle::Particle() :
    radius(0.0),
    density(0.0),
    pressure(0.0),
    position(SPHAlgorithms::Point3D()),
    velocity(SPHAlgorithms::Point3D()),
    acceleration(SPHAlgorithms::Point3D()),
    fGravity(SPHAlgorithms::Point3D()),
    fSurfaceTension(SPHAlgorithms::Point3D()),
    fViscosity(SPHAlgorithms::Point3D()),
    fPressure(SPHAlgorithms::Point3D()),
    fExternal(SPHAlgorithms::Point3D()),
    fInternal(SPHAlgorithms::Point3D()),
    fTotal(SPHAlgorithms::Point3D())
{
}

Particle::Particle(const SPHAlgorithms::Point3D & position, double radius) :
    radius(radius),
    density(0.0),
    pressure(0.0),
    position(position),
    velocity(SPHAlgorithms::Point3D()),
    acceleration(SPHAlgorithms::Point3D()),
    fGravity(SPHAlgorithms::Point3D()),
    fSurfaceTension(SPHAlgorithms::Point3D()),
    fViscosity(SPHAlgorithms::Point3D()),
    fPressure(SPHAlgorithms::Point3D()),
    fExternal(SPHAlgorithms::Point3D()),
    fInternal(SPHAlgorithms::Point3D()),
    fTotal(SPHAlgorithms::Point3D())
{
}

} // SPHSDK
