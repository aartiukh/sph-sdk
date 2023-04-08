#include "Collisions.h"

#include "Config.h"
#include "algorithms/src/Area.h"


namespace SPHSDK
{

// (Formula 4.35)
static FLOAT calculateF(const Point3F& differenceParticleNeighbour)
{
    return differenceParticleNeighbour.calcNormSqr() - Config::ParticleRadius * Config::ParticleRadius;
}

// (Formula 4.36)
static Point3F calculateContactPoint(const Point3F& particlePosition,
                                     const Point3F& differenceParticleNeighbour)
{
    const FLOAT particleDistance = differenceParticleNeighbour.calcNorm();
    return particlePosition + (differenceParticleNeighbour / particleDistance) * Config::ParticleRadius;
}

// (Formula 4.38)
static Point3F calculateSurfaceNormal(const Point3F& differenceParticleNeighbour)
{
    const FLOAT particleDistance = differenceParticleNeighbour.calcNorm();
    return -differenceParticleNeighbour / particleDistance;
}

// (Formula 4.56)
static Point3F calculateVelocity(const Point3F& particleVelocity,
                                 const Point3F& differenceParticleNeighbour)
{
    const FLOAT scalarProduct = particleVelocity.x * differenceParticleNeighbour.x +
                                particleVelocity.y * differenceParticleNeighbour.y +
                                particleVelocity.z * differenceParticleNeighbour.z;
    return particleVelocity - differenceParticleNeighbour * 2 * scalarProduct;
}

void Collision::detectCollisions(ParticleVect&                                    particleVect,
                                 const Volume&                                    volume,
                                 const std::function<FLOAT(FLOAT, FLOAT, FLOAT)>* obstacle)
{
    for (size_t i = 0; i < particleVect.size(); i++)
    {
        /* Particle Collision */

        for (size_t j = 0; j < particleVect[i].neighbours.size(); j++)
        {
            Point3F differenceParticleNeighbour =
                particleVect[i].position - particleVect[particleVect[i].neighbours[j]].position;

            // (Formula 4.35)
            if (calculateF(differenceParticleNeighbour) < 0)
            {
                const Point3 surfaceNormal = calculateSurfaceNormal(differenceParticleNeighbour);

                // (Formula 4.55)
                particleVect[i].position = calculateContactPoint(particleVect[i].position, differenceParticleNeighbour);

                // (Formula 4.56)
                particleVect[i].velocity = calculateVelocity(particleVect[i].velocity, surfaceNormal);
            }
        }

        /* Boundary Collision */

        const Cuboid cuboid = volume.getBoundingCuboid();

        if (particleVect[i].position.x > cuboid.width - particleVect[i].radius)
        {
            particleVect[i].position.x = cuboid.width - particleVect[i].radius;
            particleVect[i].velocity.x *= Config::CollisionVelocityMultiplier;
        }

        if (particleVect[i].position.x < particleVect[i].radius)
        {
            particleVect[i].position.x = particleVect[i].radius;
            particleVect[i].velocity.x *= Config::CollisionVelocityMultiplier;
        }

        if (particleVect[i].position.y > cuboid.length - particleVect[i].radius)
        {
            particleVect[i].position.y = cuboid.length - particleVect[i].radius;
            particleVect[i].velocity.y *= Config::CollisionVelocityMultiplier;
        }

        if (particleVect[i].position.y < particleVect[i].radius)
        {
            particleVect[i].position.y = particleVect[i].radius;
            particleVect[i].velocity.y *= Config::CollisionVelocityMultiplier;
        }

        if (particleVect[i].position.z > cuboid.height - particleVect[i].radius)
        {
            particleVect[i].position.z = cuboid.height - particleVect[i].radius;
            particleVect[i].velocity.z *= Config::CollisionVelocityMultiplier;
        }

        if (particleVect[i].position.z < particleVect[i].radius)
        {
            particleVect[i].position.z = particleVect[i].radius;
            particleVect[i].velocity.z *= Config::CollisionVelocityMultiplier;
        }

        /* Obstacle collision */

        if (obstacle != nullptr &&
            (*obstacle)(static_cast<FLOAT>(particleVect[i].position.x), static_cast<FLOAT>(particleVect[i].position.y),
                        static_cast<FLOAT>(particleVect[i].position.z)) > 0.f)
        {
            particleVect[i].position = particleVect[i].previous_position;
            particleVect[i].velocity *= Config::CollisionVelocityMultiplier;
        }
    }
}
} // namespace SPHSDK
