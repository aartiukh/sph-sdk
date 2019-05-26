/**
* @file MarchingCubes.h
* @author Ihor Lytvyn(litvinigor98@gmail.com)
* @date Created May 26, 2019
**/

#ifndef MARCHING_CUBES_H_43C34465A6ED4DB9B9F2F4C3937BF5DC
#define MARCHING_CUBES_H_43C34465A6ED4DB9B9F2F4C3937BF5DC

#include <functional>
#include "vector"


namespace SPHAlgorithms
{
	struct V3 {
		float x, y, z; // x, y, z axis point

		V3() {
			x = 0.f;
			y = 0.f;
			z = 0.f;
		}

		V3(float _x, float _y, float _z) {
			x = _x;
			y = _y;
			z = _z;
		}
	};

	class MarchingCubes {

	public:
		static void generateObj(std::function<float(float,float,float)> f);

	private:
		static std::vector<V3> MarchCube(std::function<float(float, float, float)> f, float fX, float fY, float fZ);

		static void generateObjFile(const std::vector<V3>& vertices, const std::string& fileName);
	};


} //SPHAlgorithms

#endif // MARCHING_CUBES_H_43C34465A6ED4DB9B9F2F4C3937BF5DC
