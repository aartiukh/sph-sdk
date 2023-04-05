//
//  Config.cpp
//
//  Created by Oleksii Shabalin on 11/3/18.
//

#include "Config.h"

namespace SPHSDK
{
    const size_t Config::ParticlesNumber = 6000;
    const FLOAT Config::ParticleRadius = 0.015;

    const FLOAT Config::WaterDensity = 998.29;
    const FLOAT Config::WaterStiffness = 3.0;
    const FLOAT Config::WaterViscosity = 3.5;
    const FLOAT Config::WaterThreshold = 7.065;
    const FLOAT Config::WaterParticleMass = 0.02;
    const FLOAT Config::WaterSupportRadius = 0.1;
    const FLOAT Config::WaterSurfaceTension = 0.0728;

    const Point3F Config::InitialGravitationalAcceleration(0.0, 0.0, -9.82);
    Point3F Config::GravitationalAcceleration(0.0, 0.0, -9.82);
    const Point3F Config::InitialVelocity(0.0, 0.0, 0.0);
    const FLOAT Config::CollisionVelocityMultiplier = -0.5;

    const FLOAT Config::SpeedTreshold = 3.0;

    const FLOAT Config::CubeSize = 3.0;
} //SPHSDK
