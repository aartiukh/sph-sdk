# sph

![Build status](https://travis-ci.com/aartiukh/sph.svg?branch=develop) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/85727c26d7fc4fd5b65e631e8a6aeca1)](https://app.codacy.com/app/aartiukh/sph?utm_source=github.com&utm_medium=referral&utm_content=aartiukh/sph&utm_campaign=Badge_Grade_Dashboard)

C++ implementation of Smoothed Particle Hydrodynamics.

## How to build

### Ubuntu

* `sudo apt-get install libxtst-dev libxrandr-dev`
* `cd build`
* `cmake -DBUILD_UNIT_TESTS=ON -DCMAKE_BUILD_TYPE=Release ..`
*  `make -j`

### Windows MSVC 2017
* `cd build`
* `cmake -G "Visual Studio 15 2017 Win64" -DBUILD_UNIT_TESTS=ON -DCMAKE_BUILD_TYPE=Release ..`
*  Open generated `sph-sdk.sln` and run `Build Solution` in MSVC 2017 IDE

### How to test
* `ctest -VV`
