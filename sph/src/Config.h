#ifndef CONFIG_H_73C34465A6ED4DB9B9F2F4C3937BF5DC
#define CONFIG_H_73C34465A6ED4DB9B9F2F4C3937BF5DC

#include "algorithms/src/Point.h"

#include <cstddef>

namespace SPHSDK
{
struct Config
{
    static const size_t ParticlesNumber;
    static const double ParticleRadius;

    static const double WaterDensity;
    static const double WaterStiffness;
    static const double WaterViscosity;
    static const double WaterThreshold;
    static const double WaterParticleMass;
    static const double WaterSupportRadius;
    static const double WaterSurfaceTension;

    static const SPHAlgorithms::Point3D InitialGravitationalAcceleration;
    static SPHAlgorithms::Point3D GravitationalAcceleration;
    static const SPHAlgorithms::Point3D InitialVelocity;
    static const double CollisionVelocityMultiplier;

    static const double SpeedTreshold;

    static const double CubeSize;

}; //Config
} //SPHSDK

#endif // CONFIG_H_73C34465A6ED4DB9B9F2F4C3937BF5DC
