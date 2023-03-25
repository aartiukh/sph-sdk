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

    Particle(const Point3F& position, FLOAT radius = Config::ParticleRadius);

    Point3F position;

    FLOAT radius;
    FLOAT density;
    FLOAT pressure;
    FLOAT mass;
    FLOAT supportRadius;

    Point3F previous_position;
    Point3F velocity;
    Point3F acceleration;

    Point3F fGravity;
    Point3F fSurfaceTension;
    Point3F fViscosity;
    Point3F fPressure;

    Point3F fExternal;
    Point3F fInternal;

    Point3F fTotal;

    SizetVector neighbours;
};

using ParticleVect = std::vector<Particle>;
using ParticleVectConstIter = ParticleVect::const_iterator;
using ParticleVectIter = ParticleVect::iterator;

} // namespace SPHSDK

#endif // PARTICLE_H_73C34465A6ED4DB9B9F2F4C3937BF5DC
