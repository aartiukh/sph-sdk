/**
 * @file NSBruteForce.h
 * @author Anton Artiukh
 * @date Created Jan 25, 2025
 **/

#ifndef NS_BRUTE_FORCE_H_37DCCF3737274ADE9B6EEF8BF6947A6E
#define NS_BRUTE_FORCE_H_37DCCF3737274ADE9B6EEF8BF6947A6E

#include "Area.h"
#include "Defines.h"
#include "NeighboursSearchInterface.h"
#include "Point.h"

namespace SPHSDK
{

namespace TestEnvironment
{
class NeighboursSearchTestSuite;
} // namespace TestEnvironment

template <class T> class NSBruteForce : public NeighboursSearchI<T>
{
    friend class TestEnvironment::NSBruteForceTestSuite;

public:
    explicit NSBruteForce(const Volume &volume, FLOAT radius, FLOAT eps);

    ~NSBruteForce();

    void search(T &points);

private:
    Volume m_volume;

    FLOAT m_radius;

    FLOAT m_eps;

    VectorOfSizetVectors m_boxes;
};
} // namespace SPHSDK

#include "NSBruteForce.hpp"

#endif // NS_BRUTE_FORCE_H_37DCCF3737274ADE9B6EEF8BF6947A6E
