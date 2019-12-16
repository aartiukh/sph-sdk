/**
 * @file IntegratorTestSuite.cpp
 * @author Anton Artyukh (artyukhanton@gmail.com)
 * @date Created June 11, 2017
 **/

#include "IntegratorTestSuite.h"

#include "Integrator.h"

#include <gtest/gtest.h>

namespace SPHSDK
{
namespace TestEnvironment
{

void IntegratorTestSuite::oneParticleWithZeroVelocity()
{
    ParticleVect particles = { Particle(SPHAlgorithms::Point3D{0., 1., 1.}, 0.1) };
    particles[0].density = 0.5;
    particles[0].fTotal = SPHAlgorithms::Point3D{0.25, 0.25, 0.25};
    particles[0].acceleration = SPHAlgorithms::Point3D{0.1, 0.1, 0.1};

    Integrator::integrate(0.01, particles);

    EXPECT_DOUBLE_EQ(0.003, particles[0].velocity[0]);
    EXPECT_DOUBLE_EQ(0.003, particles[0].velocity[1]);
    EXPECT_DOUBLE_EQ(0.003, particles[0].velocity[2]);
    EXPECT_DOUBLE_EQ(5.0e-06, particles[0].position[0]);
    EXPECT_DOUBLE_EQ(1.000005, particles[0].position[1]);
    EXPECT_DOUBLE_EQ(1.000005, particles[0].position[2]);
}

void IntegratorTestSuite::oneParticleWithZeroDensity()
{
    ParticleVect particles = {Particle(SPHAlgorithms::Point3D{0., 1., 1.0}, 0.1)};
    particles[0].fTotal = SPHAlgorithms::Point3D{0.25, 0.25, 0.25};
    particles[0].acceleration = SPHAlgorithms::Point3D{0.1, 0.1, 0.1};

    Integrator::integrate(0.01, particles);

    EXPECT_DOUBLE_EQ(0.1, particles[0].acceleration[0]);
    EXPECT_DOUBLE_EQ(0.1, particles[0].acceleration[1]);
    EXPECT_DOUBLE_EQ(0.1, particles[0].acceleration[2]);
    EXPECT_DOUBLE_EQ(0.001, particles[0].velocity[0]);
    EXPECT_DOUBLE_EQ(0.001, particles[0].velocity[1]);
    EXPECT_DOUBLE_EQ(0.001, particles[0].velocity[2]);
    EXPECT_DOUBLE_EQ(5.0e-06, particles[0].position[0]);
    EXPECT_DOUBLE_EQ(1.000005, particles[0].position[1]);
    EXPECT_DOUBLE_EQ(1.000005, particles[0].position[2]);
}

} // namespace TestEnvironment
} // namespace SPHSDK

using namespace SPHSDK::TestEnvironment;

TEST(IntegratorTestSuite, oneParticleWithZeroVelocity)
{
    IntegratorTestSuite::oneParticleWithZeroVelocity();
}

TEST(IntegratorTestSuite, oneParticleWithZeroDensity)
{
    IntegratorTestSuite::oneParticleWithZeroDensity();
}
