#include "Forces.h"

#define _USE_MATH_DEFINES
#include <cfloat>
#include <math.h>
#include <cassert>

namespace SPHSDK
{

static const double PiPowH9 = M_PI * pow(Config::WaterSupportRadius, 9);
static const double PiPowH6 = M_PI * pow(Config::WaterSupportRadius, 6);
static const double SupportRadiusSqr = Config::WaterSupportRadius * Config::WaterSupportRadius;
static const double KernelDefaultMultiplier = 315.0 / (64.0 * PiPowH9);
static const double KernelDefaultGradientMultiplier = -945.0 / (32.0 * PiPowH9);
static const double KernelPressureGradientMultiplier = -45.0 / PiPowH6;
static const double KernelViscosityLaplacianMultiplier = 45.0 / PiPowH6;
static const double OwnDensity = 315.0 / (64.0 * M_PI * pow(Config::WaterSupportRadius, 3));

static double defaultKernel(SPHAlgorithms::Point3D differenceParticleNeighbour) {
    // (Formula 4.3)
    const double particleDistanceSqr = differenceParticleNeighbour.norm();
    return KernelDefaultMultiplier * pow(SupportRadiusSqr - particleDistanceSqr, 3);
}

static SPHAlgorithms::Point3D defaultKernelGradient(SPHAlgorithms::Point3D differenceParticleNeighbour) {
    // (Formula 4.4)
    const double particleDistanceSqr = differenceParticleNeighbour.norm();
    return differenceParticleNeighbour * KernelDefaultGradientMultiplier
                                       * (SupportRadiusSqr - particleDistanceSqr)
                                       * (SupportRadiusSqr - particleDistanceSqr);
}

static double defaultKernelLaplacian(SPHAlgorithms::Point3D differenceParticleNeighbour) {
    // (Formula 4.5)
    const double particleDistanceSqr = differenceParticleNeighbour.norm();
    return KernelDefaultGradientMultiplier * (SupportRadiusSqr - particleDistanceSqr)
                                           * (3.0 * SupportRadiusSqr - 7.0 * particleDistanceSqr);
}

static SPHAlgorithms::Point3D pressureKernelGradient(SPHAlgorithms::Point3D differenceParticleNeighbour) {
    // (Formula 4.14)
    const double particleDistance = std::sqrt( differenceParticleNeighbour.norm() );
    return differenceParticleNeighbour * KernelPressureGradientMultiplier / particleDistance
                                       * (Config::WaterSupportRadius - particleDistance)
                                       * (Config::WaterSupportRadius - particleDistance);
}

static double viscosityKernelLaplacian(SPHAlgorithms::Point3D differenceParticleNeighbour) {
    // (Formula 4.22)
    const double particleDistance = std::sqrt( differenceParticleNeighbour.norm() );
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
            const SPHAlgorithms::Point3D differenceParticleNeighbour =
                particleVect[i].position - particleVect[particleVect[i].neighbours[j]].position;

            if (Config::WaterSupportRadius - std::sqrt(differenceParticleNeighbour.norm()) > DBL_EPSILON)
                particleVect[i].density += Config::WaterParticleMass * defaultKernel(differenceParticleNeighbour);
        }
    }
}

void Forces::ComputePressure(ParticleVect& particleVect)
{
    // (Formula 4.12)
    for (ParticleVectIter iter = particleVect.begin(); iter != particleVect.end(); ++iter)
        iter->pressure = Config::WaterStiffness * (iter->density - Config::WaterDensity);
}

void Forces::ComputeInternalForces(ParticleVect& particleVect)
{
    for (size_t i = 0; i < particleVect.size(); i++)
    {
        particleVect[i].fPressure = SPHAlgorithms::Point3D{0., 0., 0.};
        particleVect[i].fViscosity = SPHAlgorithms::Point3D{0., 0., 0.};

        for (size_t j = 0; j < particleVect[i].neighbours.size(); j++)
        {
            assert(std::abs(particleVect[i].density) > 0.);
            assert(std::abs(particleVect[particleVect[i].neighbours[j]].density) > 0.);

            const SPHAlgorithms::Point3D differenceParticleNeighbour =
                particleVect[i].position - particleVect[particleVect[i].neighbours[j]].position;

            const double particleDistance = std::sqrt( differenceParticleNeighbour.norm() );

            if (std::abs(particleDistance) > 0.)
            {
                const double dividedMassDensity =
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
    for (ParticleVectIter iter = particleVect.begin(); iter != particleVect.end(); ++iter)
        iter->fGravity = Config::GravitationalAcceleration * iter->density;
}

void Forces::ComputeSurfaceTension(ParticleVect& particleVect)
{
    for (size_t i = 0; i < particleVect.size(); i++)
    {
        particleVect[i].fSurfaceTension = SPHAlgorithms::Point3D{0., 0., 0.};

        SPHAlgorithms::Point3D surfaceTensionGradient = SPHAlgorithms::Point3D{0., 0., 0.};
        double surfaceTensionLaplacian = 0.0;

        for (size_t j = 0; j < particleVect[i].neighbours.size(); j++)
        {
            assert(std::abs(particleVect[i].density) > 0.);
            assert(std::abs(particleVect[particleVect[i].neighbours[j]].density) > 0.);

            const SPHAlgorithms::Point3D differenceParticleNeighbour =
                particleVect[i].position - particleVect[particleVect[i].neighbours[j]].position;

            if (differenceParticleNeighbour.norm() <= SupportRadiusSqr)
            {
                const double dividedMassDensity =
                    Config::WaterParticleMass / particleVect[particleVect[i].neighbours[j]].density;

                // (Formulae 4.28 & 4.4)
                surfaceTensionGradient += defaultKernelGradient(differenceParticleNeighbour) * dividedMassDensity;

                // (Formulae 4.27 & 4.5)
                surfaceTensionLaplacian += defaultKernelLaplacian(differenceParticleNeighbour) * dividedMassDensity;
            }
        }

        // (Formulae 4.32 & 5.17)
        if (surfaceTensionGradient.norm() >= std::sqrt(Config::WaterDensity / particleVect[i].neighbours.size()))
            // (Formula 4.26 is presented by combination of 4.27 & 4.5 - laplacian - and 4.28 & 4.4 - gradient)
            particleVect[i].fSurfaceTension = -surfaceTensionGradient / std::sqrt(surfaceTensionGradient.norm()) *
                                               surfaceTensionLaplacian * Config::WaterSurfaceTension;
    }
}

void Forces::ComputeExternalForces(ParticleVect& particleVect)
{
    Forces::ComputeGravityForce(particleVect);
    Forces::ComputeSurfaceTension(particleVect);

    for (ParticleVectIter iter = particleVect.begin(); iter != particleVect.end(); ++iter)
        iter->fExternal = iter->fSurfaceTension + iter->fGravity;
}

void Forces::ComputeAllForces(ParticleVect& particleVect)
{
    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);
    Forces::ComputeInternalForces(particleVect);
    Forces::ComputeExternalForces(particleVect);

    for (ParticleVectIter iter = particleVect.begin(); iter != particleVect.end(); ++iter)
        iter->fTotal = iter->fExternal + iter->fInternal;
}

} // namespace SPHSDK
