/**
 * @file CollisionsTestSuite.h
 * @author Anton Artyukh (artyukhanton@gmail.com)
 * @date Created May 28, 2017
 **/

#ifndef COLLISIONS_TEST_SUITE_H_96192C2023784EE0B4976A48A1A8779B
#define COLLISIONS_TEST_SUITE_H_96192C2023784EE0B4976A48A1A8779B

namespace SPHSDK
{

namespace TestEnvironment
{

class CollisionsTestSuite
{
public:
    static void twoParticleCollision();

    static void threeParticleCollision();

    static void fourParticleCollision();

    static void twoAndTwoParticleCollision();

    static void oneAndFiveParticleCollision();

    static void oneAndFourParticleCollision();

    static void oneAndEightParticleCollision();

    static void oneOnBoundaryParticleCollision();

    static void twoOnBoundaryParticleCollision();

    static void threeOnBoundaryParticleCollision();
};

} // namespace TestEnvironment
} // namespace SPHSDK

#endif // COLLISIONS_TEST_SUITE_H_96192C2023784EE0B4976A48A1A8779B
