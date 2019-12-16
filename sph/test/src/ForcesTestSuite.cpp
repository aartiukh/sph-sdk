/**
 * @file ParticleTestSuite.h
 * @author Anton Artyukh (artyukhanton@gmail.com)
 * @date Created May 31, 2017
 **/

#include "ForcesTestSuite.h"
#include "algorithms/src/Area.h"
#include "algorithms/src/NeighboursSearch.h"

#include "Forces.h"

#include <gtest/gtest.h>

namespace SPHSDK
{
namespace TestEnvironment
{

static const double Precision = 1e-07;
static const size_t numberOfParticles = 5;

ParticleVect generalParticleVect = {};

static void initGeneralParticles()
{
    generalParticleVect.resize(numberOfParticles);

    for (size_t i = 0; i < numberOfParticles; ++i)
    {
        generalParticleVect[i] = Particle(SPHAlgorithms::Point3D{0.5 + 0.01 * i, 0.5 + 0.01 * i, 0.5 + 0.01 * i}, 0.01);
        generalParticleVect[i].mass = Config::WaterParticleMass;
        generalParticleVect[i].supportRadius = Config::WaterSupportRadius;
    }

    generalParticleVect[0].velocity = SPHAlgorithms::Point3D{1.0, 1.0, 1.0};
    generalParticleVect[1].velocity = SPHAlgorithms::Point3D{0.5, 0.5, 0.5};
    generalParticleVect[2].velocity = SPHAlgorithms::Point3D{0.01, 0.01, 0.01};
    generalParticleVect[3].velocity = SPHAlgorithms::Point3D{-0.5, -0.5, -0.5};
    generalParticleVect[4].velocity = SPHAlgorithms::Point3D{-1.0, -1.0, -1.0};

    SPHAlgorithms::Volume volume(SPHAlgorithms::Cuboid(SPHAlgorithms::Point3D{0.0, 0.0, 0.0}, 1.0, 1.0, 1.0));
    SPHAlgorithms::NeighboursSearch3D<ParticleVect> searcher(volume, Config::WaterSupportRadius, 0.001);
    searcher.search(generalParticleVect);
}

void ForcesTestSuite::densityForFourNeighbours()
{
    initGeneralParticles();

    Forces::ComputeDensity(generalParticleVect);

    EXPECT_NEAR(1633.2268932167424, generalParticleVect[0].density, Precision);
    EXPECT_NEAR(1657.4184918158344, generalParticleVect[1].density, Precision);
    EXPECT_NEAR(1666.5821684082164, generalParticleVect[2].density, Precision);
    EXPECT_NEAR(1657.4184918158344, generalParticleVect[3].density, Precision);
    EXPECT_NEAR(1633.2268932167424, generalParticleVect[4].density, Precision);
}

void ForcesTestSuite::pressureForFourNeighbours()
{
    Forces::ComputePressure(generalParticleVect);

    EXPECT_NEAR(1904.8106796502273, generalParticleVect[0].pressure, Precision);
    EXPECT_NEAR(1977.3854754475033, generalParticleVect[1].pressure, Precision);
    EXPECT_NEAR(2004.8765052246492, generalParticleVect[2].pressure, Precision);
    EXPECT_NEAR(1977.3854754475033, generalParticleVect[3].pressure, Precision);
    EXPECT_NEAR(1904.8106796502273, generalParticleVect[4].pressure, Precision);
}

void ForcesTestSuite::internalForcesForFourNeighbours()
{
    Forces::ComputeInternalForces(generalParticleVect);

    EXPECT_NEAR(-2781.9657993131996, generalParticleVect[0].fPressure[0], Precision);
    EXPECT_NEAR(-2781.9657993131996, generalParticleVect[0].fPressure[1], Precision);
    EXPECT_NEAR(-2781.9657993131996, generalParticleVect[0].fPressure[2], Precision);
    EXPECT_NEAR(-1303.6387682093077, generalParticleVect[1].fPressure[0], Precision);
    EXPECT_NEAR(-1303.6387682093077, generalParticleVect[1].fPressure[1], Precision);
    EXPECT_NEAR(-1303.6387682093077, generalParticleVect[1].fPressure[2], Precision);
    EXPECT_NEAR(0, generalParticleVect[2].fPressure[0], Precision);
    EXPECT_NEAR(0, generalParticleVect[2].fPressure[1], Precision);
    EXPECT_NEAR(0, generalParticleVect[2].fPressure[2], Precision);
    EXPECT_NEAR(1303.6387682093077, generalParticleVect[3].fPressure[0], Precision);
    EXPECT_NEAR(1303.6387682093077, generalParticleVect[3].fPressure[1], Precision);
    EXPECT_NEAR(1303.6387682093077, generalParticleVect[3].fPressure[2], Precision);
    EXPECT_NEAR(2781.9657993131996, generalParticleVect[4].fPressure[0], Precision);
    EXPECT_NEAR(2781.9657993131996, generalParticleVect[4].fPressure[1], Precision);
    EXPECT_NEAR(2781.9657993131996, generalParticleVect[4].fPressure[2], Precision);

    EXPECT_NEAR(-145.2472804052253, generalParticleVect[0].fViscosity[0], Precision);
    EXPECT_NEAR(-145.2472804052253, generalParticleVect[0].fViscosity[1], Precision);
    EXPECT_NEAR(-145.2472804052253, generalParticleVect[0].fViscosity[2], Precision);
    EXPECT_NEAR(-82.77227382174101, generalParticleVect[1].fViscosity[0], Precision);
    EXPECT_NEAR(-82.77227382174101, generalParticleVect[1].fViscosity[1], Precision);
    EXPECT_NEAR(-82.77227382174101, generalParticleVect[1].fViscosity[2], Precision);
    EXPECT_NEAR(-1.8028680885943995, generalParticleVect[2].fViscosity[0], Precision);
    EXPECT_NEAR(-1.8028680885943995, generalParticleVect[2].fViscosity[1], Precision);
    EXPECT_NEAR(-1.8028680885943995, generalParticleVect[2].fViscosity[2], Precision);
    EXPECT_NEAR(83.76713330738265, generalParticleVect[3].fViscosity[0], Precision);
    EXPECT_NEAR(83.76713330738265, generalParticleVect[3].fViscosity[1], Precision);
    EXPECT_NEAR(83.76713330738265, generalParticleVect[3].fViscosity[2], Precision);
    EXPECT_NEAR(146.03372700208183, generalParticleVect[4].fViscosity[0], Precision);
    EXPECT_NEAR(146.03372700208183, generalParticleVect[4].fViscosity[1], Precision);
    EXPECT_NEAR(146.03372700208183, generalParticleVect[4].fViscosity[2], Precision);

    EXPECT_NEAR(-2927.213079718425, generalParticleVect[0].fInternal[0], Precision);
    EXPECT_NEAR(-2927.213079718425, generalParticleVect[0].fInternal[1], Precision);
    EXPECT_NEAR(-2927.213079718425, generalParticleVect[0].fInternal[2], Precision);
    EXPECT_NEAR(-1386.4110420310487, generalParticleVect[1].fInternal[0], Precision);
    EXPECT_NEAR(-1386.4110420310487, generalParticleVect[1].fInternal[1], Precision);
    EXPECT_NEAR(-1386.4110420310487, generalParticleVect[1].fInternal[2], Precision);
    EXPECT_NEAR(-1.8028680885941721, generalParticleVect[2].fInternal[0], Precision);
    EXPECT_NEAR(-1.8028680885941721, generalParticleVect[2].fInternal[1], Precision);
    EXPECT_NEAR(-1.8028680885941721, generalParticleVect[2].fInternal[2], Precision);
    EXPECT_NEAR(1387.4059015166904, generalParticleVect[3].fInternal[0], Precision);
    EXPECT_NEAR(1387.4059015166904, generalParticleVect[3].fInternal[1], Precision);
    EXPECT_NEAR(1387.4059015166904, generalParticleVect[3].fInternal[2], Precision);
    EXPECT_NEAR(2927.9995263152814, generalParticleVect[4].fInternal[0], Precision);
    EXPECT_NEAR(2927.9995263152814, generalParticleVect[4].fInternal[1], Precision);
    EXPECT_NEAR(2927.9995263152814, generalParticleVect[4].fInternal[2], Precision);
}

void ForcesTestSuite::externalForcesForFourNeighbours()
{
    Forces::ComputeExternalForces(generalParticleVect);

    EXPECT_NEAR(0, generalParticleVect[0].fGravity[0], Precision);
    EXPECT_NEAR(0, generalParticleVect[0].fGravity[1], Precision);
    EXPECT_NEAR(-16038.288091388411, generalParticleVect[0].fGravity[2], Precision);
    EXPECT_NEAR(0, generalParticleVect[1].fGravity[0], Precision);
    EXPECT_NEAR(0, generalParticleVect[1].fGravity[1], Precision);
    EXPECT_NEAR(-16275.849589631494, generalParticleVect[1].fGravity[2], Precision);
    EXPECT_NEAR(0, generalParticleVect[2].fGravity[0], Precision);
    EXPECT_NEAR(0, generalParticleVect[2].fGravity[1], Precision);
    EXPECT_NEAR(-16365.836893768685, generalParticleVect[2].fGravity[2], Precision);
    EXPECT_NEAR(0, generalParticleVect[3].fGravity[0], Precision);
    EXPECT_NEAR(0, generalParticleVect[3].fGravity[1], Precision);
    EXPECT_NEAR(-16275.849589631494, generalParticleVect[3].fGravity[2], Precision);
    EXPECT_NEAR(0, generalParticleVect[4].fGravity[0], Precision);
    EXPECT_NEAR(0, generalParticleVect[4].fGravity[1], Precision);
    EXPECT_NEAR(-16038.288091388411, generalParticleVect[4].fGravity[2], Precision);

    EXPECT_NEAR(0, generalParticleVect[0].fSurfaceTension[0], Precision);
    EXPECT_NEAR(0, generalParticleVect[0].fSurfaceTension[1], Precision);
    EXPECT_NEAR(0, generalParticleVect[1].fSurfaceTension[0], Precision);
    EXPECT_NEAR(0, generalParticleVect[1].fSurfaceTension[1], Precision);
    EXPECT_NEAR(0, generalParticleVect[2].fSurfaceTension[0], Precision);
    EXPECT_NEAR(0, generalParticleVect[2].fSurfaceTension[1], Precision);
    EXPECT_NEAR(0, generalParticleVect[3].fSurfaceTension[0], Precision);
    EXPECT_NEAR(0, generalParticleVect[3].fSurfaceTension[1], Precision);
    EXPECT_NEAR(0, generalParticleVect[4].fSurfaceTension[0], Precision);
    EXPECT_NEAR(0, generalParticleVect[4].fSurfaceTension[1], Precision);

    EXPECT_NEAR(0, generalParticleVect[0].fExternal[0], Precision);
    EXPECT_NEAR(0, generalParticleVect[0].fExternal[1], Precision);
    EXPECT_NEAR(-16038.288091388411, generalParticleVect[0].fExternal[2], Precision);
    EXPECT_NEAR(0, generalParticleVect[1].fExternal[0], Precision);
    EXPECT_NEAR(0, generalParticleVect[1].fExternal[1], Precision);
    EXPECT_NEAR(-16275.849589631494, generalParticleVect[1].fExternal[2], Precision);
    EXPECT_NEAR(0, generalParticleVect[2].fExternal[0], Precision);
    EXPECT_NEAR(0, generalParticleVect[2].fExternal[1], Precision);
    EXPECT_NEAR(-16365.836893768685, generalParticleVect[2].fExternal[2], Precision);
    EXPECT_NEAR(0, generalParticleVect[3].fExternal[0], Precision);
    EXPECT_NEAR(0, generalParticleVect[3].fExternal[1], Precision);
    EXPECT_NEAR(-16275.849589631494, generalParticleVect[3].fExternal[2], Precision);
    EXPECT_NEAR(0, generalParticleVect[4].fExternal[0], Precision);
    EXPECT_NEAR(0, generalParticleVect[4].fExternal[1], Precision);
    EXPECT_NEAR(-16038.288091388411, generalParticleVect[4].fExternal[2], Precision);
}

//---------------------------------------------

void ForcesTestSuite::densityForOneNeighbour()
{
    Particle particle1(SPHAlgorithms::Point3D{3.0, 3.0, 1.0}, 0.01);
    Particle particle2(SPHAlgorithms::Point3D{3.0, 3.01, 1.0}, 0.01);
    particle1.neighbours = {1};
    particle2.neighbours = {0};

    ParticleVect particleVect = {particle1, particle2};

    Forces::ComputeDensity(particleVect);

    EXPECT_NEAR(1597.0844603546218, particleVect[0].density, Precision);
    EXPECT_NEAR(1597.0844603546218, particleVect[1].density, Precision);
}

void ForcesTestSuite::densityForTwoNeighbours()
{
    Particle particle1(SPHAlgorithms::Point3D{3.0, 3.0, 1.0}, 0.01);
    Particle particle2(SPHAlgorithms::Point3D{3.0, 3.01, 1.0}, 0.01);
    Particle particle3(SPHAlgorithms::Point3D{3.005, 3.005, 1.0}, 0.01);
    particle1.neighbours = {1, 2};
    particle2.neighbours = {0, 2};
    particle3.neighbours = {0, 1};

    ParticleVect particleVect = {particle1, particle2, particle3};

    Forces::ComputeDensity(particleVect);

    EXPECT_NEAR(1627.9504314400233, particleVect[0].density, Precision);
    EXPECT_NEAR(1627.9504314400233, particleVect[1].density, Precision);
    EXPECT_NEAR(1628.4134132316474, particleVect[2].density, Precision);
}

void ForcesTestSuite::densityForThreeNeighbours()
{
    Particle particle1(SPHAlgorithms::Point3D{3.0, 3.0, 1.0}, 0.01);
    Particle particle2(SPHAlgorithms::Point3D{3.0, 3.01, 1.0}, 0.01);
    Particle particle3(SPHAlgorithms::Point3D{3.005, 3.005, 1.0}, 0.01);
    Particle particle4(SPHAlgorithms::Point3D{2.995, 2.996, 1.0}, 0.01);
    particle1.neighbours = {1, 2, 3};
    particle2.neighbours = {0, 2, 3};
    particle3.neighbours = {0, 1, 3};
    particle4.neighbours = {0, 1, 2};

    ParticleVect particleVect = {particle1, particle2, particle3, particle4};

    Forces::ComputeDensity(particleVect);

    EXPECT_NEAR(1658.9002352147459, particleVect[0].density, Precision);
    EXPECT_NEAR(1657.2522139936098, particleVect[1].density, Precision);
    EXPECT_NEAR(1658.0762364059892, particleVect[2].density, Precision);
    EXPECT_NEAR(1656.5958805634953, particleVect[3].density, Precision);
}

void ForcesTestSuite::pressureForOneNeighbour()
{
    Particle particle1(SPHAlgorithms::Point3D{0.0, 0.0, 1.0}, 0.01);
    Particle particle2(SPHAlgorithms::Point3D{0.0, 0.01, 1.0}, 0.01);
    particle1.neighbours = {1};
    particle2.neighbours = {0};

    ParticleVect particleVect = {particle1, particle2};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);

    EXPECT_NEAR(1796.3833810638655, particleVect[0].pressure, Precision);
    EXPECT_NEAR(1796.3833810638655, particleVect[1].pressure, Precision);
}

void ForcesTestSuite::pressureForTwoNeighbours()
{
    Particle particle1(SPHAlgorithms::Point3D{3.0, 3.0, 1.0}, 0.01);
    Particle particle2(SPHAlgorithms::Point3D{3.0, 3.01, 1.0}, 0.01);
    Particle particle3(SPHAlgorithms::Point3D{3.005, 3.005, 1.0}, 0.01);
    particle1.neighbours = {1, 2};
    particle2.neighbours = {0, 2};
    particle3.neighbours = {0, 1};

    ParticleVect particleVect = {particle1, particle2, particle3};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);

    EXPECT_NEAR(1888.98129432007, particleVect[0].pressure, Precision);
    EXPECT_NEAR(1888.98129432007, particleVect[1].pressure, Precision);
    EXPECT_NEAR(1890.3702396949423, particleVect[2].pressure, Precision);
}

void ForcesTestSuite::pressureForThreeNeighbours()
{
    Particle particle1(SPHAlgorithms::Point3D{3.0, 3.0, 1.0}, 0.01);
    Particle particle2(SPHAlgorithms::Point3D{3.0, 3.01, 1.0}, 0.01);
    Particle particle3(SPHAlgorithms::Point3D{3.005, 3.005, 1.0}, 0.01);
    Particle particle4(SPHAlgorithms::Point3D{2.995, 2.996, 1.0}, 0.01);
    particle1.neighbours = {1, 2, 3};
    particle2.neighbours = {0, 2, 3};
    particle3.neighbours = {0, 1, 3};
    particle4.neighbours = {0, 1, 2};

    ParticleVect particleVect = {particle1, particle2, particle3, particle4};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);

    EXPECT_NEAR(1981.8307056442377, particleVect[0].pressure, Precision);
    EXPECT_NEAR(1976.8866419808294, particleVect[1].pressure, Precision);
    EXPECT_NEAR(1979.3587092179678, particleVect[2].pressure, Precision);
    EXPECT_NEAR(1974.9176416904859, particleVect[3].pressure, Precision);
}

void ForcesTestSuite::internalForcesForOneNeighbour()
{
    Particle particle1(SPHAlgorithms::Point3D{0.0, 0.0, 1.0}, 0.01);
    Particle particle2(SPHAlgorithms::Point3D{0.0, 0.01, 1.0}, 0.01);
    particle1.velocity = SPHAlgorithms::Point3D{0.1, 0.1, 1.0};
    particle2.velocity = SPHAlgorithms::Point3D{-0.1, -0.1, 1.0};
    particle1.neighbours = {1};
    particle2.neighbours = {0};

    ParticleVect particleVect = {particle1, particle2};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);
    Forces::ComputeInternalForces(particleVect);

    EXPECT_NEAR(0, particleVect[0].fPressure[0], Precision);
    EXPECT_NEAR(-2610.0498385862716, particleVect[0].fPressure[1], Precision);
    EXPECT_NEAR(0, particleVect[0].fPressure[2], Precision);
    EXPECT_NEAR(0, particleVect[1].fPressure[0], Precision);
    EXPECT_NEAR(2610.0498385862716, particleVect[1].fPressure[1], Precision);
    EXPECT_NEAR(0, particleVect[1].fPressure[2], Precision);

    EXPECT_NEAR(-11.300698863861873, particleVect[0].fViscosity[0], Precision);
    EXPECT_NEAR(-11.300698863861873, particleVect[0].fViscosity[1], Precision);
    EXPECT_NEAR(0, particleVect[0].fViscosity[2], Precision);
    EXPECT_NEAR(11.300698863861873, particleVect[1].fViscosity[0], Precision);
    EXPECT_NEAR(11.300698863861873, particleVect[1].fViscosity[1], Precision);
    EXPECT_NEAR(0, particleVect[1].fViscosity[2], Precision);

    EXPECT_NEAR(-11.300698863861873, particleVect[0].fInternal[0], Precision);
    EXPECT_NEAR(-2621.3505374501333, particleVect[0].fInternal[1], Precision);
    EXPECT_NEAR(0, particleVect[0].fInternal[2], Precision);
    EXPECT_NEAR(11.300698863861873, particleVect[1].fInternal[0], Precision);
    EXPECT_NEAR(2621.3505374501333, particleVect[1].fInternal[1], Precision);
    EXPECT_NEAR(0, particleVect[1].fInternal[2], Precision);
}

void ForcesTestSuite::internalForcesForTwoNeighbours()
{
    Particle particle1(SPHAlgorithms::Point3D{3.0, 3.0, 1.0}, 0.01);
    Particle particle2(SPHAlgorithms::Point3D{3.0, 3.01, 1.0}, 0.01);
    Particle particle3(SPHAlgorithms::Point3D{3.005, 3.005, 1.0}, 0.01);
    particle1.velocity = SPHAlgorithms::Point3D{0.1, 0.1, 1.0};
    particle2.velocity = SPHAlgorithms::Point3D{-0.1, -0.1, 1.0};
    particle3.velocity = SPHAlgorithms::Point3D{0.1, -0.1, 1.0};
    particle1.neighbours = {1, 2};
    particle2.neighbours = {0, 2};
    particle3.neighbours = {0, 1};

    ParticleVect particleVect = {particle1, particle2, particle3};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);
    Forces::ComputeInternalForces(particleVect);

    EXPECT_NEAR(-2030.0285948263722, particleVect[0].fPressure[0], Precision);
    EXPECT_NEAR(-4722.5808205980848, particleVect[0].fPressure[1], Precision);
    EXPECT_NEAR(-2030.0285948263722, particleVect[1].fPressure[0], Precision);
    EXPECT_NEAR(4722.5808205980848, particleVect[1].fPressure[1], Precision);
    EXPECT_NEAR(4061.2118516838846, particleVect[2].fPressure[0], Precision);
    EXPECT_NEAR(0.0, particleVect[2].fPressure[1], Precision);

    EXPECT_NEAR(-11.086437398868615, particleVect[0].fViscosity[0], Precision);
    EXPECT_NEAR(-22.530413775020236, particleVect[0].fViscosity[1], Precision);
    EXPECT_NEAR(22.530413775020236, particleVect[1].fViscosity[0], Precision);
    EXPECT_NEAR(11.086437398868615, particleVect[1].fViscosity[1], Precision);
    EXPECT_NEAR(-11.447230991638436, particleVect[2].fViscosity[0], Precision);
    EXPECT_NEAR(11.447230991638436, particleVect[2].fViscosity[1], Precision);

    EXPECT_NEAR(-2041.1150322252408, particleVect[0].fInternal[0], Precision);
    EXPECT_NEAR(-4745.1112343731047, particleVect[0].fInternal[1], Precision);
    EXPECT_NEAR(-2007.498181051352, particleVect[1].fInternal[0], Precision);
    EXPECT_NEAR(4733.6672579969536, particleVect[1].fInternal[1], Precision);
    EXPECT_NEAR(4049.7646206922459, particleVect[2].fInternal[0], Precision);
    EXPECT_NEAR(11.447230991638436, particleVect[2].fInternal[1], Precision);
}

void ForcesTestSuite::internalForcesForThreeNeighbours()
{
    Particle particle1(SPHAlgorithms::Point3D{3.0, 3.0, 1.0}, 0.01);
    Particle particle2(SPHAlgorithms::Point3D{3.0, 3.01, 1.0}, 0.01);
    Particle particle3(SPHAlgorithms::Point3D{3.005, 3.005, 1.0}, 0.01);
    Particle particle4(SPHAlgorithms::Point3D{2.995, 2.996, 1.0}, 0.01);
    particle1.velocity = SPHAlgorithms::Point3D{0.0, 0.1, 1.0};
    particle2.velocity = SPHAlgorithms::Point3D{0.0, -0.1, 1.0};
    particle3.velocity = SPHAlgorithms::Point3D{-0.1, -0.1, 1.0};
    particle3.velocity = SPHAlgorithms::Point3D{0.1, 0.1, 1.0};
    particle1.neighbours = {1, 2, 3};
    particle2.neighbours = {0, 2, 3};
    particle3.neighbours = {0, 1, 3};
    particle4.neighbours = {0, 1, 2};

    ParticleVect particleVect = {particle1, particle2, particle3, particle4};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);
    Forces::ComputeInternalForces(particleVect);

    EXPECT_NEAR(250.73800272912922, particleVect[0].fPressure[0], Precision);
    EXPECT_NEAR(-2988.8282778642024, particleVect[0].fPressure[1], Precision);
    EXPECT_NEAR(-1254.0744609015103, particleVect[1].fPressure[0], Precision);
    EXPECT_NEAR(7188.0357586699693, particleVect[1].fPressure[1], Precision);
    EXPECT_NEAR(6080.2456386975646, particleVect[2].fPressure[0], Precision);
    EXPECT_NEAR(1713.7561759307598, particleVect[2].fPressure[1], Precision);
    EXPECT_NEAR(-5071.6290076368005, particleVect[3].fPressure[0], Precision);
    EXPECT_NEAR(-5912.738598577429, particleVect[3].fPressure[1], Precision);

    EXPECT_NEAR(5.6196223739462559, particleVect[0].fViscosity[0], Precision);
    EXPECT_NEAR(-16.555491020431027, particleVect[0].fViscosity[1], Precision);
    EXPECT_NEAR(5.6196223739462559, particleVect[1].fViscosity[0], Precision);
    EXPECT_NEAR(27.27168607636467, particleVect[1].fViscosity[1], Precision);
    EXPECT_NEAR(-16.477579252237028, particleVect[2].fViscosity[0], Precision);
    EXPECT_NEAR(-16.483164797185353, particleVect[2].fViscosity[1], Precision);
    EXPECT_NEAR(5.2336547858356761, particleVect[3].fViscosity[0], Precision);
    EXPECT_NEAR(5.7400569236350769, particleVect[3].fViscosity[1], Precision);

    EXPECT_NEAR(256.35762510307546, particleVect[0].fInternal[0], Precision);
    EXPECT_NEAR(-3005.3837688846334, particleVect[0].fInternal[1], Precision);
    EXPECT_NEAR(-1248.4548385275641, particleVect[1].fInternal[0], Precision);
    EXPECT_NEAR(7215.3074447463341, particleVect[1].fInternal[1], Precision);
    EXPECT_NEAR(6063.7680594453277, particleVect[2].fInternal[0], Precision);
    EXPECT_NEAR(1697.2730111335745, particleVect[2].fInternal[1], Precision);
    EXPECT_NEAR(-5066.3953528509646, particleVect[3].fInternal[0], Precision);
    EXPECT_NEAR(-5906.9985416537938, particleVect[3].fInternal[1], Precision);
}

void ForcesTestSuite::externalForcesForOneNeighbour()
{
    Particle particle1(SPHAlgorithms::Point3D{0.0, 0.0, 0.0}, 0.01);
    Particle particle2(SPHAlgorithms::Point3D{0.0, 0.01, 0.0}, 0.01);
    particle1.velocity = SPHAlgorithms::Point3D{0.1, 0.1, 0.1};
    particle2.velocity = SPHAlgorithms::Point3D{-0.1, -0.1, -0.1};
    particle1.neighbours = {1};
    particle2.neighbours = {0};

    ParticleVect particleVect = {particle1, particle2};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);
    Forces::ComputeInternalForces(particleVect);
    Forces::ComputeExternalForces(particleVect);

    EXPECT_NEAR(0.0, particleVect[0].fSurfaceTension[0], Precision);
    EXPECT_NEAR(0.0, particleVect[0].fSurfaceTension[1], Precision);
    EXPECT_NEAR(0.0, particleVect[0].fSurfaceTension[2], Precision);
    EXPECT_NEAR(0.0, particleVect[1].fSurfaceTension[0], Precision);
    EXPECT_NEAR(0.0, particleVect[1].fSurfaceTension[1], Precision);
    EXPECT_NEAR(0.0, particleVect[1].fSurfaceTension[2], Precision);

    EXPECT_NEAR(0.0, particleVect[0].fExternal[0], Precision);
    EXPECT_NEAR(0.0, particleVect[0].fExternal[1], Precision);
    EXPECT_NEAR(-15683.369400682386, particleVect[0].fExternal[2], Precision);

    EXPECT_NEAR(0.0, particleVect[1].fExternal[0], Precision);
    EXPECT_NEAR(0.0, particleVect[1].fExternal[1], Precision);
    EXPECT_NEAR(-15683.369400682386, particleVect[1].fExternal[2], Precision);
}

void ForcesTestSuite::externalForcesForTwoNeighbours()
{
    Particle particle1(SPHAlgorithms::Point3D{3.0, 3.0, 1.0}, 0.01);
    Particle particle2(SPHAlgorithms::Point3D{3.0, 3.01, 1.0}, 0.01);
    Particle particle3(SPHAlgorithms::Point3D{3.005, 3.005, 1.0}, 0.01);
    particle1.velocity = SPHAlgorithms::Point3D{0.1, 0.1, 1.0};
    particle2.velocity = SPHAlgorithms::Point3D{-0.1, -0.1, 1.0};
    particle3.velocity = SPHAlgorithms::Point3D{0.1, -0.1, 1.0};
    particle1.neighbours = {1, 2};
    particle2.neighbours = {0, 2};
    particle3.neighbours = {0, 1};

    ParticleVect particleVect = {particle1, particle2, particle3};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);
    Forces::ComputeInternalForces(particleVect);
    Forces::ComputeExternalForces(particleVect);

    EXPECT_NEAR(0.0, particleVect[0].fSurfaceTension[0], Precision);
    EXPECT_NEAR(0.0, particleVect[0].fSurfaceTension[1], Precision);
    EXPECT_NEAR(0.0, particleVect[0].fSurfaceTension[2], Precision);
    EXPECT_NEAR(0.0, particleVect[1].fSurfaceTension[0], Precision);
    EXPECT_NEAR(0.0, particleVect[1].fSurfaceTension[1], Precision);
    EXPECT_NEAR(0.0, particleVect[1].fSurfaceTension[2], Precision);
    EXPECT_NEAR(0.0, particleVect[2].fSurfaceTension[0], Precision);
    EXPECT_NEAR(0.0, particleVect[2].fSurfaceTension[1], Precision);
    EXPECT_NEAR(0.0, particleVect[2].fSurfaceTension[2], Precision);

    EXPECT_NEAR(0.0, particleVect[0].fExternal[0], Precision);
    EXPECT_NEAR(0.0, particleVect[0].fExternal[1], Precision);
    EXPECT_NEAR(-15986.473236741029, particleVect[0].fExternal[2], Precision);
    EXPECT_NEAR(0.0, particleVect[1].fExternal[0], Precision);
    EXPECT_NEAR(0.0, particleVect[1].fExternal[1], Precision);
    EXPECT_NEAR(-15986.473236741029, particleVect[1].fExternal[2], Precision);
    EXPECT_NEAR(0.0, particleVect[2].fExternal[0], Precision);
    EXPECT_NEAR(0.0, particleVect[2].fExternal[1], Precision);
    EXPECT_NEAR(-15991.019717934778, particleVect[2].fExternal[2], Precision);
}

void ForcesTestSuite::externalForcesForThreeNeighbours()
{
    Particle particle1(SPHAlgorithms::Point3D{3.0, 3.0, 1.0}, 0.01);
    Particle particle2(SPHAlgorithms::Point3D{3.0, 3.01, 1.0}, 0.01);
    Particle particle3(SPHAlgorithms::Point3D{3.005, 3.005, 1.0}, 0.01);
    Particle particle4(SPHAlgorithms::Point3D{2.995, 2.996, 1.0}, 0.01);
    particle1.velocity = SPHAlgorithms::Point3D{0.0, 0.1, 1.0};
    particle2.velocity = SPHAlgorithms::Point3D{0.0, -0.1, 1.0};
    particle3.velocity = SPHAlgorithms::Point3D{-0.1, -0.1, 1.0};
    particle4.velocity = SPHAlgorithms::Point3D{0.1, 0.1, 1.0};
    particle1.neighbours = {1, 2, 3};
    particle2.neighbours = {0, 2, 3};
    particle3.neighbours = {0, 1, 3};
    particle4.neighbours = {0, 1, 2};

    ParticleVect particleVect = {particle1, particle2, particle3, particle4};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);
    Forces::ComputeInternalForces(particleVect);
    Forces::ComputeExternalForces(particleVect);

    EXPECT_NEAR(0.0, particleVect[0].fSurfaceTension[0], Precision);
    EXPECT_NEAR(0.0, particleVect[0].fSurfaceTension[1], Precision);
    EXPECT_NEAR(0.0, particleVect[0].fSurfaceTension[2], Precision);
    EXPECT_NEAR(0.0, particleVect[1].fSurfaceTension[0], Precision);
    EXPECT_NEAR(0.0, particleVect[1].fSurfaceTension[1], Precision);
    EXPECT_NEAR(0.0, particleVect[1].fSurfaceTension[2], Precision);
    EXPECT_NEAR(0.0, particleVect[2].fSurfaceTension[0], Precision);
    EXPECT_NEAR(0.0, particleVect[2].fSurfaceTension[1], Precision);
    EXPECT_NEAR(0.0, particleVect[2].fSurfaceTension[2], Precision);
    EXPECT_NEAR(0.0, particleVect[3].fSurfaceTension[0], Precision);
    EXPECT_NEAR(0.0, particleVect[3].fSurfaceTension[1], Precision);
    EXPECT_NEAR(0.0, particleVect[3].fSurfaceTension[2], Precision);

    EXPECT_NEAR(0.0, particleVect[0].fExternal[0], Precision);
    EXPECT_NEAR(0.0, particleVect[0].fExternal[1], Precision);
    EXPECT_NEAR(-16290.400309808805, particleVect[0].fExternal[2], Precision);
    EXPECT_NEAR(0.0, particleVect[1].fExternal[0], Precision);
    EXPECT_NEAR(0.0, particleVect[1].fExternal[1], Precision);
    EXPECT_NEAR(-16274.216741417249, particleVect[1].fExternal[2], Precision);
    EXPECT_NEAR(0.0, particleVect[2].fExternal[0], Precision);
    EXPECT_NEAR(0.0, particleVect[2].fExternal[1], Precision);
    EXPECT_NEAR(-16282.308641506814, particleVect[2].fExternal[2], Precision);
    EXPECT_NEAR(0.0, particleVect[3].fExternal[0], Precision);
    EXPECT_NEAR(0.0, particleVect[3].fExternal[1], Precision);
    EXPECT_NEAR(-16267.771547133523, particleVect[3].fExternal[2], Precision);
}

void ForcesTestSuite::externalForcesForFiveNeighbours()
{
    Particle particle1(SPHAlgorithms::Point3D{3.0, 3.0, 1.0}, 0.01);
    Particle particle2(SPHAlgorithms::Point3D{3.0, 3.02, 1.0}, 0.01);
    Particle particle3(SPHAlgorithms::Point3D{3.02, 3.0, 1.0}, 0.01);
    Particle particle4(SPHAlgorithms::Point3D{3.02, 3.02, 1.0}, 0.01);
    Particle particle5(SPHAlgorithms::Point3D{3.01, 3.01, 1.0}, 0.01);
    particle1.neighbours = {1, 2, 3, 4};
    particle2.neighbours = {0, 2, 3, 4};
    particle3.neighbours = {0, 1, 3, 4};
    particle4.neighbours = {0, 1, 2, 4};
    particle5.neighbours = {0, 1, 2, 3};

    particle1.velocity = SPHAlgorithms::Point3D{0.0, 0.1, 1.0};
    particle2.velocity = SPHAlgorithms::Point3D{0.0, -0.1, 1.0};
    particle3.velocity = SPHAlgorithms::Point3D{-0.1, -0.1, 1.0};
    particle4.velocity = SPHAlgorithms::Point3D{0.1, 0.1, 1.0};

    ParticleVect particleVect = {particle1, particle2, particle3, particle4, particle5};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);
    Forces::ComputeInternalForces(particleVect);
    Forces::ComputeExternalForces(particleVect);

    EXPECT_NEAR(0.0, particleVect[0].fSurfaceTension[0], Precision);
    EXPECT_NEAR(0.0, particleVect[0].fSurfaceTension[1], Precision);
    EXPECT_NEAR(0.0, particleVect[0].fSurfaceTension[2], Precision);
    EXPECT_NEAR(0.0, particleVect[1].fSurfaceTension[0], Precision);
    EXPECT_NEAR(0.0, particleVect[1].fSurfaceTension[1], Precision);
    EXPECT_NEAR(0.0, particleVect[1].fSurfaceTension[2], Precision);
    EXPECT_NEAR(0.0, particleVect[2].fSurfaceTension[0], Precision);
    EXPECT_NEAR(0.0, particleVect[2].fSurfaceTension[1], Precision);
    EXPECT_NEAR(0.0, particleVect[2].fSurfaceTension[2], Precision);
    EXPECT_NEAR(0.0, particleVect[3].fSurfaceTension[0], Precision);
    EXPECT_NEAR(0.0, particleVect[3].fSurfaceTension[1], Precision);
    EXPECT_NEAR(0.0, particleVect[3].fSurfaceTension[2], Precision);
    EXPECT_NEAR(0.0, particleVect[4].fSurfaceTension[0], Precision);
    EXPECT_NEAR(0.0, particleVect[4].fSurfaceTension[1], Precision);
    EXPECT_NEAR(0.0, particleVect[4].fSurfaceTension[2], Precision);

    EXPECT_NEAR(0.0, particleVect[0].fExternal[0], Precision);
    EXPECT_NEAR(0.0, particleVect[0].fExternal[1], Precision);
    EXPECT_NEAR(-16458.472539451439, particleVect[0].fExternal[2], Precision);
    EXPECT_NEAR(0.0, particleVect[1].fExternal[0], Precision);
    EXPECT_NEAR(0.0, particleVect[1].fExternal[1], Precision);
    EXPECT_NEAR(-16458.472539451439, particleVect[1].fExternal[2], Precision);
    EXPECT_NEAR(0.0, particleVect[2].fExternal[0], Precision);
    EXPECT_NEAR(0.0, particleVect[2].fExternal[1], Precision);
    EXPECT_NEAR(-16458.472539451439, particleVect[2].fExternal[2], Precision);
    EXPECT_NEAR(0.0, particleVect[3].fExternal[0], Precision);
    EXPECT_NEAR(0.0, particleVect[3].fExternal[1], Precision);
    EXPECT_NEAR(-16458.472539451439, particleVect[3].fExternal[2], Precision);
    EXPECT_NEAR(0.0, particleVect[4].fExternal[0], Precision);
    EXPECT_NEAR(0.0, particleVect[4].fExternal[1], Precision);
    EXPECT_NEAR(-16543.217007339656, particleVect[4].fExternal[2], Precision);
}

void ForcesTestSuite::allForcesForOneNeighbour()
{
    Particle particle1(SPHAlgorithms::Point3D{3.0, 3.0, 1.0}, 0.01);
    Particle particle2(SPHAlgorithms::Point3D{3.0, 3.01, 1.0}, 0.01);
    particle1.velocity = SPHAlgorithms::Point3D{0.0, 0.1, 1.0};
    particle2.velocity = SPHAlgorithms::Point3D{0.0, -0.1, 1.0};
    particle1.neighbours = {1};
    particle2.neighbours = {0};

    ParticleVect particleVect = {particle1, particle2};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);
    Forces::ComputeInternalForces(particleVect);
    Forces::ComputeExternalForces(particleVect);
    Forces::ComputeAllForces(particleVect);

    EXPECT_NEAR(0.0, particleVect[0].fTotal[0], Precision);
    EXPECT_NEAR(-2621.3505374501456, particleVect[0].fTotal[1], Precision);
    EXPECT_NEAR(-15683.369400682386, particleVect[0].fTotal[2], Precision);
    EXPECT_NEAR(0.0, particleVect[1].fTotal[0], Precision);
    EXPECT_NEAR(2621.3505374501456, particleVect[1].fTotal[1], Precision);
    EXPECT_NEAR(-15683.369400682386, particleVect[1].fTotal[2], Precision);
}

void ForcesTestSuite::allForcesForTwoNeighbours()
{
    Particle particle1(SPHAlgorithms::Point3D{3.0, 3.0, 1.0}, 0.01);
    Particle particle2(SPHAlgorithms::Point3D{3.0, 3.01, 1.0}, 0.01);
    Particle particle3(SPHAlgorithms::Point3D{3.005, 3.005, 1.0}, 0.01);
    particle1.velocity = SPHAlgorithms::Point3D{0.0, 0.1, 1.0};
    particle2.velocity = SPHAlgorithms::Point3D{0.0, -0.1, 1.0};
    particle3.velocity = SPHAlgorithms::Point3D{-0.1, -0.1, 1.0};
    particle1.neighbours = {1, 2};
    particle2.neighbours = {0, 2};
    particle3.neighbours = {0, 1};

    ParticleVect particleVect = {particle1, particle2, particle3};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);
    Forces::ComputeInternalForces(particleVect);
    Forces::ComputeExternalForces(particleVect);
    Forces::ComputeAllForces(particleVect);

    EXPECT_NEAR(-2035.750583014448, particleVect[0].fTotal[0], Precision);
    EXPECT_NEAR(-4745.1112343731047, particleVect[0].fTotal[1], Precision);
    EXPECT_NEAR(-15986.473236741029, particleVect[0].fTotal[2], Precision);
    EXPECT_NEAR(-2035.750583014448, particleVect[1].fTotal[0], Precision);
    EXPECT_NEAR(4733.6672579969536, particleVect[1].fTotal[1], Precision);
    EXPECT_NEAR(-15986.473236741029, particleVect[1].fTotal[2], Precision);
    EXPECT_NEAR(4072.6590826755232, particleVect[2].fTotal[0], Precision);
    EXPECT_NEAR(11.447230991638436, particleVect[2].fTotal[1], Precision);
    EXPECT_NEAR(-15991.019717934778, particleVect[2].fTotal[2], Precision);
}

void ForcesTestSuite::allForcesForThreeNeighbours()
{
    Particle particle1(SPHAlgorithms::Point3D{3.0, 3.0, 1.0}, 0.01);
    Particle particle2(SPHAlgorithms::Point3D{3.0, 3.01, 1.0}, 0.01);
    Particle particle3(SPHAlgorithms::Point3D{3.005, 3.005, 1.0}, 0.01);
    Particle particle4(SPHAlgorithms::Point3D{2.995, 2.996, 1.0}, 0.01);
    particle1.velocity = SPHAlgorithms::Point3D{0.0, 0.1, 1.0};
    particle2.velocity = SPHAlgorithms::Point3D{0.0, -0.1, 1.0};
    particle3.velocity = SPHAlgorithms::Point3D{-0.1, -0.1, 1.0};
    particle4.velocity = SPHAlgorithms::Point3D{0.1, 0.1, 1.0};
    particle1.neighbours = {1, 2, 3};
    particle2.neighbours = {0, 2, 3};
    particle3.neighbours = {0, 1, 3};
    particle4.neighbours = {0, 1, 2};

    ParticleVect particleVect = {particle1, particle2, particle3, particle4};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);
    Forces::ComputeInternalForces(particleVect);
    Forces::ComputeExternalForces(particleVect);
    Forces::ComputeAllForces(particleVect);

    EXPECT_NEAR(250.7834526486244, particleVect[0].fTotal[0], Precision);
    EXPECT_NEAR(-3010.9579413390843, particleVect[0].fTotal[1], Precision);
    EXPECT_NEAR(-16290.400309808805, particleVect[0].fTotal[2], Precision);
    EXPECT_NEAR(-1254.5412416742606, particleVect[1].fTotal[0], Precision);
    EXPECT_NEAR(7209.2210415996369, particleVect[1].fTotal[1], Precision);
    EXPECT_NEAR(-16274.216741417249, particleVect[1].fTotal[2], Precision);
    EXPECT_NEAR(6101.9615495983116, particleVect[2].fTotal[0], Precision);
    EXPECT_NEAR(1735.4665012865582, particleVect[2].fTotal[1], Precision);
    EXPECT_NEAR(-16282.308641506814, particleVect[2].fTotal[2], Precision);
    EXPECT_NEAR(-5092.904321115343, particleVect[3].fTotal[0], Precision);
    EXPECT_NEAR(-5933.5075099181722, particleVect[3].fTotal[1], Precision);
    EXPECT_NEAR(-16267.771547133523, particleVect[3].fTotal[2], Precision);
}

} // namespace TestEnvironment
} // namespace SPHSDK

using namespace SPHSDK::TestEnvironment;

TEST(ForcesTestSuite, densityForFourNeighbours)
{
    ForcesTestSuite::densityForFourNeighbours();
}

TEST(ForcesTestSuite, pressureForFourNeighbours)
{
    ForcesTestSuite::pressureForFourNeighbours();
}

TEST(ForcesTestSuite, internalForcesForFourNeighbours)
{
    ForcesTestSuite::internalForcesForFourNeighbours();
}

TEST(ForcesTestSuite, externalForcesForFourNeighbours)
{
    ForcesTestSuite::externalForcesForFourNeighbours();
}

//---------------------------------------------

TEST(ForcesTestSuite, densityForOneNeighbour)
{
    ForcesTestSuite::densityForOneNeighbour();
}
TEST(ForcesTestSuite, densityForTwoNeighbours)
{
    ForcesTestSuite::densityForTwoNeighbours();
}
TEST(ForcesTestSuite, densityForThreeNeighbours)
{
    ForcesTestSuite::densityForThreeNeighbours();
}
TEST(ForcesTestSuite, pressureForOneNeighbour)
{
    ForcesTestSuite::pressureForOneNeighbour();
}
TEST(ForcesTestSuite, pressureForTwoNeighbours)
{
    ForcesTestSuite::pressureForTwoNeighbours();
}
TEST(ForcesTestSuite, pressureForThreeNeighbours)
{
    ForcesTestSuite::pressureForThreeNeighbours();
}
TEST(ForcesTestSuite, internalForcesForOneNeighbour)
{
    ForcesTestSuite::internalForcesForOneNeighbour();
}
TEST(ForcesTestSuite, internalForcesForTwoNeighbours)
{
    ForcesTestSuite::internalForcesForTwoNeighbours();
}
TEST(ForcesTestSuite, internalForcesForThreeNeighbours)
{
    ForcesTestSuite::internalForcesForThreeNeighbours();
}
TEST(ForcesTestSuite, externalForcesForOneNeighbour)
{
    ForcesTestSuite::externalForcesForOneNeighbour();
}
TEST(ForcesTestSuite, externalForcesForTwoNeighbours)
{
    ForcesTestSuite::externalForcesForTwoNeighbours();
}
TEST(ForcesTestSuite, externalForcesForThreeNeighbours)
{
    ForcesTestSuite::externalForcesForThreeNeighbours();
}
TEST(ForsesTestSuite, externalForcesForFiveNeighbours)
{
    ForcesTestSuite::externalForcesForFiveNeighbours();
}
TEST(ForcesTestSuite, allForcesForOneNeighbour)
{
    ForcesTestSuite::allForcesForOneNeighbour();
}
TEST(ForcesTestSuite, allForcesForTwoNeighbours)
{
    ForcesTestSuite::allForcesForTwoNeighbours();
}
TEST(ForcesTestSuite, allForcesForThreeNeighbours)
{
    ForcesTestSuite::allForcesForThreeNeighbours();
}
