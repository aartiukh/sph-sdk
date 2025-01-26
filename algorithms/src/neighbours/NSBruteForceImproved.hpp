/**
 * @file NSBruteForce.hpp
 * @author Anton Artiukh
 * @date Created Jan 25, 2025
 **/

#include "NSBruteForceImproved.h"

#include <iostream>

namespace SPHSDK
{

template <class T>
NSBruteForceImproved<T>::NSBruteForceImproved(const Volume& volume, FLOAT radius, FLOAT eps)
    : m_volume(volume),
      m_radius(radius),
      m_eps(eps)
{
}

template <class T> NSBruteForceImproved<T>::~NSBruteForceImproved() = default;

template <class T> void NSBruteForceImproved<T>::search(T& points)
{
    for (size_t i = 0u; i < points.size(); ++i)
    {
        for (size_t j = i + 1u; j < points.size(); ++j)
        {
            const auto distanceSqr = (points[i].position - points[j].position).calcNormSqr();

            if (distanceSqr < pow(m_radius, 2) + DBL_EPSILON)
            {
                points[i].neighbours.push_back(j);
                points[j].neighbours.push_back(i);
            }
        }
    }
}

} // namespace SPHSDK
