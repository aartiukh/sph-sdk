/**
 * @file ParticleTestSuite.h
 * @author Anton Artyukh (artyukhanton@gmail.com)
 * @date Created May 21, 2017
 **/

#include "ParticleTestSuite.h"

#include "Particle.h"

#include <gtest/gtest.h>

namespace SPHSDK
{
namespace TestEnvironment
{

void ParticleTestSuite::particleIsValid()
{
    Particle particle(SPHAlgorithms::Point3D(5.0, -6.0, 1.0), 0.1);

    EXPECT_DOUBLE_EQ(5.0, particle.position.x);
    EXPECT_DOUBLE_EQ(-6.0, particle.position.y);
    EXPECT_DOUBLE_EQ(1.0, particle.position.z);
    EXPECT_DOUBLE_EQ(0.1, particle.radius);
    EXPECT_DOUBLE_EQ(0.0, particle.velocity.x);
    EXPECT_DOUBLE_EQ(0.0, particle.velocity.y);
    EXPECT_DOUBLE_EQ(0.0, particle.velocity.z);
    EXPECT_DOUBLE_EQ(0.0, particle.density);
    EXPECT_DOUBLE_EQ(0.0, particle.pressure);
}

} // namespace TestEnvironment
} // namespace SPHSDK

using namespace SPHSDK::TestEnvironment;

TEST(ParticleTestSuite, particleIsValid)
{
    ParticleTestSuite::particleIsValid();
}
