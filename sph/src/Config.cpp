//
//  Config.cpp
//
//  Created by Oleksii Shabalin on 11/3/18.
//

#include "sph/include/Config.h"

namespace SPHSDK
{
    const size_t Config::ParticlesNumber = 6000;
    const double Config::ParticleRadius = 0.015;

    const double Config::WaterDensity = 998.29;
    const double Config::WaterStiffness = 3.0;
    const double Config::WaterViscosity = 3.5;
    const double Config::WaterThreshold = 7.065;
    const double Config::WaterParticleMass = 0.02;
    const double Config::WaterSupportRadius = 0.1;
    const double Config::WaterSurfaceTension = 0.0728;

    const SPHAlgorithms::Point3D Config::InitialGravitationalAcceleration(0.0, 0.0, -9.82);
    SPHAlgorithms::Point3D Config::GravitationalAcceleration(0.0, 0.0, -9.82);
    const SPHAlgorithms::Point3D Config::InitialVelocity(0.0, 0.0, 0.0);

    const double Config::SpeedTreshold = 3.0;

    const double Config::CubeSize = 3.0;
} //SPHSDK
