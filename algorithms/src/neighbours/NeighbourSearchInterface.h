#ifndef NEIGHBOUR_SEARCH_INTERFACE_H_27DCCF3737274ADE9B6EEF8BF6947A6A
#define NEIGHBOUR_SEARCH_INTERFACE_H_27DCCF3737274ADE9B6EEF8BF6947A6A

namespace SPHSDK
{

/// @brief Interface for searching neighbours.
/// @tparam T
template <class T> class NeighbourSearchI
{
public:
    /// @brief Search for neighbours for every point in points.
    /// @param points Points to search neighbours for.
    virtual void search(T& points) = 0;
};

} // namespace SPHSDK

#endif // NEIGHBOUR_SEARCH_INTERFACE_H_27DCCF3737274ADE9B6EEF8BF6947A6A
