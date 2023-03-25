#ifndef CONFIG_H_73C34465A6ED4DB9B9F2F4C3937BF5DC
#define CONFIG_H_73C34465A6ED4DB9B9F2F4C3937BF5DC

#include "algorithms/src/Point.h"

#include <cstddef>

namespace SPHSDK
{
struct Config
{
    static const size_t ParticlesNumber;
    static const FLOAT ParticleRadius;

    static const FLOAT WaterDensity;
    static const FLOAT WaterStiffness;
    static const FLOAT WaterViscosity;
    static const FLOAT WaterThreshold;
    static const FLOAT WaterParticleMass;
    static const FLOAT WaterSupportRadius;
    static const FLOAT WaterSurfaceTension;

    static const Point3F InitialGravitationalAcceleration;
    static Point3F GravitationalAcceleration;
    static const Point3F InitialVelocity;
    static const FLOAT CollisionVelocityMultiplier;

    static const FLOAT SpeedTreshold;

    static const FLOAT CubeSize;

}; //Config
} //SPHSDK

#endif // CONFIG_H_73C34465A6ED4DB9B9F2F4C3937BF5DC
