/**
 * @file Collisions.h
 * @author Anton Artyukh (artyukhanton@gmail.com)
 * @date Created June 2, 2017
 **/

#ifndef COLLISIONS_H_73C34465A6ED4DB9B9F2F4C3937BF5DC
#define COLLISIONS_H_73C34465A6ED4DB9B9F2F4C3937BF5DC

#include "Particle.h"
#include "algorithms/src/Defines.h"

#include <functional>

namespace SPHSDK
{
class Area;
class Volume;


class Collision
{

public:
    static void detectCollisions(ParticleVect& particleVect,
                                 const Volume& volume,
                                 const std::function<FLOAT(FLOAT, FLOAT, FLOAT)>* obstacle = nullptr);
};

} // namespace SPHSDK

#endif // COLLISIONS_H_73C34465A6ED4DB9B9F2F4C3937BF5DC
