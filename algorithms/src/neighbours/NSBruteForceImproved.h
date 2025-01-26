#ifndef NS_BRUTE_FORCE_IMPROVED_H_48DCCF3737274ADE9B6EEF8BF6947A6E
#define NS_BRUTE_FORCE_IMPROVED_H_48DCCF3737274ADE9B6EEF8BF6947A6E

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

template <class T> class NSBruteForceImproved : public NeighbourSearchI<T>
{
    friend class TestEnvironment::NeighboursSearchTestSuite;

public:
    explicit NSBruteForceImproved(const Volume& volume, FLOAT radius, FLOAT eps);

    ~NSBruteForceImproved();

    void search(T& points);

private:
    Volume m_volume;

    FLOAT m_radius;

    FLOAT m_eps;
};
} // namespace SPHSDK

#include "NSBruteForceImproved.hpp"

#endif // NS_BRUTE_FORCE_IMPROVED_H_48DCCF3737274ADE9B6EEF8BF6947A6E
