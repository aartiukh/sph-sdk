#include "NSBruteForce.h"

#include <iostream>

namespace SPHSDK
{

template <class T>
NSBruteForce<T>::NSBruteForce(const Volume& volume, FLOAT radius, FLOAT eps)
    : m_volume(volume),
      m_radius(radius),
      m_eps(eps)
{
}

template <class T> NSBruteForce<T>::~NSBruteForce() = default;

template <class T> void NSBruteForce<T>::search(T& points)
{
    for (size_t i = 0u; i < points.size(); ++i)
    {
        for (size_t j = 0u; j < points.size(); ++j)
        {
            if (i == j)
            {
                continue;
            }

            const auto distanceSqr = (points[i].position - points[j].position).calcNormSqr();

            if (distanceSqr < pow(m_radius, 2) + DBL_EPSILON)
            {
                points[i].neighbours.push_back(j);
            }
        }
    }
}

} // namespace SPHSDK
