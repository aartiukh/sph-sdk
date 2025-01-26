#ifndef NS_BRUTE_FORCE_H_37DCCF3737274ADE9B6EEF8BF6947A6E
#define NS_BRUTE_FORCE_H_37DCCF3737274ADE9B6EEF8BF6947A6E

#include "Area.h"
#include "Defines.h"
#include "NeighbourSearchInterface.h"
#include "Point.h"

namespace SPHSDK
{

namespace TestEnvironment
{
class NeighboursSearchTestSuite;
} // namespace TestEnvironment

template <class T> class NSBruteForce : public NeighbourSearchI<T>
{
    friend class TestEnvironment::NeighboursSearchTestSuite;

public:
    explicit NSBruteForce(const Volume& volume, FLOAT radius, FLOAT eps);

    ~NSBruteForce();

    void search(T& points);

private:
    Volume m_volume;

    FLOAT m_radius;

    FLOAT m_eps;
};
} // namespace SPHSDK

#include "NSBruteForce.hpp"

#endif // NS_BRUTE_FORCE_H_37DCCF3737274ADE9B6EEF8BF6947A6E
