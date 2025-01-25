/**
 * @file NSBruteForce.hpp
 * @author Anton Artiukh
 * @date Created Jan 25, 2025
 **/

#include "NSBruteForce.h"

namespace SPHSDK
{
template <class T>
NSBruteForce<T>::NSBruteForce(const Volume& volume, FLOAT radius, FLOAT eps)
    : m_volume(volume)
    , m_radius(radius)
    , m_eps(eps)
    , m_boxes(VectorOfSizetVectors())
    {
        const Cuboid cuboid = m_volume.getBoundingCuboid();

        m_cuboid = cuboid;

        m_normalizedCuboidWidth = static_cast<size_t>(m_cuboid.width / m_radius);
        m_normalizedCuboidLength = static_cast<size_t>(m_cuboid.length / m_radius);
        m_normalizedCuboidHeight = static_cast<size_t>(m_cuboid.height / m_radius); 

        m_boxesNumber = static_cast<size_t>(m_normalizedCuboidWidth *
                                            m_normalizedCuboidLength *
                                            m_normalizedCuboidHeight);
        m_boxes.resize(m_boxesNumber);
        m_nearbyBoxes.resize(m_boxesNumber);

        findNearbyBoxes();
    }

template <class T> NSBruteForce<T>::~NSBruteForce() = default;

template <class T> void NSBruteForce<T>::search(T& points)
{
}
} // namespace SPHSDK