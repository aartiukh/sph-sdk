/**
* @file Main.cpp
* @author Ihor Lytvyn(litvinigor98@gmail.com)
* @date Created May 26, 2019
**/

#include "MarchingCubesConfig.h"
#include "MarchingCubes.h"
#include "ROperations.h"
#include <cmath>

#include <iostream>

float omega(float x, float y, float z) 
{
	using namespace SPHAlgorithms;

	return ROperations::disjunction(
		ROperations::conjunction(
			ROperations::conjunction(0.25f - std::powf(x - 1.5f, 2.f) - std::powf(y - 1.5f, 2.f), - 20.f * (std::powf(x - 1.5f, 2.f) + std::powf(y - 1.5f, 2.f)) + 1.f + 10.f * std::powf(z - 0.75f, 2.f)),
		z * (1.f - z)),
		ROperations::disjunction(0.125f - std::powf(x - 1.5f, 2.f) - std::powf(y - 1.5f, 2.f) - 20.f * std::powf(1.f - z, 2.f),
			                     0.05f - std::powf(x - 1.5f, 2.f) - std::powf(y - 1.5f, 2.f) - std::powf(1.25f - z, 2.f)));
}

int main()
{
	SPHAlgorithms::MarchingCubes::generateObj(omega);

	return 0;
}