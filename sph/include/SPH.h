/**
 * @file SPH.h
 * @author Anton Artyukh (artyukhanton@gmail.com)
 * @date Created June 12, 2017
 **/

#ifndef SPH_H_73C34465A6ED4DB9B9F2F4C3937BF5DC
#define SPH_H_73C34465A6ED4DB9B9F2F4C3937BF5DC

#include "algorithms/include/Area.h"
#include "algorithms/include/Defines.h"
#include "algorithms/include/NeighboursSearch.h"

#include "Particle.h"

namespace SPHSDK
{

class SPH
{
public:
    ParticleVect particles;

    SPH();

    void run();

private:

    SPHAlgorithms::Volume m_volume;

    SPHAlgorithms::NeighboursSearch3D<ParticleVect> m_searcher;

};

} // namespace SPHSDK

#endif // SPH_H_73C34465A6ED4DB9B9F2F4C3937BF5DC
