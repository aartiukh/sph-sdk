# sph
[![All Contributors](https://img.shields.io/badge/all_contributors-1-orange.svg?style=flat-square)](#contributors)

![Build status](https://travis-ci.com/aartiukh/sph.svg?branch=develop) [![codecov](https://codecov.io/gh/aartiukh/sph/branch/develop/graph/badge.svg)](https://codecov.io/gh/aartiukh/sph) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/85727c26d7fc4fd5b65e631e8a6aeca1)](https://app.codacy.com/app/aartiukh/sph?utm_source=github.com&utm_medium=referral&utm_content=aartiukh/sph&utm_campaign=Badge_Grade_Dashboard)

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

## Contributors

Thanks goes to these wonderful people ([emoji key](https://allcontributors.org/docs/en/emoji-key)):

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore -->
<table><tr><td align="center"><a href="https://github.com/aartiukh"><img src="https://avatars2.githubusercontent.com/u/6399458?v=4" width="100px;" alt="Anton Artiukh"/><br /><sub><b>Anton Artiukh</b></sub></a><br /><a href="https://github.com/aartiukh/sph/commits?author=aartiukh" title="Code">💻</a> <a href="https://github.com/aartiukh/sph/commits?author=aartiukh" title="Documentation">📖</a> <a href="#review-aartiukh" title="Reviewed Pull Requests">👀</a></td></tr></table>

<!-- ALL-CONTRIBUTORS-LIST:END -->

This project follows the [all-contributors](https://github.com/all-contributors/all-contributors) specification. Contributions of any kind welcome!