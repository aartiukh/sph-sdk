/**
 * @file Particle.h
 * @author Anton Artyukh (artyukhanton@gmail.com)
 * @date Created May 21, 2017
 **/

#ifndef PARTICLE_H_73C34465A6ED4DB9B9F2F4C3937BF5DC
#define PARTICLE_H_73C34465A6ED4DB9B9F2F4C3937BF5DC

#include "Config.h"
#include "algorithms/src/Defines.h"
#include "algorithms/src/Point.h"

namespace SPHSDK
{

namespace TestEnvironment
{
class ParticleTestSuite;
} // namespace TestEnvironment

/**
 * @brief Particle class defines one particle object with properties.
 */
class Particle
{
    friend class TestEnvironment::ParticleTestSuite;

public:
    Particle();
    Particle(SPHAlgorithms::Point3D && position, double radius = Config::ParticleRadius);

    double radius;
    double density;
    double pressure;
    double mass;
    double supportRadius;

    SPHAlgorithms::Point3D position;
    SPHAlgorithms::Point3D previous_position;
    SPHAlgorithms::Point3D velocity;
    SPHAlgorithms::Point3D acceleration;

    SPHAlgorithms::Point3D fGravity;
    SPHAlgorithms::Point3D fSurfaceTension;
    SPHAlgorithms::Point3D fViscosity;
    SPHAlgorithms::Point3D fPressure;

    SPHAlgorithms::Point3D fExternal;
    SPHAlgorithms::Point3D fInternal;

    SPHAlgorithms::Point3D fTotal;

    SPHAlgorithms::SizetVector neighbours;
};

using ParticleVect = std::vector<Particle>;
using ParticleVectConstIter = ParticleVect::const_iterator;
using ParticleVectIter = ParticleVect::iterator;

} // namespace SPHSDK

#endif // PARTICLE_H_73C34465A6ED4DB9B9F2F4C3937BF5DC
