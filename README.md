# sph

[![CMake](https://github.com/aartiukh/sph-sdk/actions/workflows/cmake.yml/badge.svg?branch=develop)](https://github.com/aartiukh/sph-sdk/actions/workflows/cmake.yml) [![codecov](https://codecov.io/gh/aartiukh/sph-sdk/branch/develop/graph/badge.svg)](https://codecov.io/gh/aartiukh/sph-sdk)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/610f12b0ffcf48ff98d202fe4029f605)](https://www.codacy.com/gh/aartiukh/sph-sdk/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=aartiukh/sph-sdk&amp;utm_campaign=Badge_Grade) [!

C++ implementation of Smoothed Particle Hydrodynamics.

## How to build

### Ubuntu

* `sudo apt-get install libxtst-dev libxrandr-dev libxxf86vm-dev`
* `cd build`
* `cmake -DBUILD_UNIT_TESTS=ON -DCMAKE_BUILD_TYPE=Release ..`
* `make -j`

### Windows MSVC 2017

* `cd build`
* `cmake -G "Visual Studio 15 2017 Win64" -DBUILD_UNIT_TESTS=ON -DCMAKE_BUILD_TYPE=Release ..`
* Open generated `sph-sdk.sln` and run `Build Solution` in MSVC 2017 IDE

### Windows MSVC 2019

* `cd build`
* `cmake -G "Visual Studio 16 2019" -A x64 -DBUILD_UNIT_TESTS=ON -DCMAKE_BUILD_TYPE=Release ..`
* Open generated `sph-sdk.sln` and run `Build Solution` in MSVC 2019 IDE

### Windows MinGW

* `cd build`
* `cmake -G "MinGW Makefiles"  -DBUILD_UNIT_TESTS=ON -DCMAKE_BUILD_TYPE=Release ..`
* `cmake --build . --config Release -j8`

### Mac OS

* `cd build`
* `cmake -DBUILD_UNIT_TESTS=ON -DCMAKE_BUILD_TYPE=Release ..`
* `make -j`

### How to test

* `ctest -VV`
