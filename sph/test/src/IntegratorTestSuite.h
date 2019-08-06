/**
 * @file IntegratorTestSuite.h
 * @author Anton Artyukh (artyukhanton@gmail.com)
 * @date Created June 11, 2017
 **/

#ifndef INTEGRATOR_TEST_SUITE_H_96192C2023784EE0B4976A48A1A8779B
#define INTEGRATOR_TEST_SUITE_H_96192C2023784EE0B4976A48A1A8779B

namespace SPHSDK
{

namespace TestEnvironment
{

class IntegratorTestSuite
{
public:
    static void oneParticleWithZeroVelocity();

    static void oneParticleWithZeroDensity();
};

} // namespace TestEnvironment
} // namespace SPHSDK

#endif // INTEGRATOR_TEST_SUITE_H_96192C2023784EE0B4976A48A1A8779B
