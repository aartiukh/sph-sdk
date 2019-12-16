/**
* @file Integrator.h
* @author Anton Artyukh (artyukhanton@gmail.com)
* @date Created June 11, 2017
**/

#ifndef INTEGRATOR_H_73C34465A6ED4DB9B9F2F4C3937BF5DV
#define INTEGRATOR_H_73C34465A6ED4DB9B9F2F4C3937BF5DV

#include "Particle.h"

namespace SPHSDK
{

class Integrator
{
public:
    static void integrate(double timeStep, ParticleVect& particles);
};

} //SPHSDK

#endif // INTEGRATOR_H_73C34465A6ED4DB9B9F2F4C3937BF5DV
