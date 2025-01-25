/**
 * @file NeighboursSearchInterface.h
 * @author Anton Artiukh
 * @date Created Jan 25, 2025
 **/

#ifndef NEIGHBOURS_SEARCH_INTERFACE_H_27DCCF3737274ADE9B6EEF8BF6947A6A
#define NEIGHBOURS_SEARCH_INTERFACE_H_27DCCF3737274ADE9B6EEF8BF6947A6A

namespace SPHSDK
{

template <class T> class NeighboursSearchI
{
public:
    virtual void search(T& points) = 0;
};

} // namespace SPHSDK

#endif // NEIGHBOURS_SEARCH_INTERFACE_H_27DCCF3737274ADE9B6EEF8BF6947A6A
