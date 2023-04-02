/**
 * @file SPH.h
 * @author Anton Artyukh (artyukhanton@gmail.com)
 * @date Created June 12, 2017
 **/

#ifndef SPH_H_73C34465A6ED4DB9B9F2F4C3937BF5DC
#define SPH_H_73C34465A6ED4DB9B9F2F4C3937BF5DC

#include "Particle.h"

#include "algorithms/src/Area.h"
#include "algorithms/src/Defines.h"
#include "algorithms/src/NeighboursSearch.h"

#include <functional>

namespace SPHSDK
{

class SPH
{
public:
    SPH(const std::function<FLOAT(FLOAT, FLOAT, FLOAT)>* obstacle = nullptr);

    void run();

public:
    ParticleVect particles;

private:
    Volume m_volume;

    NeighboursSearch3D<ParticleVect> m_searcher;

    const std::function<FLOAT(FLOAT, FLOAT, FLOAT)>* m_obstacle;
};

} // namespace SPHSDK

#endif // SPH_H_73C34465A6ED4DB9B9F2F4C3937BF5DC
