#include "Forces.h"

#define _USE_MATH_DEFINES
#include <cfloat>
#include <math.h>
#include <cassert>

namespace SPHSDK
{

static const FLOAT PiPowH9 = M_PI * pow(Config::WaterSupportRadius, 9);
static const FLOAT PiPowH6 = M_PI * pow(Config::WaterSupportRadius, 6);
static const FLOAT SupportRadiusSqr = Config::WaterSupportRadius * Config::WaterSupportRadius;
static const FLOAT KernelDefaultMultiplier = 315.0 / (64.0 * PiPowH9);
static const FLOAT KernelDefaultGradientMultiplier = -945.0 / (32.0 * PiPowH9);
static const FLOAT KernelPressureGradientMultiplier = -45.0 / PiPowH6;
static const FLOAT KernelViscosityLaplacianMultiplier = 45.0 / PiPowH6;
static const FLOAT OwnDensity = 315.0 / (64.0 * M_PI * pow(Config::WaterSupportRadius, 3));


static FLOAT defaultKernel(const Point3F& differenceParticleNeighbour) {
    // (Formula 4.3)
    const FLOAT particleDistanceSqr = differenceParticleNeighbour.calcNormSqr();
    return KernelDefaultMultiplier * pow(SupportRadiusSqr - particleDistanceSqr, 3);
}

static Point3F defaultKernelGradient(const Point3F& differenceParticleNeighbour) {
    // (Formula 4.4)
    const FLOAT particleDistanceSqr = differenceParticleNeighbour.calcNormSqr();
    return differenceParticleNeighbour * KernelDefaultGradientMultiplier
                                       * (SupportRadiusSqr - particleDistanceSqr)
                                       * (SupportRadiusSqr - particleDistanceSqr);
}

static FLOAT defaultKernelLaplacian(const Point3F& differenceParticleNeighbour) {
    // (Formula 4.5)
    const FLOAT particleDistanceSqr = differenceParticleNeighbour.calcNormSqr();
    return KernelDefaultGradientMultiplier * (SupportRadiusSqr - particleDistanceSqr)
                                           * (3.0 * SupportRadiusSqr - 7.0 * particleDistanceSqr);
}

static Point3F pressureKernelGradient(const Point3F& differenceParticleNeighbour) {
    // (Formula 4.14)
    const FLOAT particleDistance = differenceParticleNeighbour.calcNorm();
    return differenceParticleNeighbour * KernelPressureGradientMultiplier / particleDistance
                                       * (Config::WaterSupportRadius - particleDistance)
                                       * (Config::WaterSupportRadius - particleDistance);
}

static FLOAT viscosityKernelLaplacian(const Point3F& differenceParticleNeighbour) {
    // (Formula 4.22)
    const FLOAT particleDistance = differenceParticleNeighbour.calcNorm();
    return KernelViscosityLaplacianMultiplier * (Config::WaterSupportRadius - particleDistance);
}

void Forces::ComputeDensity(ParticleVect& particleVect)
{
    // (Formula 4.6)
    for (size_t i = 0; i < particleVect.size(); i++)
    {
        particleVect[i].density = OwnDensity;

        for (size_t j = 0; j < particleVect[i].neighbours.size(); j++)
        {
            const Point3F differenceParticleNeighbour =
                particleVect[i].position - particleVect[particleVect[i].neighbours[j]].position;

            if (Config::WaterSupportRadius - differenceParticleNeighbour.calcNorm() > DBL_EPSILON)
                particleVect[i].density += Config::WaterParticleMass * defaultKernel(differenceParticleNeighbour);
        }
    }
}

void Forces::ComputePressure(ParticleVect& particleVect)
{
    // (Formula 4.12)
    for (auto& particle : particleVect)
    {
        particle.pressure = Config::WaterStiffness * (particle.density - Config::WaterDensity);
    }
}

void Forces::ComputeInternalForces(ParticleVect& particleVect)
{
    for (size_t i = 0; i < particleVect.size(); i++)
    {
        particleVect[i].fPressure = Point3F();
        particleVect[i].fViscosity = Point3F();

        for (size_t j = 0; j < particleVect[i].neighbours.size(); j++)
        {
            assert(std::abs(particleVect[i].density) > 0.);
            assert(std::abs(particleVect[particleVect[i].neighbours[j]].density) > 0.);

            const Point3F differenceParticleNeighbour =
                particleVect[i].position - particleVect[particleVect[i].neighbours[j]].position;

            const FLOAT particleDistance = differenceParticleNeighbour.calcNorm();

            if (std::abs(particleDistance) > 0.)
            {
                const FLOAT dividedMassDensity =
                    Config::WaterParticleMass / particleVect[particleVect[i].neighbours[j]].density;

                // (Formulae 4.11 & 4.14)
                particleVect[i].fPressure +=
                    pressureKernelGradient(differenceParticleNeighbour) *
                    (particleVect[i].pressure + particleVect[particleVect[i].neighbours[j]].pressure) *
                    dividedMassDensity;

                // (Formulae 4.17 & 4.22)
                particleVect[i].fViscosity +=
                    (particleVect[particleVect[i].neighbours[j]].velocity - particleVect[i].velocity) *
                    viscosityKernelLaplacian(differenceParticleNeighbour) * dividedMassDensity;
            }
        }

        particleVect[i].fPressure *= -0.5;
        particleVect[i].fViscosity *= Config::WaterViscosity;

        particleVect[i].fInternal = particleVect[i].fPressure + particleVect[i].fViscosity;
    }
}

void Forces::ComputeGravityForce(ParticleVect& particleVect)
{
    for (auto& particle : particleVect)
    {
        particle.fGravity = Config::GravitationalAcceleration * particle.density;
    }
}

void Forces::ComputeSurfaceTension(ParticleVect& particleVect)
{
    for (size_t i = 0; i < particleVect.size(); i++)
    {
        particleVect[i].fSurfaceTension = Point3F();

        Point3F surfaceTensionGradient = Point3F();
        FLOAT surfaceTensionLaplacian = 0.0;

        for (size_t j = 0; j < particleVect[i].neighbours.size(); j++)
        {
            assert(std::abs(particleVect[i].density) > 0.);
            assert(std::abs(particleVect[particleVect[i].neighbours[j]].density) > 0.);

            const Point3F differenceParticleNeighbour =
                particleVect[i].position - particleVect[particleVect[i].neighbours[j]].position;

            if (differenceParticleNeighbour.calcNormSqr() <= SupportRadiusSqr)
            {
                const FLOAT dividedMassDensity =
                    Config::WaterParticleMass / particleVect[particleVect[i].neighbours[j]].density;

                // (Formulae 4.28 & 4.4)
                surfaceTensionGradient += defaultKernelGradient(differenceParticleNeighbour) * dividedMassDensity;

                // (Formulae 4.27 & 4.5)
                surfaceTensionLaplacian += defaultKernelLaplacian(differenceParticleNeighbour) * dividedMassDensity;
            }
        }

        // (Formulae 4.32 & 5.17)
        if (surfaceTensionGradient.calcNorm() >= std::sqrt(Config::WaterDensity / particleVect[i].neighbours.size()))
            // (Formula 4.26 is presented by combination of 4.27 & 4.5 - laplacian - and 4.28 & 4.4 - gradient)
            particleVect[i].fSurfaceTension = -surfaceTensionGradient / surfaceTensionGradient.calcNorm() *
                                               surfaceTensionLaplacian * Config::WaterSurfaceTension;
    }
}

void Forces::ComputeExternalForces(ParticleVect& particleVect)
{
    Forces::ComputeGravityForce(particleVect);
    Forces::ComputeSurfaceTension(particleVect);

    for (auto& particle : particleVect)
    {
        particle.fExternal = particle.fSurfaceTension + particle.fGravity;
    }
}

void Forces::ComputeAllForces(ParticleVect& particleVect)
{
    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);
    Forces::ComputeInternalForces(particleVect);
    Forces::ComputeExternalForces(particleVect);

    for (auto& particle : particleVect)
    {
        particle.fTotal = particle.fExternal + particle.fInternal;
    }
}

} // namespace SPHSDK
