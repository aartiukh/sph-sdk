/**
* @file Defines.h
* @author Anton Artyukh (artyukhanton@gmail.com)
* @date Created Feb 26, 2017
**/

#ifndef DEFINES_H_B25DE75875BB40248241AD0DFE5A69FC
#define DEFINES_H_B25DE75875BB40248241AD0DFE5A69FC

#include <vector>
#include <cstddef>
#include <cfloat>

namespace SPHSDK
{
    // Float precision to be used in all algorithims
    using FLOAT = float;

    using SizetVector = std::vector<size_t>;

    using VectorOfSizetVectors = std::vector<SizetVector>;

} // SPHSDK

#endif // DEFINES_H_B25DE75875BB40248241AD0DFE5A69FC
