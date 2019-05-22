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

    for (size_t i = 0; i < numberOfParticles; ++i) {
        generalParticleVect[i] = Particle(SPHAlgorithms::Point3D(0.5 + 0.01 * i, 0.5 + 0.01 * i, 0.5 + 0.01 * i), 0.01);
        generalParticleVect[i].mass = Config::WaterParticleMass;
        generalParticleVect[i].supportRadius = Config::WaterSupportRadius;
    }

    generalParticleVect[0].velocity = SPHAlgorithms::Point3D(1.0, 1.0, 1.0);
    generalParticleVect[1].velocity = SPHAlgorithms::Point3D(0.5, 0.5, 0.5);
    generalParticleVect[2].velocity = SPHAlgorithms::Point3D(0.0, 0.0, 0.0);
    generalParticleVect[3].velocity = SPHAlgorithms::Point3D(-0.5, -0.5, -0.5);
    generalParticleVect[4].velocity = SPHAlgorithms::Point3D(-1.0, -1.0, -1.0);

    SPHAlgorithms::Volume volume(SPHAlgorithms::Cuboid(SPHAlgorithms::Point3D(0.0, 0.0, 0.0), 1.0, 1.0, 1.0));
	SPHAlgorithms::NeighboursSearch3D<ParticleVect> searcher(volume, Config::WaterSupportRadius, 0.001);
    searcher.search(generalParticleVect);
}

void ForcesTestSuite::densityForFourNeighbours()
{
    initGeneralParticles();

    Forces::ComputeDensity(generalParticleVect);

    EXPECT_NEAR(16735.34710282386, generalParticleVect[0].density, Precision);
    EXPECT_NEAR(16978.06900702438, generalParticleVect[1].density, Precision);
    EXPECT_NEAR(17054.29550344709, generalParticleVect[2].density, Precision);
    EXPECT_NEAR(16978.06900702438, generalParticleVect[3].density, Precision);
    EXPECT_NEAR(16735.34710282386, generalParticleVect[4].density, Precision);
}

void ForcesTestSuite::pressureForFourNeighbours()
{
    Forces::ComputePressure(generalParticleVect);

    EXPECT_NEAR(47211.17130847158, generalParticleVect[0].pressure, Precision);
    EXPECT_NEAR(47939.33702107313, generalParticleVect[1].pressure, Precision);
    EXPECT_NEAR(48168.01651034128, generalParticleVect[2].pressure, Precision);
    EXPECT_NEAR(47939.33702107313, generalParticleVect[3].pressure, Precision);
    EXPECT_NEAR(47211.17130847158, generalParticleVect[4].pressure, Precision);
}

void ForcesTestSuite::internalForcesForFourNeighbours()
{
    Forces::ComputeInternalForces(generalParticleVect);

    EXPECT_NEAR(-81584.950692131839, generalParticleVect[0].fPressure.x, Precision);
    EXPECT_NEAR(-81584.950692131839, generalParticleVect[0].fPressure.y, Precision);
    EXPECT_NEAR(-19165.703792130851, generalParticleVect[1].fPressure.x, Precision);
    EXPECT_NEAR(-19165.703792130851, generalParticleVect[1].fPressure.y, Precision);
    EXPECT_NEAR(0, generalParticleVect[2].fPressure.x, Precision);
    EXPECT_NEAR(0, generalParticleVect[2].fPressure.y, Precision);
    EXPECT_NEAR(19165.703792130851, generalParticleVect[3].fPressure.x, Precision);
    EXPECT_NEAR(19165.703792130851, generalParticleVect[3].fPressure.y, Precision);
    EXPECT_NEAR(81584.950692131839, generalParticleVect[4].fPressure.x, Precision);
    EXPECT_NEAR(81584.950692131839, generalParticleVect[4].fPressure.y, Precision);

    EXPECT_NEAR(-246.52991956173287, generalParticleVect[0].fViscosity.x, Precision);
    EXPECT_NEAR(-246.52991956173287, generalParticleVect[0].fViscosity.y, Precision);
    EXPECT_NEAR(-143.26079870121757, generalParticleVect[1].fViscosity.x, Precision);
    EXPECT_NEAR(-143.26079870121757, generalParticleVect[1].fViscosity.y, Precision);
    EXPECT_NEAR(0, generalParticleVect[2].fViscosity.x, Precision);
    EXPECT_NEAR(0, generalParticleVect[2].fViscosity.y, Precision);
    EXPECT_NEAR(143.26079870121757, generalParticleVect[3].fViscosity.x, Precision);
    EXPECT_NEAR(143.26079870121757, generalParticleVect[3].fViscosity.y, Precision);
    EXPECT_NEAR(246.52991956173287, generalParticleVect[4].fViscosity.x, Precision);
    EXPECT_NEAR(246.52991956173287, generalParticleVect[4].fViscosity.y, Precision);

    EXPECT_NEAR(-81831.480611693565, generalParticleVect[0].fInternal.x, Precision);
    EXPECT_NEAR(-81831.480611693565, generalParticleVect[0].fInternal.y, Precision);
    EXPECT_NEAR(-19308.964590832071, generalParticleVect[1].fInternal.x, Precision);
    EXPECT_NEAR(-19308.964590832071, generalParticleVect[1].fInternal.y, Precision);
    EXPECT_NEAR(0, generalParticleVect[2].fInternal.x, Precision);
    EXPECT_NEAR(0, generalParticleVect[2].fInternal.y, Precision);
    EXPECT_NEAR(19308.964590832071, generalParticleVect[3].fInternal.x, Precision);
    EXPECT_NEAR(19308.964590832071, generalParticleVect[3].fInternal.y, Precision);
    EXPECT_NEAR(81831.480611693565, generalParticleVect[4].fInternal.x, Precision);
    EXPECT_NEAR(81831.480611693565, generalParticleVect[4].fInternal.y, Precision);
}

void ForcesTestSuite::externalForcesForFourNeighbours()
{
    Forces::ComputeExternalForces(generalParticleVect);

    EXPECT_NEAR(0, generalParticleVect[0].fGravity.x, Precision);
    EXPECT_NEAR(-164341.10854973036, generalParticleVect[0].fGravity.y, Precision);
    EXPECT_NEAR(0, generalParticleVect[1].fGravity.x, Precision);
    EXPECT_NEAR(-166724.63764897941, generalParticleVect[1].fGravity.y, Precision);
    EXPECT_NEAR(0, generalParticleVect[2].fGravity.x, Precision);
    EXPECT_NEAR(-167473.18184385047, generalParticleVect[2].fGravity.y, Precision);
    EXPECT_NEAR(0, generalParticleVect[3].fGravity.x, Precision);
    EXPECT_NEAR(-166724.63764897941, generalParticleVect[3].fGravity.y, Precision);
    EXPECT_NEAR(0, generalParticleVect[4].fGravity.x, Precision);
    EXPECT_NEAR(-164341.10854973036, generalParticleVect[4].fGravity.y, Precision);

    EXPECT_NEAR(0, generalParticleVect[0].fSurfaceTension.x, Precision);
    EXPECT_NEAR(0, generalParticleVect[0].fSurfaceTension.y, Precision);
    EXPECT_NEAR(0, generalParticleVect[1].fSurfaceTension.x, Precision);
    EXPECT_NEAR(0, generalParticleVect[1].fSurfaceTension.y, Precision);
    EXPECT_NEAR(0, generalParticleVect[2].fSurfaceTension.x, Precision);
    EXPECT_NEAR(0, generalParticleVect[2].fSurfaceTension.y, Precision);
    EXPECT_NEAR(0, generalParticleVect[3].fSurfaceTension.x, Precision);
    EXPECT_NEAR(0, generalParticleVect[3].fSurfaceTension.y, Precision);
    EXPECT_NEAR(0, generalParticleVect[4].fSurfaceTension.x, Precision);
    EXPECT_NEAR(0, generalParticleVect[4].fSurfaceTension.y, Precision);

    EXPECT_NEAR(0, generalParticleVect[0].fExternal.x, Precision);
    EXPECT_NEAR(-164341.10854973036, generalParticleVect[0].fExternal.y, Precision);
    EXPECT_NEAR(0, generalParticleVect[1].fExternal.x, Precision);
    EXPECT_NEAR(-166724.63764897941, generalParticleVect[1].fExternal.y, Precision);
    EXPECT_NEAR(0, generalParticleVect[2].fExternal.x, Precision);
    EXPECT_NEAR(-167473.18184385047, generalParticleVect[2].fExternal.y, Precision);
    EXPECT_NEAR(0, generalParticleVect[3].fExternal.x, Precision);
    EXPECT_NEAR(-166724.63764897941, generalParticleVect[3].fExternal.y, Precision);
    EXPECT_NEAR(0, generalParticleVect[4].fExternal.x, Precision);
    EXPECT_NEAR(-164341.10854973036, generalParticleVect[4].fExternal.y, Precision);
}

//---------------------------------------------

void ForcesTestSuite::densityForOneNeighbour()
{
    Particle particle1(SPHAlgorithms::Point3D(3.0, 3.0, 1.0), 0.01);
    Particle particle2(SPHAlgorithms::Point3D(3.0, 3.01, 1.0), 0.01);
    particle1.neighbours = {1};
    particle2.neighbours = {0};

    ParticleVect particleVect = {particle1, particle2};

    Forces::ComputeDensity(particleVect);

    // TODO: Recalculate expected values
    EXPECT_NEAR(51851.55861657341, particleVect[0].density, Precision);
    EXPECT_NEAR(51851.55861657341, particleVect[1].density, Precision);
}

void ForcesTestSuite::densityForTwoNeighbours()
{
    Particle particle1(SPHAlgorithms::Point3D(3.0, 3.0, 1.0), 0.01);
    Particle particle2(SPHAlgorithms::Point3D(3.0, 3.01, 1.0), 0.01);
    Particle particle3(SPHAlgorithms::Point3D(3.005, 3.005, 1.0), 0.01);
    particle1.neighbours = {1, 2};
    particle2.neighbours = {0, 2};
    particle3.neighbours = {0, 1};

    ParticleVect particleVect = {particle1, particle2, particle3};

    Forces::ComputeDensity(particleVect);

    // TODO: Recalculate expected values
    EXPECT_NEAR(103725.03404765946, particleVect[0].density, Precision);
    EXPECT_NEAR(103725.03404765946, particleVect[1].density, Precision);
    EXPECT_NEAR(103746.95086217206, particleVect[2].density, Precision);
}

void ForcesTestSuite::densityForThreeNeighbours()
{
    Particle particle1(SPHAlgorithms::Point3D(3.0, 3.0, 1.0), 0.01);
    Particle particle2(SPHAlgorithms::Point3D(3.0, 3.01, 1.0), 0.01);
    Particle particle3(SPHAlgorithms::Point3D(3.005, 3.005, 1.0), 0.01);
    Particle particle4(SPHAlgorithms::Point3D(2.995, 2.996, 1.0), 0.01);
    particle1.neighbours = {1, 2, 3};
    particle2.neighbours = {0, 2, 3};
    particle3.neighbours = {0, 1, 3};
    particle4.neighbours = {0, 1, 2};

    ParticleVect particleVect = {particle1, particle2, particle3, particle4};

    Forces::ComputeDensity(particleVect);

    // TODO: Recalculate expected values
    EXPECT_NEAR(155602.57074862678, particleVect[0].density, Precision);
    EXPECT_NEAR(155527.94929964322, particleVect[1].density, Precision);
    EXPECT_NEAR(155565.27359797963, particleVect[2].density, Precision);
    EXPECT_NEAR(155498.77468875865, particleVect[3].density, Precision);
}

void ForcesTestSuite::pressureForOneNeighbour()
{
    Particle particle1(SPHAlgorithms::Point3D(0.0, 0.0, 1.0), 0.01);
    Particle particle2(SPHAlgorithms::Point3D(0.0, 0.01, 1.0), 0.01);
    particle1.neighbours = {1};
    particle2.neighbours = {0};

    ParticleVect particleVect = {particle1, particle2};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);

    // TODO: Recalculate expected values
    EXPECT_NEAR(152559.80584972026, particleVect[0].pressure, Precision);
    EXPECT_NEAR(152559.80584972026, particleVect[1].pressure, Precision);
}

void ForcesTestSuite::pressureForTwoNeighbours()
{
    Particle particle1(SPHAlgorithms::Point3D(3.0, 3.0, 1.0), 0.01);
    Particle particle2(SPHAlgorithms::Point3D(3.0, 3.01, 1.0), 0.01);
    Particle particle3(SPHAlgorithms::Point3D(3.005, 3.005, 1.0), 0.01);
    particle1.neighbours = {1, 2};
    particle2.neighbours = {0, 2};
    particle3.neighbours = {0, 1};

    ParticleVect particleVect = {particle1, particle2, particle3};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);

    // TODO: Recalculate expected values
    EXPECT_NEAR(308180.23214297841, particleVect[0].pressure, Precision);
    EXPECT_NEAR(308180.23214297841, particleVect[1].pressure, Precision);
    EXPECT_NEAR(308245.98258651618, particleVect[2].pressure, Precision);
}

void ForcesTestSuite::pressureForThreeNeighbours()
{
    Particle particle1(SPHAlgorithms::Point3D(3.0, 3.0, 1.0), 0.01);
    Particle particle2(SPHAlgorithms::Point3D(3.0, 3.01, 1.0), 0.01);
    Particle particle3(SPHAlgorithms::Point3D(3.005, 3.005, 1.0), 0.01);
    Particle particle4(SPHAlgorithms::Point3D(2.995, 2.996, 1.0), 0.01);
    particle1.neighbours = {1, 2, 3};
    particle2.neighbours = {0, 2, 3};
    particle3.neighbours = {0, 1, 3};
    particle4.neighbours = {0, 1, 2};

    ParticleVect particleVect = {particle1, particle2, particle3, particle4};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);

    // TODO: Recalculate expected values
    EXPECT_NEAR(463812.84224588028, particleVect[0].pressure, Precision);
    EXPECT_NEAR(463588.97789892962, particleVect[1].pressure, Precision);
    EXPECT_NEAR(463700.95079393883, particleVect[2].pressure, Precision);
    EXPECT_NEAR(463501.45406627597, particleVect[3].pressure, Precision);
}

void ForcesTestSuite::internalForcesForOneNeighbour()
{
    Particle particle1(SPHAlgorithms::Point3D(0.0, 0.0, 1.0), 0.01);
    Particle particle2(SPHAlgorithms::Point3D(0.0, 0.01, 1.0), 0.01);
    particle1.velocity = SPHAlgorithms::Point3D(0.1, 0.1, 1.0);
    particle2.velocity = SPHAlgorithms::Point3D(-0.1, -0.1, 1.0);
    particle1.neighbours = {1};
    particle2.neighbours = {0};

    ParticleVect particleVect = {particle1, particle2};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);
    Forces::ComputeInternalForces(particleVect);

    // TODO: Recalculate expected values
    EXPECT_NEAR(0, particleVect[0].fPressure.x, Precision);
    EXPECT_NEAR(-117926.16637639207, particleVect[0].fPressure.y, Precision);
    EXPECT_NEAR(0, particleVect[1].fPressure.x, Precision);
    EXPECT_NEAR(117926.16637639207, particleVect[1].fPressure.y, Precision);

    EXPECT_NEAR(-0.015202002863630612, particleVect[0].fViscosity.x, Precision);
    EXPECT_NEAR(-0.015202002863630612, particleVect[0].fViscosity.y, Precision);
    EXPECT_NEAR(0.015202002863630612, particleVect[1].fViscosity.x, Precision);
    EXPECT_NEAR(0.015202002863630612, particleVect[1].fViscosity.y, Precision);

    EXPECT_NEAR(-0.015202002863630612, particleVect[0].fInternal.x, Precision);
    EXPECT_NEAR(-117926.18157839493, particleVect[0].fInternal.y, Precision);
    EXPECT_NEAR(0.015202002863630612, particleVect[1].fInternal.x, Precision);
    EXPECT_NEAR(117926.18157839493, particleVect[1].fInternal.y, Precision);
}

void ForcesTestSuite::internalForcesForTwoNeighbours()
{
    Particle particle1(SPHAlgorithms::Point3D(3.0, 3.0, 1.0), 0.01);
    Particle particle2(SPHAlgorithms::Point3D(3.0, 3.01, 1.0), 0.01);
    Particle particle3(SPHAlgorithms::Point3D(3.005, 3.005, 1.0), 0.01);
    particle1.velocity = SPHAlgorithms::Point3D(0.1, 0.1, 1.0);
    particle2.velocity = SPHAlgorithms::Point3D(-0.1, -0.1, 1.0);
    particle3.velocity = SPHAlgorithms::Point3D(0.1, -0.1, 1.0);
    particle1.neighbours = {1, 2};
    particle2.neighbours = {0, 2};
    particle3.neighbours = {0, 1};

    ParticleVect particleVect = {particle1, particle2, particle3};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);
    Forces::ComputeInternalForces(particleVect);

    // TODO: Recalculate expected values
    EXPECT_NEAR(-98578.364211214794, particleVect[0].fPressure.x, Precision);
    EXPECT_NEAR(-217662.26725528983, particleVect[0].fPressure.y, Precision);
    EXPECT_NEAR(-98578.364211214794, particleVect[1].fPressure.x, Precision);
    EXPECT_NEAR(217662.26725528983, particleVect[1].fPressure.y, Precision);
    EXPECT_NEAR(197198.38709708242, particleVect[2].fPressure.x, Precision);
    EXPECT_NEAR(0.0, particleVect[2].fPressure.y, Precision);

    EXPECT_NEAR(-0.0075993953611110041, particleVect[0].fViscosity.x, Precision);
    EXPECT_NEAR(-0.015820530192803266, particleVect[0].fViscosity.y, Precision);
    EXPECT_NEAR(0.015820530192803266, particleVect[1].fViscosity.x, Precision);
    EXPECT_NEAR(0.0075993953611110041, particleVect[1].fViscosity.y, Precision);
    EXPECT_NEAR(-0.0082228719348790037, particleVect[2].fViscosity.x, Precision);
    EXPECT_NEAR(0.0082228719348790037, particleVect[2].fViscosity.y, Precision);

    EXPECT_NEAR(-98578.371810610159, particleVect[0].fInternal.x, Precision);
    EXPECT_NEAR(-217662.28307582001, particleVect[0].fInternal.y, Precision);
    EXPECT_NEAR(-98578.348390684594, particleVect[1].fInternal.x, Precision);
    EXPECT_NEAR(217662.27485468518, particleVect[1].fInternal.y, Precision);
    EXPECT_NEAR(197198.3788742105, particleVect[2].fInternal.x, Precision);
    EXPECT_NEAR(0.0082228719348790037, particleVect[2].fInternal.y, Precision);
}

void ForcesTestSuite::internalForcesForThreeNeighbours()
{
    Particle particle1(SPHAlgorithms::Point3D(3.0, 3.0, 1.0), 0.01);
    Particle particle2(SPHAlgorithms::Point3D(3.0, 3.01, 1.0), 0.01);
    Particle particle3(SPHAlgorithms::Point3D(3.005, 3.005, 1.0), 0.01);
    Particle particle4(SPHAlgorithms::Point3D(2.995, 2.996, 1.0), 0.01);
    particle1.velocity = SPHAlgorithms::Point3D(0.0, 0.1, 1.0);
    particle2.velocity = SPHAlgorithms::Point3D(0.0, -0.1, 1.0);
    particle3.velocity = SPHAlgorithms::Point3D(-0.1, -0.1, 1.0);
    particle3.velocity = SPHAlgorithms::Point3D(0.1, 0.1, 1.0);
    particle1.neighbours = {1, 2, 3};
    particle2.neighbours = {0, 2, 3};
    particle3.neighbours = {0, 1, 3};
    particle4.neighbours = {0, 1, 2};

    ParticleVect particleVect = {particle1, particle2, particle3, particle4};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);
    Forces::ComputeInternalForces(particleVect);

    // TODO: Recalculate expected values
    EXPECT_NEAR(14153.287707445299, particleVect[0].fPressure.x, Precision);
    EXPECT_NEAR(-127959.54736643603, particleVect[0].fPressure.y, Precision);
    EXPECT_NEAR(-68918.721236387355, particleVect[1].fPressure.x, Precision);
    EXPECT_NEAR(302273.28313290753, particleVect[1].fPressure.y, Precision);
    EXPECT_NEAR(270282.11371215997, particleVect[2].fPressure.x, Precision);
    EXPECT_NEAR(65196.02154430432, particleVect[2].fPressure.y, Precision);
    EXPECT_NEAR(-215404.63069230239, particleVect[3].fPressure.x, Precision);
    EXPECT_NEAR(-239510.54300795306, particleVect[3].fPressure.y, Precision);

    EXPECT_NEAR(0.0027413498259869526, particleVect[0].fViscosity.x, Precision);
    EXPECT_NEAR(-0.0078581489517066967, particleVect[0].fViscosity.y, Precision);
    EXPECT_NEAR(0.0027413498259869526, particleVect[1].fViscosity.x, Precision);
    EXPECT_NEAR(0.012737577937034811, particleVect[1].fViscosity.y, Precision);
    EXPECT_NEAR(-0.0077720829287022839, particleVect[2].fViscosity.x, Precision);
    EXPECT_NEAR(-0.0077733978979040866, particleVect[2].fViscosity.y, Precision);
    EXPECT_NEAR(0.0022884038491340335, particleVect[3].fViscosity.x, Precision);
    EXPECT_NEAR(0.0028877935702870837, particleVect[3].fViscosity.y, Precision);

    EXPECT_NEAR(14153.290448795125, particleVect[0].fInternal.x, Precision);
    EXPECT_NEAR(-127959.55522458498, particleVect[0].fInternal.y, Precision);
    EXPECT_NEAR(-68918.718495037523, particleVect[1].fInternal.x, Precision);
    EXPECT_NEAR(302273.29587048548, particleVect[1].fInternal.y, Precision);
    EXPECT_NEAR(270282.10594007705, particleVect[2].fInternal.x, Precision);
    EXPECT_NEAR(65196.013770906422, particleVect[2].fInternal.y, Precision);
    EXPECT_NEAR(-215404.62840389853, particleVect[3].fInternal.x, Precision);
    EXPECT_NEAR(-239510.54012015948, particleVect[3].fInternal.y, Precision);
}

void ForcesTestSuite::externalForcesForOneNeighbour()
{
    Particle particle1(SPHAlgorithms::Point3D(0.0, 0.0, 1.0), 0.01);
    Particle particle2(SPHAlgorithms::Point3D(0.0, 0.01, 1.0), 0.01);
    particle1.velocity = SPHAlgorithms::Point3D(0.1, 0.1, 1.0);
    particle2.velocity = SPHAlgorithms::Point3D(-0.1, -0.1, 1.0);
    particle1.neighbours = {1};
    particle2.neighbours = {0};

    ParticleVect particleVect = {particle1, particle2};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);
    Forces::ComputeInternalForces(particleVect);
    Forces::ComputeExternalForces(particleVect);

    // TODO: Recalculate expected values
    EXPECT_NEAR(0.0, particleVect[0].fSurfaceTension.x, Precision);
    EXPECT_NEAR(0.0, particleVect[0].fSurfaceTension.y, Precision);
    EXPECT_NEAR(0.0, particleVect[1].fSurfaceTension.x, Precision);
    EXPECT_NEAR(0.0, particleVect[1].fSurfaceTension.y, Precision);

    EXPECT_NEAR(0.0, particleVect[0].fExternal.x, Precision);
    EXPECT_NEAR(-509182.30561475095, particleVect[0].fExternal.y, Precision);
    EXPECT_NEAR(0.0, particleVect[1].fExternal.x, Precision);
    EXPECT_NEAR(-509182.30561475095, particleVect[1].fExternal.y, Precision);
}

void ForcesTestSuite::externalForcesForTwoNeighbours()
{
    Particle particle1(SPHAlgorithms::Point3D(3.0, 3.0, 1.0), 0.01);
    Particle particle2(SPHAlgorithms::Point3D(3.0, 3.01, 1.0), 0.01);
    Particle particle3(SPHAlgorithms::Point3D(3.005, 3.005, 1.0), 0.01);
    particle1.velocity = SPHAlgorithms::Point3D(0.1, 0.1, 1.0);
    particle2.velocity = SPHAlgorithms::Point3D(-0.1, -0.1, 1.0);
    particle3.velocity = SPHAlgorithms::Point3D(0.1, -0.1, 1.0);
    particle1.neighbours = {1, 2};
    particle2.neighbours = {0, 2};
    particle3.neighbours = {0, 1};

    ParticleVect particleVect = {particle1, particle2, particle3};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);
    Forces::ComputeInternalForces(particleVect);
    Forces::ComputeExternalForces(particleVect);

    // TODO: Recalculate expected values
    EXPECT_NEAR(0.0, particleVect[0].fSurfaceTension.x, Precision);
    EXPECT_NEAR(0.0, particleVect[0].fSurfaceTension.y, Precision);
    EXPECT_NEAR(0.0, particleVect[1].fSurfaceTension.x, Precision);
    EXPECT_NEAR(0.0, particleVect[1].fSurfaceTension.y, Precision);
    EXPECT_NEAR(0.0, particleVect[2].fSurfaceTension.x, Precision);
    EXPECT_NEAR(0.0, particleVect[2].fSurfaceTension.y, Precision);

    EXPECT_NEAR(0.0, particleVect[0].fExternal.x, Precision);
    EXPECT_NEAR(-1018579.8343480156, particleVect[0].fExternal.y, Precision);
    EXPECT_NEAR(0.0, particleVect[1].fExternal.x, Precision);
    EXPECT_NEAR(-1018579.8343480156, particleVect[1].fExternal.y, Precision);
    EXPECT_NEAR(0.0, particleVect[2].fExternal.x, Precision);
    EXPECT_NEAR(-1018795.0574665295, particleVect[2].fExternal.y, Precision);
}

void ForcesTestSuite::externalForcesForThreeNeighbours()
{
    Particle particle1(SPHAlgorithms::Point3D(3.0, 3.0, 1.0), 0.01);
    Particle particle2(SPHAlgorithms::Point3D(3.0, 3.01, 1.0), 0.01);
    Particle particle3(SPHAlgorithms::Point3D(3.005, 3.005, 1.0), 0.01);
    Particle particle4(SPHAlgorithms::Point3D(2.995, 2.996, 1.0), 0.01);
    particle1.velocity = SPHAlgorithms::Point3D(0.0, 0.1, 1.0);
    particle2.velocity = SPHAlgorithms::Point3D(0.0, -0.1, 1.0);
    particle3.velocity = SPHAlgorithms::Point3D(-0.1, -0.1, 1.0);
    particle4.velocity = SPHAlgorithms::Point3D(0.1, 0.1, 1.0);
    particle1.neighbours = {1, 2, 3};
    particle2.neighbours = {0, 2, 3};
    particle3.neighbours = {0, 1, 3};
    particle4.neighbours = {0, 1, 2};

    ParticleVect particleVect = {particle1, particle2, particle3, particle4};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);
    Forces::ComputeInternalForces(particleVect);
    Forces::ComputeExternalForces(particleVect);

    // TODO: Recalculate expected values
    EXPECT_NEAR(0.0, particleVect[0].fSurfaceTension.x, Precision);
    EXPECT_NEAR(0.0, particleVect[0].fSurfaceTension.y, Precision);
    EXPECT_NEAR(0.0, particleVect[1].fSurfaceTension.x, Precision);
    EXPECT_NEAR(0.0, particleVect[1].fSurfaceTension.y, Precision);
    EXPECT_NEAR(0.0, particleVect[2].fSurfaceTension.x, Precision);
    EXPECT_NEAR(0.0, particleVect[2].fSurfaceTension.y, Precision);
    EXPECT_NEAR(0.0, particleVect[3].fSurfaceTension.x, Precision);
    EXPECT_NEAR(0.0, particleVect[3].fSurfaceTension.y, Precision);

    EXPECT_NEAR(0.0, particleVect[0].fExternal.x, Precision);
    EXPECT_NEAR(-1528017.2447515146, particleVect[0].fExternal.y, Precision);
    EXPECT_NEAR(0, particleVect[1].fExternal.x, Precision);
    EXPECT_NEAR(-1527284.462122496, particleVect[1].fExternal.y, Precision);
    EXPECT_NEAR(0.0, particleVect[2].fExternal.x, Precision);
    EXPECT_NEAR(-1527650.9867321597, particleVect[2].fExternal.y, Precision);
    EXPECT_NEAR(0.0, particleVect[3].fExternal.x, Precision);
    EXPECT_NEAR(-1526997.9674436101, particleVect[3].fExternal.y, Precision);
}

void ForcesTestSuite::externalForcesForFiveNeighbours()
{
    Particle particle1(SPHAlgorithms::Point3D(3.0, 3.0, 1.0), 0.01);
    Particle particle2(SPHAlgorithms::Point3D(3.0, 3.02, 1.0), 0.01);
    Particle particle3(SPHAlgorithms::Point3D(3.02, 3.0, 1.0), 0.01);
    Particle particle4(SPHAlgorithms::Point3D(3.02, 3.02, 1.0), 0.01);
    Particle particle5(SPHAlgorithms::Point3D(3.01, 3.01, 1.0), 0.01);
    particle1.neighbours = {1, 2, 3, 4};
    particle2.neighbours = {0, 2, 3, 4};
    particle3.neighbours = {0, 1, 3, 4};
    particle4.neighbours = {0, 1, 2, 4};
    particle5.neighbours = {0, 1, 2, 3};

    particle1.velocity = SPHAlgorithms::Point3D(0.0, 0.1, 1.0);
    particle2.velocity = SPHAlgorithms::Point3D(0.0, -0.1, 1.0);
    particle3.velocity = SPHAlgorithms::Point3D(-0.1, -0.1, 1.0);
    particle4.velocity = SPHAlgorithms::Point3D(0.1, 0.1, 1.0);

    ParticleVect particleVect = {particle1, particle2, particle3, particle4, particle5};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);
    Forces::ComputeInternalForces(particleVect);
    Forces::ComputeExternalForces(particleVect);

    // TODO: Recalculate expected values
    EXPECT_NEAR(0.0, particleVect[0].fSurfaceTension.x, Precision);
}

void ForcesTestSuite::allForcesForOneNeighbour()
{
    Particle particle1(SPHAlgorithms::Point3D(3.0, 3.0, 1.0), 0.01);
    Particle particle2(SPHAlgorithms::Point3D(3.0, 3.01, 1.0), 0.01);
    particle1.velocity = SPHAlgorithms::Point3D(0.0, 0.1, 1.0);
    particle2.velocity = SPHAlgorithms::Point3D(0.0, -0.1, 1.0);
    particle1.neighbours = {1};
    particle2.neighbours = {0};

    ParticleVect particleVect = {particle1, particle2};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);
    Forces::ComputeInternalForces(particleVect);
    Forces::ComputeExternalForces(particleVect);
    Forces::ComputeAllForces(particleVect);

    // TODO: Recalculate expected values
    EXPECT_NEAR(0.0, particleVect[0].fTotal.x, Precision);
    EXPECT_NEAR(-627108.4871931473, particleVect[0].fTotal.y, Precision);
    EXPECT_NEAR(0.0, particleVect[1].fTotal.x, Precision);
    EXPECT_NEAR(-391256.12403635459, particleVect[1].fTotal.y, Precision);
}

void ForcesTestSuite::allForcesForTwoNeighbours()
{
    Particle particle1(SPHAlgorithms::Point3D(3.0, 3.0, 1.0), 0.01);
    Particle particle2(SPHAlgorithms::Point3D(3.0, 3.01, 1.0), 0.01);
    Particle particle3(SPHAlgorithms::Point3D(3.005, 3.005, 1.0), 0.01);
    particle1.velocity = SPHAlgorithms::Point3D(0.0, 0.1, 1.0);
    particle2.velocity = SPHAlgorithms::Point3D(0.0, -0.1, 1.0);
    particle3.velocity = SPHAlgorithms::Point3D(-0.1, -0.1, 1.0);
    particle1.neighbours = {1, 2};
    particle2.neighbours = {0, 2};
    particle3.neighbours = {0, 1};

    ParticleVect particleVect = {particle1, particle2, particle3};

    Forces::ComputeDensity(particleVect);
    Forces::ComputePressure(particleVect);
    Forces::ComputeInternalForces(particleVect);
    Forces::ComputeExternalForces(particleVect);
    Forces::ComputeAllForces(particleVect);

    // TODO: Recalculate expected values
    EXPECT_NEAR(-98578.368321782196, particleVect[0].fTotal.x, Precision);
    EXPECT_NEAR(-1236242.1174238357, particleVect[0].fTotal.y, Precision);
    EXPECT_NEAR(-98578.368321782196, particleVect[1].fTotal.x, Precision);
    EXPECT_NEAR(-800917.55949333042, particleVect[1].fTotal.y, Precision);
    EXPECT_NEAR(197198.39531995435, particleVect[2].fTotal.x, Precision);
    EXPECT_NEAR(-1018795.0492436577, particleVect[2].fTotal.y, Precision);
}

void ForcesTestSuite::allForcesForThreeNeighbours()
{
    Particle particle1(SPHAlgorithms::Point3D(3.0, 3.0, 1.0), 0.01);
    Particle particle2(SPHAlgorithms::Point3D(3.0, 3.01, 1.0), 0.01);
    Particle particle3(SPHAlgorithms::Point3D(3.005, 3.005, 1.0), 0.01);
    Particle particle4(SPHAlgorithms::Point3D(2.995, 2.996, 1.0), 0.01);
    particle1.velocity = SPHAlgorithms::Point3D(0.0, 0.1, 1.0);
    particle2.velocity = SPHAlgorithms::Point3D(0.0, -0.1, 1.0);
    particle3.velocity = SPHAlgorithms::Point3D(-0.1, -0.1, 1.0);
    particle4.velocity = SPHAlgorithms::Point3D(0.1, 0.1, 1.0);
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

    // TODO: Recalculate expected values
    EXPECT_NEAR(14153.287756039332, particleVect[0].fTotal.x, Precision);
    EXPECT_NEAR(-1655976.8026688555, particleVect[0].fTotal.y, Precision);
    EXPECT_NEAR(-68918.72178863344, particleVect[1].fTotal.x, Precision);
    EXPECT_NEAR(-1225011.1695456065, particleVect[1].fTotal.y, Precision);
    EXPECT_NEAR(270282.12377362541, particleVect[2].fTotal.x, Precision);
    EXPECT_NEAR(-1462454.9551277049, particleVect[2].fTotal.y, Precision);
    EXPECT_NEAR(-215404.640245886, particleVect[3].fTotal.x, Precision);
    EXPECT_NEAR(-1766508.5194057571, particleVect[3].fTotal.y, Precision);
}

} // namespace TestEnvironment
} // namespace SPHSDK

using namespace SPHSDK::TestEnvironment;

TEST(ForcesTestSuite, DISABLED_densityForFourNeighbours)
{
    ForcesTestSuite::densityForFourNeighbours();
}

TEST(ForcesTestSuite, DISABLED_pressureForFourNeighbours)
{
    ForcesTestSuite::pressureForFourNeighbours();
}

TEST(ForcesTestSuite, DISABLED_internalForcesForFourNeighbours)
{
    ForcesTestSuite::internalForcesForFourNeighbours();
}

TEST(ForcesTestSuite, DISABLED_externalForcesForFourNeighbours)
{
    ForcesTestSuite::externalForcesForFourNeighbours();
}

//---------------------------------------------

TEST(ForcesTestSuite, DISABLED_densityForOneNeighbour)
{
    ForcesTestSuite::densityForOneNeighbour();
}
TEST(ForcesTestSuite, DISABLED_densityForTwoNeighbours)
{
    ForcesTestSuite::densityForTwoNeighbours();
}
TEST(ForcesTestSuite, DISABLED_densityForThreeNeighbours)
{
    ForcesTestSuite::densityForThreeNeighbours();
}
TEST(ForcesTestSuite, DISABLED_pressureForOneNeighbour)
{
    ForcesTestSuite::pressureForOneNeighbour();
}
TEST(ForcesTestSuite, DISABLED_pressureForTwoNeighbours)
{
    ForcesTestSuite::pressureForTwoNeighbours();
}
TEST(ForcesTestSuite, DISABLED_pressureForThreeNeighbours)
{
    ForcesTestSuite::pressureForThreeNeighbours();
}
TEST(ForcesTestSuite, DISABLED_internalForcesForOneNeighbour)
{
    ForcesTestSuite::internalForcesForOneNeighbour();
}
TEST(ForcesTestSuite, DISABLED_internalForcesForTwoNeighbours)
{
    ForcesTestSuite::internalForcesForTwoNeighbours();
}
TEST(ForcesTestSuite, DISABLED_internalForcesForThreeNeighbours)
{
    ForcesTestSuite::internalForcesForThreeNeighbours();
}
TEST(ForcesTestSuite, DISABLED_externalForcesForOneNeighbour)
{
    ForcesTestSuite::externalForcesForOneNeighbour();
}
TEST(ForcesTestSuite, DISABLED_externalForcesForTwoNeighbours)
{
    ForcesTestSuite::externalForcesForTwoNeighbours();
}
TEST(ForcesTestSuite, DISABLED_externalForcesForThreeNeighbours)
{
    ForcesTestSuite::externalForcesForThreeNeighbours();
}
TEST(ForsesTestSuite, DISABLED_externalForcesForFiveNeighbours)
{
    ForcesTestSuite::externalForcesForFiveNeighbours();
}
TEST(ForcesTestSuite, DISABLED_allForcesForOneNeighbour)
{
    ForcesTestSuite::allForcesForOneNeighbour();
}
TEST(ForcesTestSuite, DISABLED_allForcesForTwoNeighbours)
{
    ForcesTestSuite::allForcesForTwoNeighbours();
}
TEST(ForcesTestSuite, DISABLED_allForcesForThreeNeighbours)
{
    ForcesTestSuite::allForcesForThreeNeighbours();
}
