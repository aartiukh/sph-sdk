/**
 * @file SPH.cpp
 * @author Anton Artyukh (artyukhanton@gmail.com)
 * @date Created June 12, 2017
 **/

#include "SPH.h"

#include "Collisions.h"
#include "Config.h"
#include "Forces.h"
#include "Integrator.h"

#include <cfloat>
#include <cmath>
#include <iostream>


namespace SPHSDK
{

static const FLOAT PI = 3.14159265359;

namespace
{
inline Point3F SpericalToCartesian(FLOAT r, FLOAT fi, FLOAT teta)
{
    return Point3F(r * sin(teta) * cos(fi) + 1.5, r * sin(teta) * sin(fi) + 1.5, r * cos(teta) + 2.);
}
} // namespace

SPH::SPH(const std::function<FLOAT(FLOAT, FLOAT, FLOAT)>* obstacle)
    : particles(Config::ParticlesNumber)
    , m_volume(Volume(
          Cuboid(Point3F(), Config::CubeSize, Config::CubeSize, Config::CubeSize)))
    , m_searcher(NeighboursSearch3D<ParticleVect>(m_volume, Config::WaterSupportRadius, 0.001))
    , m_obstacle(obstacle)
{
    // set initial particle data
    FLOAT r = 2 * Config::ParticleRadius;
    FLOAT fi = 0.;
    FLOAT teta = 0.;

    size_t M = 5;
    size_t N = 5;

    size_t m = 0;
    size_t n = 0;

    for (size_t i = 0u; i < Config::ParticlesNumber; ++i)
    {
        particles[i] = SpericalToCartesian(r, fi, teta);
        particles[i].velocity = Config::InitialVelocity;
        particles[i].mass = Config::WaterParticleMass;
        particles[i].supportRadius = Config::WaterSupportRadius;

        ++n;

        fi = 2 * PI * n / N;
        teta = PI * m / M;

        if (n == N)
        {
            ++m;
            n = 0;
        }

        if (m == M)
        {
            n = 0;
            m = 0;
            r += 2 * Config::ParticleRadius;
            M += 2;
            N += 2;
        }
    }
}

void SPH::run()
{
    m_searcher.search(particles);

    Forces::ComputeAllForces(particles);
    Integrator::integrate(0.01, particles);

    Collision::detectCollisions(particles, m_volume, m_obstacle);
}

} // namespace SPHSDK
