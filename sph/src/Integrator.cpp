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
    for (ParticleVectIter iter = particles.begin(); iter != particles.end(); ++iter)
    {
        iter->previous_position = iter->position;

        const SPHAlgorithms::Point3D prevAcceleration = iter->acceleration;

        if (std::abs(iter->density) > 0.)
            iter->acceleration = iter->fTotal / iter->density;

        const SPHAlgorithms::Point3D prevVelocity = iter->velocity;

        iter->velocity += (prevAcceleration + iter->acceleration) / 2.0 * timeStep;

        if (iter->velocity.norm() > Config::SpeedTreshold)
            iter->velocity = prevVelocity;

        iter->position += prevVelocity * timeStep + prevAcceleration / 2.0 * timeStep * timeStep;
    }
}

} // SPHSDK
