/**
 * @file CollisionsTestSuite.h
 * @author Anton Artyukh (artyukhanton@gmail.com)
 * @date Created May 28, 2017
 **/

#include "CollisionsTestSuite.h"

#include "Collisions.h"
#include "algorithms/src/Area.h"

#include <gtest/gtest.h>

namespace SPHSDK
{
namespace TestEnvironment
{

void CollisionsTestSuite::twoParticleCollision()
{
    ParticleVect particleVector = {Particle(SPHAlgorithms::Point3D(0.01, 0.01, 0.01), 0.1),
                                   Particle(SPHAlgorithms::Point3D(0.09, 0.09, 0.09), 0.1)};
    particleVector[0].velocity = SPHAlgorithms::Point3D(2.0, 2.0, 2.0);
    particleVector[1].velocity = SPHAlgorithms::Point3D(-2.0, -2.0, -2.0);
    particleVector[0].neighbours = {1};
    particleVector[1].neighbours = {0};
    SPHAlgorithms::Volume volume(SPHAlgorithms::Cuboid(SPHAlgorithms::Point3D(0.0, 0.0, 0.0), 1.0, 1.0, 1.0));

    Collision::detectCollisions(particleVector, volume);

    EXPECT_DOUBLE_EQ(0.1, particleVector[0].position.x);
    EXPECT_DOUBLE_EQ(0.1, particleVector[0].position.y);
    EXPECT_DOUBLE_EQ(0.1, particleVector[0].position.z);
    EXPECT_DOUBLE_EQ(0.1, particleVector[1].position.x);
    EXPECT_DOUBLE_EQ(0.1, particleVector[1].position.y);
    EXPECT_DOUBLE_EQ(0.1, particleVector[1].position.z);

    EXPECT_DOUBLE_EQ(-1, particleVector[0].velocity.x);
    EXPECT_DOUBLE_EQ(-1, particleVector[0].velocity.y);
    EXPECT_DOUBLE_EQ(-1, particleVector[0].velocity.z);
    EXPECT_DOUBLE_EQ(1, particleVector[1].velocity.x);
    EXPECT_DOUBLE_EQ(1, particleVector[1].velocity.y);
    EXPECT_DOUBLE_EQ(1, particleVector[1].velocity.z);
}

void CollisionsTestSuite::threeParticleCollision()
{
    ParticleVect particleVector = {Particle(SPHAlgorithms::Point3D(1.0, 1.0, 1.0), 1.6),
                                   Particle(SPHAlgorithms::Point3D(3.0, 1.0, 1.0), 1.6),
                                   Particle(SPHAlgorithms::Point3D(2.0, 2.0, 2.0), 1.6)};
    particleVector[0].velocity = SPHAlgorithms::Point3D(2.0, 2.0, 2.0);
    particleVector[1].velocity = SPHAlgorithms::Point3D(-2.0, 2.0, 2.0);
    particleVector[2].velocity = SPHAlgorithms::Point3D(0.0, -2.0, 0.0);
    particleVector[0].neighbours = {1, 2};
    particleVector[1].neighbours = {0, 2};
    particleVector[2].neighbours = {0, 1};

    SPHAlgorithms::Volume volume(SPHAlgorithms::Cuboid(SPHAlgorithms::Point3D(0.0, 0.0, 0.0), 4.0, 4.0, 4.0));

    Collision::detectCollisions(particleVector, volume);

    EXPECT_DOUBLE_EQ(1.6, particleVector[0].position.x);
    EXPECT_DOUBLE_EQ(1.6, particleVector[0].position.y);
    EXPECT_DOUBLE_EQ(1.6, particleVector[0].position.z);
    EXPECT_DOUBLE_EQ(2.4, particleVector[1].position.x);
    EXPECT_DOUBLE_EQ(1.6, particleVector[1].position.y);
    EXPECT_DOUBLE_EQ(1.6, particleVector[1].position.z);
    EXPECT_DOUBLE_EQ(2.0, particleVector[2].position.x);
    EXPECT_DOUBLE_EQ(2.0, particleVector[2].position.y);
    EXPECT_DOUBLE_EQ(2.0, particleVector[2].position.z);

    EXPECT_DOUBLE_EQ(-1.0, particleVector[0].velocity.x);
    EXPECT_DOUBLE_EQ(-1.0, particleVector[0].velocity.y);
    EXPECT_DOUBLE_EQ(-1.0, particleVector[0].velocity.z);
    EXPECT_DOUBLE_EQ(1.0, particleVector[1].velocity.x);
    EXPECT_DOUBLE_EQ(-1.0, particleVector[1].velocity.y);
    EXPECT_DOUBLE_EQ(-1.0, particleVector[1].velocity.z);
    EXPECT_DOUBLE_EQ(0.0, particleVector[2].velocity.x);
    EXPECT_DOUBLE_EQ(-2.0, particleVector[2].velocity.y);
    EXPECT_DOUBLE_EQ(0.0, particleVector[2].velocity.z);
}

void CollisionsTestSuite::fourParticleCollision()
{
    ParticleVect particleVector = {
        Particle(SPHAlgorithms::Point3D(1.0, 1.0, 1.0), 1.6), Particle(SPHAlgorithms::Point3D(3.0, 1.0, 1.0), 1.6),
        Particle(SPHAlgorithms::Point3D(1.0, 3.0, 1.0), 1.6), Particle(SPHAlgorithms::Point3D(3.0, 3.0, 3.0), 1.6)};
    particleVector[0].velocity = SPHAlgorithms::Point3D(2.0, 2.0, 2.0);
    particleVector[1].velocity = SPHAlgorithms::Point3D(-2.0, 2.0, 2.0);
    particleVector[2].velocity = SPHAlgorithms::Point3D(2.0, -2.0, 2.0);
    particleVector[3].velocity = SPHAlgorithms::Point3D(-2.0, -2.0, 2.0);
    particleVector[0].neighbours = {1, 2, 3};
    particleVector[1].neighbours = {0, 2, 3};
    particleVector[2].neighbours = {0, 1, 3};
    particleVector[3].neighbours = {0, 1, 2};

    SPHAlgorithms::Volume volume(SPHAlgorithms::Cuboid(SPHAlgorithms::Point3D(0.0, 0.0, 0.0), 4.0, 4.0, 4.0));

    Collision::detectCollisions(particleVector, volume);

    EXPECT_DOUBLE_EQ(1.6, particleVector[0].position.x);
    EXPECT_DOUBLE_EQ(1.6, particleVector[0].position.y);
    EXPECT_DOUBLE_EQ(1.6, particleVector[0].position.z);
    EXPECT_DOUBLE_EQ(2.4, particleVector[1].position.x);
    EXPECT_DOUBLE_EQ(1.6, particleVector[1].position.y);
    EXPECT_DOUBLE_EQ(1.6, particleVector[1].position.z);
    EXPECT_DOUBLE_EQ(1.6, particleVector[2].position.x);
    EXPECT_DOUBLE_EQ(2.4, particleVector[2].position.y);
    EXPECT_DOUBLE_EQ(1.6, particleVector[2].position.z);
    EXPECT_DOUBLE_EQ(2.4, particleVector[3].position.x);
    EXPECT_DOUBLE_EQ(2.4, particleVector[3].position.y);
    EXPECT_DOUBLE_EQ(2.4, particleVector[3].position.z);

    EXPECT_DOUBLE_EQ(-1.0, particleVector[0].velocity.x);
    EXPECT_DOUBLE_EQ(-1.0, particleVector[0].velocity.y);
    EXPECT_DOUBLE_EQ(-1.0, particleVector[0].velocity.z);
    EXPECT_DOUBLE_EQ(1.0, particleVector[1].velocity.x);
    EXPECT_DOUBLE_EQ(-1.0, particleVector[1].velocity.y);
    EXPECT_DOUBLE_EQ(-1.0, particleVector[1].velocity.z);
    EXPECT_DOUBLE_EQ(-1.0, particleVector[2].velocity.x);
    EXPECT_DOUBLE_EQ(1.0, particleVector[2].velocity.y);
    EXPECT_DOUBLE_EQ(-1.0, particleVector[2].velocity.z);
    EXPECT_DOUBLE_EQ(1.0, particleVector[3].velocity.x);
    EXPECT_DOUBLE_EQ(1.0, particleVector[3].velocity.y);
    EXPECT_DOUBLE_EQ(-1.0, particleVector[3].velocity.z);
}

void CollisionsTestSuite::twoAndTwoParticleCollision()
{
    ParticleVect particleVector = {
        Particle(SPHAlgorithms::Point3D(1.0, 1.0, 1.0), 0.55), Particle(SPHAlgorithms::Point3D(1.5, 1.0, 1.0), 0.55),
        Particle(SPHAlgorithms::Point3D(1.0, 3.0, 3.0), 0.55), Particle(SPHAlgorithms::Point3D(1.5, 3.0, 3.0), 0.55)};
    particleVector[0].velocity = SPHAlgorithms::Point3D(2.0, 0.0, 1.0);
    particleVector[1].velocity = SPHAlgorithms::Point3D(-2.0, 0.0, 1.0);
    particleVector[2].velocity = SPHAlgorithms::Point3D(2.0, 0.0, 1.0);
    particleVector[3].velocity = SPHAlgorithms::Point3D(-2.0, 0.0, 1.0);
    particleVector[0].neighbours = {1, 2, 3};
    particleVector[1].neighbours = {0, 2, 3};
    particleVector[2].neighbours = {0, 1, 3};
    particleVector[3].neighbours = {0, 1, 2};

    SPHAlgorithms::Volume volume(SPHAlgorithms::Cuboid(SPHAlgorithms::Point3D(0.0, 0.0, 1.0), 4.0, 4.0, 1.0));

    Collision::detectCollisions(particleVector, volume);

    EXPECT_DOUBLE_EQ(2.0, particleVector[0].velocity.x);
    EXPECT_DOUBLE_EQ(0.0, particleVector[0].velocity.y);
    EXPECT_DOUBLE_EQ(0.25, particleVector[0].velocity.z);
    EXPECT_DOUBLE_EQ(-2.0, particleVector[1].velocity.x);
    EXPECT_DOUBLE_EQ(0.0, particleVector[1].velocity.y);
    EXPECT_DOUBLE_EQ(0.25, particleVector[1].velocity.z);
    EXPECT_DOUBLE_EQ(2.0, particleVector[2].velocity.x);
    EXPECT_DOUBLE_EQ(0.0, particleVector[2].velocity.y);
    EXPECT_DOUBLE_EQ(0.25, particleVector[2].velocity.z);
    EXPECT_DOUBLE_EQ(-2.0, particleVector[3].velocity.x);
    EXPECT_DOUBLE_EQ(0.0, particleVector[3].velocity.y);
    EXPECT_DOUBLE_EQ(0.25, particleVector[3].velocity.z);
}

void CollisionsTestSuite::oneAndFiveParticleCollision()
{
    ParticleVect particleVector = {
        Particle(SPHAlgorithms::Point3D(1.0, 1.0, 1.0), 0.12), Particle(SPHAlgorithms::Point3D(1.1, 1.0, 1.0), 0.12),
        Particle(SPHAlgorithms::Point3D(1.2, 1.0, 1.0), 0.12), Particle(SPHAlgorithms::Point3D(1.3, 1.0, 1.0), 0.12),
        Particle(SPHAlgorithms::Point3D(1.4, 1.0, 1.0), 0.12), Particle(SPHAlgorithms::Point3D(1.5, 1.0, 1.0), 0.12)};
    particleVector[0].velocity = SPHAlgorithms::Point3D(0.0, 0.0, 1.0);
    particleVector[1].velocity = SPHAlgorithms::Point3D(0.0, 0.0, 1.0);
    particleVector[2].velocity = SPHAlgorithms::Point3D(0.0, 0.0, 1.0);
    particleVector[3].velocity = SPHAlgorithms::Point3D(0.0, 0.0, 1.0);
    particleVector[4].velocity = SPHAlgorithms::Point3D(0.0, 0.0, 1.0);
    particleVector[5].velocity = SPHAlgorithms::Point3D(-1.0, 0.0, 1.0);
    particleVector[0].neighbours = {1};
    particleVector[1].neighbours = {0, 2};
    particleVector[2].neighbours = {1, 3};
    particleVector[3].neighbours = {2, 4};
    particleVector[4].neighbours = {3, 5};
    particleVector[5].neighbours = {4};

    SPHAlgorithms::Volume volume(SPHAlgorithms::Cuboid(SPHAlgorithms::Point3D(0.0, 0.0, 1.0), 4.0, 4.0, 1.0));

    Collision::detectCollisions(particleVector, volume);

    EXPECT_DOUBLE_EQ(0.0, particleVector[0].velocity.x);
    EXPECT_DOUBLE_EQ(0.0, particleVector[0].velocity.y);
    EXPECT_DOUBLE_EQ(-0.5, particleVector[0].velocity.z);
    EXPECT_DOUBLE_EQ(0.0, particleVector[1].velocity.x);
    EXPECT_DOUBLE_EQ(0.0, particleVector[1].velocity.y);
    EXPECT_DOUBLE_EQ(-0.5, particleVector[1].velocity.z);
    EXPECT_DOUBLE_EQ(0.0, particleVector[2].velocity.x);
    EXPECT_DOUBLE_EQ(0.0, particleVector[2].velocity.y);
    EXPECT_DOUBLE_EQ(-0.5, particleVector[2].velocity.z);
    EXPECT_DOUBLE_EQ(0.0, particleVector[3].velocity.x);
    EXPECT_DOUBLE_EQ(0.0, particleVector[3].velocity.y);
    EXPECT_DOUBLE_EQ(-0.5, particleVector[3].velocity.z);
    EXPECT_DOUBLE_EQ(0.0, particleVector[4].velocity.x);
    EXPECT_DOUBLE_EQ(0.0, particleVector[4].velocity.y);
    EXPECT_DOUBLE_EQ(-0.5, particleVector[4].velocity.z);
    EXPECT_DOUBLE_EQ(-1.0, particleVector[5].velocity.x);
    EXPECT_DOUBLE_EQ(0.0, particleVector[5].velocity.y);
    EXPECT_DOUBLE_EQ(-0.5, particleVector[5].velocity.z);
}

void CollisionsTestSuite::oneAndFourParticleCollision()
{
    ParticleVect particleVector = {
        Particle(SPHAlgorithms::Point3D(1.0, 1.0, 1.0), 0.12), Particle(SPHAlgorithms::Point3D(1.1, 1.0, 1.0), 0.12),
        Particle(SPHAlgorithms::Point3D(1.2, 1.0, 1.0), 0.12), Particle(SPHAlgorithms::Point3D(1.3, 1.0, 1.0), 0.12),
        Particle(SPHAlgorithms::Point3D(1.25, 1.1, 1.0), 0.12)};
    particleVector[0].velocity = SPHAlgorithms::Point3D(0.0, 0.0, 1.0);
    particleVector[1].velocity = SPHAlgorithms::Point3D(0.0, 0.0, 1.0);
    particleVector[2].velocity = SPHAlgorithms::Point3D(0.0, 0.0, 1.0);
    particleVector[3].velocity = SPHAlgorithms::Point3D(0.0, 0.0, 1.0);
    particleVector[4].velocity = SPHAlgorithms::Point3D(0.0, 5.0, 1.0);
    particleVector[0].neighbours = {1};
    particleVector[1].neighbours = {0, 2, 4};
    particleVector[2].neighbours = {1, 3, 4};
    particleVector[3].neighbours = {2};
    particleVector[4].neighbours = {1, 2};

    SPHAlgorithms::Volume volume(SPHAlgorithms::Cuboid(SPHAlgorithms::Point3D(0.0, 0.0, 1.0), 4.0, 4.0, 1.0));

    Collision::detectCollisions(particleVector, volume);

    EXPECT_DOUBLE_EQ(0.0, particleVector[0].velocity.x);
    EXPECT_DOUBLE_EQ(0.0, particleVector[0].velocity.y);
    EXPECT_DOUBLE_EQ(-0.5, particleVector[0].velocity.z);
    EXPECT_DOUBLE_EQ(0.0, particleVector[1].velocity.x);
    EXPECT_DOUBLE_EQ(0.0, particleVector[1].velocity.y);
    EXPECT_DOUBLE_EQ(-0.5, particleVector[1].velocity.z);
    EXPECT_DOUBLE_EQ(0.0, particleVector[2].velocity.x);
    EXPECT_DOUBLE_EQ(0.0, particleVector[2].velocity.y);
    EXPECT_DOUBLE_EQ(-0.5, particleVector[2].velocity.z);
    EXPECT_DOUBLE_EQ(0.0, particleVector[3].velocity.x);
    EXPECT_DOUBLE_EQ(0.0, particleVector[3].velocity.y);
    EXPECT_DOUBLE_EQ(-0.5, particleVector[3].velocity.z);
    EXPECT_DOUBLE_EQ(0.0, particleVector[4].velocity.x);
    EXPECT_DOUBLE_EQ(5.0, particleVector[4].velocity.y);
    EXPECT_DOUBLE_EQ(-0.5, particleVector[4].velocity.z);
}

void CollisionsTestSuite::oneAndEightParticleCollision()
{
    ParticleVect particleVector = {
        Particle(SPHAlgorithms::Point3D(1.0, 1.0, 1.0), 0.51), Particle(SPHAlgorithms::Point3D(0.75, 1.25, 1.0), 0.51),
        Particle(SPHAlgorithms::Point3D(0.5, 1.5, 1.0), 0.51), Particle(SPHAlgorithms::Point3D(0.75, 1.75, 1.0), 0.51),
        Particle(SPHAlgorithms::Point3D(1.0, 2.0, 1.0), 0.51), Particle(SPHAlgorithms::Point3D(1.25, 1.75, 1.0), 0.51),
        Particle(SPHAlgorithms::Point3D(1.5, 1.5, 1.0), 0.51), Particle(SPHAlgorithms::Point3D(1.25, 1.25, 1.0), 0.51),
        Particle(SPHAlgorithms::Point3D(1.0, 1.5, 1.0), 0.51)};
    particleVector[0].velocity = SPHAlgorithms::Point3D(0.0, 1.0, 1.0);
    particleVector[1].velocity = SPHAlgorithms::Point3D(1.0, 1.0, 1.0);
    particleVector[2].velocity = SPHAlgorithms::Point3D(1.0, 0.0, 1.0);
    particleVector[3].velocity = SPHAlgorithms::Point3D(1.0, -1.0, 1.0);
    particleVector[4].velocity = SPHAlgorithms::Point3D(0.0, -1.0, 1.0);
    particleVector[5].velocity = SPHAlgorithms::Point3D(-1.0, -1.0, 1.0);
    particleVector[6].velocity = SPHAlgorithms::Point3D(-1.0, 0.0, 1.0);
    particleVector[7].velocity = SPHAlgorithms::Point3D(-1.0, 1.0, 1.0);
    particleVector[8].velocity = SPHAlgorithms::Point3D(0.0, 0.0, 1.0);
    particleVector[0].neighbours = {1, 7, 8};
    particleVector[1].neighbours = {0, 2, 8};
    particleVector[2].neighbours = {1, 3, 8};
    particleVector[3].neighbours = {2, 4, 8};
    particleVector[4].neighbours = {3, 5, 8};
    particleVector[5].neighbours = {4, 6, 8};
    particleVector[6].neighbours = {5, 7, 8};
    particleVector[7].neighbours = {0, 6, 8};
    particleVector[8].neighbours = {0, 1, 2, 3, 4, 5, 6, 7};

    SPHAlgorithms::Volume volume(SPHAlgorithms::Cuboid(SPHAlgorithms::Point3D(0.0, 0.0, 0.0), 4.0, 4.0, 1.0));

    Collision::detectCollisions(particleVector, volume);

    EXPECT_DOUBLE_EQ(0, particleVector[0].velocity.x);
    EXPECT_DOUBLE_EQ(1.0, particleVector[0].velocity.y);
    EXPECT_DOUBLE_EQ(0.25, particleVector[0].velocity.z);
    EXPECT_DOUBLE_EQ(1.0, particleVector[1].velocity.x);
    EXPECT_DOUBLE_EQ(1.0, particleVector[1].velocity.y);
    EXPECT_DOUBLE_EQ(0.25, particleVector[1].velocity.z);
    EXPECT_DOUBLE_EQ(-0.5, particleVector[2].velocity.x);
    EXPECT_DOUBLE_EQ(0.0, particleVector[2].velocity.y);
    EXPECT_DOUBLE_EQ(0.25, particleVector[2].velocity.z);
    EXPECT_DOUBLE_EQ(1.0, particleVector[3].velocity.x);
    EXPECT_DOUBLE_EQ(-1.0, particleVector[3].velocity.y);
    EXPECT_DOUBLE_EQ(0.25, particleVector[3].velocity.z);
    EXPECT_DOUBLE_EQ(0.0, particleVector[4].velocity.x);
    EXPECT_DOUBLE_EQ(-1.0, particleVector[4].velocity.y);
    EXPECT_DOUBLE_EQ(0.25, particleVector[4].velocity.z);
    EXPECT_DOUBLE_EQ(-1.0, particleVector[5].velocity.x);
    EXPECT_DOUBLE_EQ(-1.0, particleVector[5].velocity.y);
    EXPECT_DOUBLE_EQ(0.25, particleVector[5].velocity.z);
    EXPECT_DOUBLE_EQ(-1.0, particleVector[6].velocity.x);
    EXPECT_DOUBLE_EQ(0.0, particleVector[6].velocity.y);
    EXPECT_DOUBLE_EQ(0.25, particleVector[6].velocity.z);
    EXPECT_DOUBLE_EQ(-1.0, particleVector[7].velocity.x);
    EXPECT_DOUBLE_EQ(1.0, particleVector[7].velocity.y);
    EXPECT_DOUBLE_EQ(0.25, particleVector[7].velocity.z);
    EXPECT_DOUBLE_EQ(0.0, particleVector[8].velocity.x);
    EXPECT_DOUBLE_EQ(0.0, particleVector[8].velocity.y);
    EXPECT_DOUBLE_EQ(0.25, particleVector[8].velocity.z);
}

void CollisionsTestSuite::oneOnBoundaryParticleCollision()
{
    ParticleVect particleVector = {Particle(SPHAlgorithms::Point3D(-9.83, -0.003716, -1.0), 0.1)};
    particleVector[0].velocity = SPHAlgorithms::Point3D(-0.5, -7.0, -1.0);
    SPHAlgorithms::Volume volume(SPHAlgorithms::Cuboid(SPHAlgorithms::Point3D(0.0, 0.0, -1.0), 10.0, 10.0, 10.0));

    Collision::detectCollisions(particleVector, volume);

    EXPECT_DOUBLE_EQ(0.1, particleVector[0].position.x);
    EXPECT_DOUBLE_EQ(0.1, particleVector[0].position.y);
    EXPECT_DOUBLE_EQ(0.1, particleVector[0].position.z);

    EXPECT_DOUBLE_EQ(0.25, particleVector[0].velocity.x);
    EXPECT_DOUBLE_EQ(3.5, particleVector[0].velocity.y);
    EXPECT_DOUBLE_EQ(0.5, particleVector[0].velocity.z);
}

void CollisionsTestSuite::twoOnBoundaryParticleCollision()
{
    ParticleVect particleVector = {Particle(SPHAlgorithms::Point3D(0.0, -0.5, 1.0), 0.1),
                                   Particle(SPHAlgorithms::Point3D(0.01, -0.5, 1.0), 0.1)};
    particleVector[0].velocity = SPHAlgorithms::Point3D(1.0, -1.0, 1.0);
    particleVector[1].velocity = SPHAlgorithms::Point3D(-1.0, -1.0, 1.0);
    particleVector[0].neighbours = {1};
    particleVector[1].neighbours = {0};

    SPHAlgorithms::Volume volume(SPHAlgorithms::Cuboid(SPHAlgorithms::Point3D(0.0, 0.0, 0.0), 2.0, 2.0, 2.0));

    Collision::detectCollisions(particleVector, volume);

    EXPECT_DOUBLE_EQ(0.5, particleVector[0].velocity.x);
    EXPECT_DOUBLE_EQ(0.5, particleVector[0].velocity.y);
    EXPECT_DOUBLE_EQ(1.0, particleVector[0].velocity.z);
    EXPECT_DOUBLE_EQ(0.5, particleVector[1].velocity.x);
    EXPECT_DOUBLE_EQ(0.5, particleVector[1].velocity.y);
    EXPECT_DOUBLE_EQ(1.0, particleVector[1].velocity.z);
}

void CollisionsTestSuite::threeOnBoundaryParticleCollision()
{
    ParticleVect particleVector = {Particle(SPHAlgorithms::Point3D(-0.1, 0.0, 1.0), 0.1),
                                   Particle(SPHAlgorithms::Point3D(-0.1, 0.2, 1.0), 0.1),
                                   Particle(SPHAlgorithms::Point3D(-0.1, 0.4, 1.0), 0.1)};
    particleVector[0].velocity = SPHAlgorithms::Point3D(-1.0, 0.0, 1.0);
    particleVector[1].velocity = SPHAlgorithms::Point3D(-1.0, 0.0, 1.0);
    particleVector[2].velocity = SPHAlgorithms::Point3D(-1.0, 0.0, 1.0);

    SPHAlgorithms::Volume volume(SPHAlgorithms::Cuboid(SPHAlgorithms::Point3D(0.0, 0.0, 0.0), 2.0, 2.0, 2.0));

    Collision::detectCollisions(particleVector, volume);

    EXPECT_DOUBLE_EQ(0.5, particleVector[0].velocity.x);
    EXPECT_DOUBLE_EQ(0.0, particleVector[0].velocity.y);
    EXPECT_DOUBLE_EQ(1.0, particleVector[0].velocity.z);
    EXPECT_DOUBLE_EQ(0.5, particleVector[1].velocity.x);
    EXPECT_DOUBLE_EQ(0.0, particleVector[1].velocity.y);
    EXPECT_DOUBLE_EQ(1.0, particleVector[1].velocity.z);
    EXPECT_DOUBLE_EQ(0.5, particleVector[2].velocity.x);
    EXPECT_DOUBLE_EQ(0.0, particleVector[2].velocity.y);
    EXPECT_DOUBLE_EQ(1.0, particleVector[2].velocity.z);
}

} // namespace TestEnvironment
} // namespace SPHSDK

using namespace SPHSDK::TestEnvironment;

TEST(CollisionsTestSuite, twoParticleCollision)
{
    CollisionsTestSuite::twoParticleCollision();
}

TEST(CollisionsTestSuite, threeParticleCollision)
{
    CollisionsTestSuite::threeParticleCollision();
}

TEST(CollisionsTestSuite, fourParticleCollision)
{
    CollisionsTestSuite::fourParticleCollision();
}

TEST(CollisionsTestSuite, twoAndTwoParticleCollision)
{
    CollisionsTestSuite::twoAndTwoParticleCollision();
}

TEST(CollisionsTestSuite, oneAndFiveParticleCollision)
{
    CollisionsTestSuite::oneAndFiveParticleCollision();
}

TEST(CollisionsTestSuite, oneAndFourParticleCollision)
{
    CollisionsTestSuite::oneAndFourParticleCollision();
}

TEST(CollisionsTestSuite, oneAndEightParticleCollision)
{
    CollisionsTestSuite::oneAndEightParticleCollision();
}

TEST(CollisionsTestSuite, oneOnBoundaryParticleCollision)
{
    CollisionsTestSuite::oneOnBoundaryParticleCollision();
}

TEST(CollisionsTestSuite, twoOnBoundaryParticleCollision)
{
    CollisionsTestSuite::twoOnBoundaryParticleCollision();
}

TEST(CollisionsTestSuite, threeOnBoundaryParticleCollision)
{
    CollisionsTestSuite::threeOnBoundaryParticleCollision();
}
