/**
 * @file ParticleTestSuite.h
 * @author Anton Artyukh (artyukhanton@gmail.com)
 * @date Created May 31, 2017
 **/

#ifndef FORCES_TEST_SUITE_H_96192C2023784EE0B4976A48A1A8779B
#define FORCES_TEST_SUITE_H_96192C2023784EE0B4976A48A1A8779B

namespace SPHSDK
{

namespace TestEnvironment
{

class ForcesTestSuite
{
public:
    static void densityForOneNeighbour();

    static void densityForTwoNeighbours();

    static void densityForThreeNeighbours();

    static void densityForFourNeighbours();

    static void pressureForOneNeighbour();

    static void pressureForTwoNeighbours();

    static void pressureForThreeNeighbours();

    static void pressureForFourNeighbours();

    static void internalForcesForOneNeighbour();

    static void internalForcesForTwoNeighbours();

    static void internalForcesForThreeNeighbours();

    static void internalForcesForFourNeighbours();

    static void externalForcesForOneNeighbour();

    static void externalForcesForTwoNeighbours();

    static void externalForcesForThreeNeighbours();

    static void externalForcesForFourNeighbours();

    static void externalForcesForFiveNeighbours();

    static void allForcesForOneNeighbour();

    static void allForcesForTwoNeighbours();

    static void allForcesForThreeNeighbours();
};

} // namespace TestEnvironment
} // namespace SPHSDK

#endif // PARTICLE_TEST_SUITE_H_96192C2023784EE0B4976A48A1A8779B
