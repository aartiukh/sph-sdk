#include "sph/include/Collisions.h"

#include "Config.h"
#include "algorithms/include/Area.h"
#include "algorithms/include/NeighboursSearch.h"

namespace SPHSDK
{

// (Formula 4.35)
static double calculateF(SPHAlgorithms::Point3D differenceParticleNeighbour)
{
    return differenceParticleNeighbour.calcNormSqr() - Config::ParticleRadius * Config::ParticleRadius;
}

// (Formula 4.36)
static SPHAlgorithms::Point3D calculateContactPoint(SPHAlgorithms::Point3D particlePosition,
                                                    SPHAlgorithms::Point3D differenceParticleNeighbour)
{
    double particleDistance = differenceParticleNeighbour.calcNorm();
    return particlePosition + (differenceParticleNeighbour / particleDistance) * Config::ParticleRadius;
}

// (Formula 4.38)
static SPHAlgorithms::Point3D calculateSurfaceNormal(SPHAlgorithms::Point3D differenceParticleNeighbour)
{
    double particleDistance = differenceParticleNeighbour.calcNorm();
    return - differenceParticleNeighbour / particleDistance;
}

// (Formula 4.56)
static SPHAlgorithms::Point3D calculateVelocity(SPHAlgorithms::Point3D particleVelocity,
                                                SPHAlgorithms::Point3D differenceParticleNeighbour)
{
        double scalarProduct = particleVelocity.x * differenceParticleNeighbour.x
                             + particleVelocity.y * differenceParticleNeighbour.y
                             + particleVelocity.z * differenceParticleNeighbour.z;
        return particleVelocity - differenceParticleNeighbour * 2 * scalarProduct;
}

void Collision::detectCollisions(ParticleVect& particleVect, const SPHAlgorithms::Volume& volume)
{
    for (size_t i = 0; i < particleVect.size(); i++)
    {
        /* Particle Collision */

        for (size_t j = 0; j < particleVect[i].neighbours.size(); j++)
        {
            SPHAlgorithms::Point3D differenceParticleNeighbour =
                    particleVect[i].position - particleVect[particleVect[i].neighbours[j]].position;

            // (Formula 4.35)
            if (calculateF(differenceParticleNeighbour) < 0)
            {
                const SPHAlgorithms::Point3D surfaceNormal = calculateSurfaceNormal(differenceParticleNeighbour);

                // (Formula 4.55)
                particleVect[i].position = calculateContactPoint(particleVect[i].position, differenceParticleNeighbour);

                // (Formula 4.56)
                particleVect[i].velocity = calculateVelocity(particleVect[i].velocity, surfaceNormal);
            }
        }

        /* Boundary Collision */

        const SPHAlgorithms::Cuboid cuboid = volume.getBoundingCuboid();

        if (particleVect[i].position.x > cuboid.width - particleVect[i].radius)
        {
            particleVect[i].position.x = cuboid.width - particleVect[i].radius;
            particleVect[i].velocity.x *= -0.5;
        }

        if (particleVect[i].position.x < particleVect[i].radius)
        {
            particleVect[i].position.x = particleVect[i].radius;
            particleVect[i].velocity.x *= -0.5;
        }

        if (particleVect[i].position.y > cuboid.length - particleVect[i].radius)
        {
            particleVect[i].position.y = cuboid.length - particleVect[i].radius;
            particleVect[i].velocity.y *= -0.5;
        }

        if (particleVect[i].position.y < particleVect[i].radius)
        {
            particleVect[i].position.y = particleVect[i].radius;
            particleVect[i].velocity.y *= -0.5;
        }

        if (particleVect[i].position.z > cuboid.height - particleVect[i].radius)
        {
            particleVect[i].position.z = cuboid.height - particleVect[i].radius;
            particleVect[i].velocity.z *= -0.5;
        }

        if (particleVect[i].position.z < particleVect[i].radius)
        {
            particleVect[i].position.z = particleVect[i].radius;
            particleVect[i].velocity.z *= -0.5;
        }
    }
}
} // namespace SPHSDK
