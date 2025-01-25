/**
 * @file SPHTestSuite.cpp
 * @author Anton Artiukh
 * @date Created Jan 25, 2025
 **/

#include "SPHTestSuite.h"

#include "SPH.h"

#include <gtest/gtest.h>

namespace SPHSDK
{
namespace TestEnvironment
{

void SPHTestSuite::runSPH()
{
    SPHSDK::SPH sph;

    sph.run();

    EXPECT_EQ(Config::ParticlesNumber, sph.particles.size());
}

} // namespace TestEnvironment
} // namespace SPHSDK

using namespace SPHSDK::TestEnvironment;

TEST(SPHTestSuite, runSPH)
{
    SPHTestSuite::runSPH();
}