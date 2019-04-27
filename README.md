# sph
C++ implementation of Smoothed Particle Hydrodynamics.

![Build status](https://travis-ci.com/aartiukh/sph.svg?branch=develop)

# How to build

## Ubuntu

* `sudo apt-get install libxtst-dev libxrandr-dev`
* `cd build`
* `cmake -DBUILD_UNIT_TESTS=ON -DCMAKE_BUILD_TYPE=Release ..`
*  `make -j`

## Windows MSVC 2017
* `cd build`
* `cmake -G "Visual Studio 15 2017 Win64" -DBUILD_UNIT_TESTS=ON -DCMAKE_BUILD_TYPE=Release ..`
*  Open generated `sph-sdk.sln` and run `Build Solution` in MSVC 2017 IDE 
