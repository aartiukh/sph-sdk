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

void Integrator::integrate(FLOAT timeStep, ParticleVect& particles)
{
    for (auto& particle : particles)
    {
        particle.previous_position = particle.position;

        const Point3F prevAcceleration = particle.acceleration;

        if (std::abs(particle.density) > 0.)
            particle.acceleration = particle.fTotal / particle.density;

        const Point3F prevVelocity = particle.velocity;

        particle.velocity += (prevAcceleration + particle.acceleration) / 2.0 * timeStep;

        if (particle.velocity.calcNormSqr() > Config::SpeedTreshold)
            particle.velocity = prevVelocity;

        particle.position += prevVelocity * timeStep + prevAcceleration / 2.0 * timeStep * timeStep;

        // color depends on velocity
        const SPHSDK::FLOAT velocityNorm = particle.velocity.calcNormSqr();
        particle.colour = Point3F(0.0f, 0.0f, 1.0f);

        if (velocityNorm > SPHSDK::Config::SpeedTreshold / 2.)
        {
            particle.colour = Point3F(1.0f, 0.0f, 0.0f);
        }
        else if (velocityNorm > SPHSDK::Config::SpeedTreshold / 4.)
        {
            particle.colour = Point3F(0.99f, 0.7f, 0.0f);
        }
    }
}

} // SPHSDK
