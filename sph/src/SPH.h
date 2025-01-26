/**
 * @file SPH.h
 * @author Anton Artyukh (artyukhanton@gmail.com)
 * @date Created June 12, 2017
 **/

#ifndef SPH_H_73C34465A6ED4DB9B9F2F4C3937BF5DC
#define SPH_H_73C34465A6ED4DB9B9F2F4C3937BF5DC

#include "Particle.h"

#include "Area.h"
#include "Defines.h"
#include "NSGridBasedOld.h"

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

    NSGridBasedOld<ParticleVect> m_searcher;

    const std::function<FLOAT(FLOAT, FLOAT, FLOAT)>* m_obstacle;
};

} // namespace SPHSDK

#endif // SPH_H_73C34465A6ED4DB9B9F2F4C3937BF5DC
