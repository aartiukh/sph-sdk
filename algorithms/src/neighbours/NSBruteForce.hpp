/**
 * @file NSBruteForce.hpp
 * @author Anton Artiukh
 * @date Created Jan 25, 2025
 **/

#include "NSBruteForce.h"

namespace SPHSDK
{

template <class T>
NSBruteForce<T>::NSBruteForce(const Volume &volume, FLOAT radius, FLOAT eps)
    : m_volume(volume),
      m_radius(radius),
      m_eps(eps),
      m_boxes(VectorOfSizetVectors())
{
}

template <class T> NSBruteForce<T>::~NSBruteForce() = default;

template <class T> void NSBruteForce<T>::search(T &points)
{
}

} // namespace SPHSDK
