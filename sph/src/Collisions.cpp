#include "Collisions.h"

#include "Config.h"
#include "algorithms/src/Area.h"
#include "algorithms/src/NeighboursSearch.h"

namespace SPHSDK
{

// (Formula 4.35)
static double calculateF(SPHAlgorithms::Point3D differenceParticleNeighbour)
{
    return differenceParticleNeighbour.norm() - Config::ParticleRadius * Config::ParticleRadius;
}

// (Formula 4.36)
static SPHAlgorithms::Point3D calculateContactPoint(SPHAlgorithms::Point3D particlePosition,
                                                    SPHAlgorithms::Point3D differenceParticleNeighbour)
{
    double particleDistance = std::sqrt( differenceParticleNeighbour.norm() );
    return particlePosition + (differenceParticleNeighbour / particleDistance) * Config::ParticleRadius;
}

// (Formula 4.38)
static SPHAlgorithms::Point3D calculateSurfaceNormal(SPHAlgorithms::Point3D differenceParticleNeighbour)
{
    double particleDistance = std::sqrt( differenceParticleNeighbour.norm() );
    return -differenceParticleNeighbour / particleDistance;
}

// (Formula 4.56)
static SPHAlgorithms::Point3D calculateVelocity(SPHAlgorithms::Point3D particleVelocity,
                                                SPHAlgorithms::Point3D differenceParticleNeighbour)
{
    double scalarProduct = particleVelocity[0] * differenceParticleNeighbour[0] +
                           particleVelocity[1] * differenceParticleNeighbour[1] +
                           particleVelocity[2] * differenceParticleNeighbour[2];
    return particleVelocity - differenceParticleNeighbour * 2 * scalarProduct;
}

void Collision::detectCollisions(ParticleVect&                                    particleVect,
                                 const SPHAlgorithms::Volume&                     volume,
                                 const std::function<float(float, float, float)>* obstacle)
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

        if (particleVect[i].position[0] > cuboid.width - particleVect[i].radius)
        {
            particleVect[i].position[0] = cuboid.width - particleVect[i].radius;
            particleVect[i].velocity[0] *= Config::CollisionVelocityMultiplier;
        }

        if (particleVect[i].position[0] < particleVect[i].radius)
        {
            particleVect[i].position[0] = particleVect[i].radius;
            particleVect[i].velocity[0] *= Config::CollisionVelocityMultiplier;
        }

        if (particleVect[i].position[1] > cuboid.length - particleVect[i].radius)
        {
            particleVect[i].position[1] = cuboid.length - particleVect[i].radius;
            particleVect[i].velocity[1] *= Config::CollisionVelocityMultiplier;
        }

        if (particleVect[i].position[1] < particleVect[i].radius)
        {
            particleVect[i].position[1] = particleVect[i].radius;
            particleVect[i].velocity[1] *= Config::CollisionVelocityMultiplier;
        }

        if (particleVect[i].position[2] > cuboid.height - particleVect[i].radius)
        {
            particleVect[i].position[2] = cuboid.height - particleVect[i].radius;
            particleVect[i].velocity[2] *= Config::CollisionVelocityMultiplier;
        }

        if (particleVect[i].position[2] < particleVect[i].radius)
        {
            particleVect[i].position[2] = particleVect[i].radius;
            particleVect[i].velocity[2] *= Config::CollisionVelocityMultiplier;
        }

        /* Obstacle collision */

        if (obstacle != nullptr &&
            (*obstacle)(static_cast<float>(particleVect[i].position[0]),
                        static_cast<float>(particleVect[i].position[1]),
                        static_cast<float>(particleVect[i].position[2])) > 0.f)
        {
            particleVect[i].position = particleVect[i].previous_position;
            particleVect[i].velocity *= Config::CollisionVelocityMultiplier;
        }
    }
}
} // namespace SPHSDK
