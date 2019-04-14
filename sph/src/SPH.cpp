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

#include <iostream>
#include <cmath>
#include <cfloat>

namespace SPHSDK
{

namespace
{
inline SPHAlgorithms::Point3D SpericalToCartesian(double r, double fi, double teta)
{
    return SPHAlgorithms::Point3D(r * sin(teta) * cos(fi) + 1.5, r * sin(teta) * sin(fi) + 1.5, r * cos(teta) + 2.);
}
}

SPH::SPH()
    : particles(Config::ParticlesNumber),
      m_volume(SPHAlgorithms::Volume(SPHAlgorithms::Cuboid(SPHAlgorithms::Point3D(),
                                                           Config::CubeSize,
                                                           Config::CubeSize,
                                                           Config::CubeSize))),
      m_searcher(SPHAlgorithms::NeighboursSearch3D<ParticleVect>(m_volume, Config::WaterSupportRadius, 0.001))
{
    // set initial particle data
    double r = 2 * Config::ParticleRadius;
    double fi = 0.;
    double teta = 0.;

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

        fi = 2 * M_PI * n / N;
        teta = M_PI * m / M;

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

    Collision::detectCollisions(particles, m_volume);
}

} // namespace SPHSDK
