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

    Particle(const SPHAlgorithms::Point3F& position, double radius = Config::ParticleRadius);

    SPHAlgorithms::Point3F position;

    double radius;
    double density;
    double pressure;
    double mass;
    double supportRadius;

    SPHAlgorithms::Point3F previous_position;
    SPHAlgorithms::Point3F velocity;
    SPHAlgorithms::Point3F acceleration;

    SPHAlgorithms::Point3F fGravity;
    SPHAlgorithms::Point3F fSurfaceTension;
    SPHAlgorithms::Point3F fViscosity;
    SPHAlgorithms::Point3F fPressure;

    SPHAlgorithms::Point3F fExternal;
    SPHAlgorithms::Point3F fInternal;

    SPHAlgorithms::Point3F fTotal;

    SPHAlgorithms::SizetVector neighbours;
};

using ParticleVect = std::vector<Particle>;
using ParticleVectConstIter = ParticleVect::const_iterator;
using ParticleVectIter = ParticleVect::iterator;

} // namespace SPHSDK

#endif // PARTICLE_H_73C34465A6ED4DB9B9F2F4C3937BF5DC
