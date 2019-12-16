/**
* @file Forces.h
* @author Anton Artyukh (artyukhanton@gmail.com)
* @date Created June 2, 2017
**/

#ifndef FORCES_H_73C34465A6ED4DB9B9F2F4C3937BF5DC
#define FORCES_H_73C34465A6ED4DB9B9F2F4C3937BF5DC

#include "Collisions.h"
#include "Config.h"
#include "Particle.h"

namespace SPHSDK
{

namespace TestEnvironment
{
    class ForcesTestSuite;
} // TestEnvironment

class Forces
{
    friend class TestEnvironment::ForcesTestSuite;

public:

    static void ComputeAllForces(ParticleVect& particleVect);

private:

    static void ComputeDensity(ParticleVect& particleVect);

    static void ComputePressure(ParticleVect& particleVect);

    static void ComputeSurfaceTension(ParticleVect& particleVect);

    static void ComputeGravityForce(ParticleVect& particleVect);

    static void ComputeInternalForces(ParticleVect& particleVect);

    static void ComputeExternalForces(ParticleVect& particleVect);

}; // Forces

} // SPHSDK

#endif // FORCES_H_73C34465A6ED4DB9B9F2F4C3937BF5DC
