/**
 * @file MarchingCubes.h
 * @author Ihor Lytvyn (litvinigor98@gmail.com)
 * @date Created May 26, 2019
 **/

#ifndef MARCHING_CUBES_H_43C34465A6ED4DB9B9F2F4C3937BF5DC
#define MARCHING_CUBES_H_43C34465A6ED4DB9B9F2F4C3937BF5DC

#include "vector"
#include <functional>

namespace SPHAlgorithms
{

/**
* @brief MarchingCubes class implements Marching Cubes algorithm.
*/
class MarchingCubes
{

public:
    /**
     * @brief Generates Obj file in Wavefront format with mesh
     * @param f    The function that represents the domain equation
     */
    static void generateObj(std::function<float(float, float, float)> f);

private:
    struct V3;

    static std::vector<V3> MarchCube(std::function<float(float, float, float)> f, float fX, float fY, float fZ);

    static void generateObjFile(const std::vector<V3>& vertices, const std::string& fileName);
};

} // namespace SPHAlgorithms

#endif // MARCHING_CUBES_H_43C34465A6ED4DB9B9F2F4C3937BF5DC
