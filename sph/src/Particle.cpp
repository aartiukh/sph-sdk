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
    position(SPHAlgorithms::Point3D{0., 0., 0.}),
    velocity(SPHAlgorithms::Point3D{0., 0., 0.}),
    acceleration(SPHAlgorithms::Point3D{0., 0., 0.}),
    fGravity(SPHAlgorithms::Point3D{0., 0., 0.}),
    fSurfaceTension(SPHAlgorithms::Point3D{0., 0., 0.}),
    fViscosity(SPHAlgorithms::Point3D{0., 0., 0.}),
    fPressure(SPHAlgorithms::Point3D{0., 0., 0.}),
    fExternal(SPHAlgorithms::Point3D{0., 0., 0.}),
    fInternal(SPHAlgorithms::Point3D{0., 0., 0.}),
    fTotal(SPHAlgorithms::Point3D{0., 0., 0.})
{
}

Particle::Particle(SPHAlgorithms::Point3D && position, double radius) :
    radius(radius),
    density(0.0),
    pressure(0.0),
    position( std::forward<SPHAlgorithms::Point3D>(position) ),
    velocity(SPHAlgorithms::Point3D{0., 0., 0.}),
    acceleration(SPHAlgorithms::Point3D{0., 0., 0.}),
    fGravity(SPHAlgorithms::Point3D{0., 0., 0.}),
    fSurfaceTension(SPHAlgorithms::Point3D{0., 0., 0.}),
    fViscosity(SPHAlgorithms::Point3D{0., 0., 0.}),
    fPressure(SPHAlgorithms::Point3D{0., 0., 0.}),
    fExternal(SPHAlgorithms::Point3D{0., 0., 0.}),
    fInternal(SPHAlgorithms::Point3D{0., 0., 0.}),
    fTotal(SPHAlgorithms::Point3D{0., 0., 0.})
{
}

} // SPHSDK
