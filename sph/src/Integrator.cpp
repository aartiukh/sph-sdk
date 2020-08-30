/**
* @file Integrator.cpp
* @author Anton Artyukh (artyukhanton@gmail.com)
* @date Created June 11, 2017
**/

#include "Integrator.h"
#include "Config.h"

#include <cmath>

namespace SPHSDK
{

void Integrator::integrate(double timeStep, ParticleVect& particles)
{
    for (auto& particle : particles)
    {
        particle.previous_position = particle.position;

        const SPHAlgorithms::Point3D prevAcceleration = particle.acceleration;

        if (std::abs(particle.density) > 0.)
            particle.acceleration = particle.fTotal / particle.density;

        const SPHAlgorithms::Point3D prevVelocity = particle.velocity;

        particle.velocity += (prevAcceleration + particle.acceleration) / 2.0 * timeStep;

        if (particle.velocity.calcNormSqr() > Config::SpeedTreshold)
            particle.velocity = prevVelocity;

        particle.position += prevVelocity * timeStep + prevAcceleration / 2.0 * timeStep * timeStep;
    }
}

} // SPHSDK
