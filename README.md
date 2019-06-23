# sph
[![Build Status](https://travis-ci.com/aartiukh/sph-sdk.svg?branch=develop)](https://travis-ci.com/aartiukh/sph-sdk) [![codecov](https://codecov.io/gh/aartiukh/sph/branch/develop/graph/badge.svg)](https://codecov.io/gh/aartiukh/sph) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/3ba389a156774edaa1152afd7c7504f7)](https://www.codacy.com/app/aartiukh/sph?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=aartiukh/sph-sdk&amp;utm_campaign=Badge_Grade) [![All Contributors](https://img.shields.io/badge/all_contributors-3-orange.svg?style=flat-square)](#contributors)

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

This project is maintained by teachers and students of Kharkiv National University of Radio Electronics ([NURE](https://nure.ua/en/)),  Department of Applied Mathematics ([AM](https://nure.ua/en/department/department-of-applied-mathematics-am)).

Thanks goes to these wonderful people ([emoji key](https://allcontributors.org/docs/en/emoji-key)):

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore -->
<table><tr><td align="center"><a href="https://github.com/aartiukh"><img src="https://avatars2.githubusercontent.com/u/6399458?v=4" width="100px;" alt="Anton Artiukh"/><br /><sub><b>Anton Artiukh</b></sub></a><br /><a href="https://github.com/aartiukh/sph/commits?author=aartiukh" title="Code">💻</a> <a href="https://github.com/aartiukh/sph/commits?author=aartiukh" title="Documentation">📖</a> <a href="#review-aartiukh" title="Reviewed Pull Requests">👀</a></td><td align="center"><a href="https://github.com/ShabalinOleksii"><img src="https://avatars2.githubusercontent.com/u/40167922?v=4" width="100px;" alt="Oleksii Shabalin"/><br /><sub><b>Oleksii Shabalin</b></sub></a><br /><a href="https://github.com/aartiukh/sph/commits?author=ShabalinOleksii" title="Code">💻</a> <a href="https://github.com/aartiukh/sph/commits?author=ShabalinOleksii" title="Documentation">📖</a></td><td align="center"><a href="https://github.com/Crosby98"><img src="https://avatars0.githubusercontent.com/u/49843837?v=4" width="100px;" alt="Crosby98"/><br /><sub><b>Igor Lytvyn</b></sub></a><br /><a href="https://github.com/aartiukh/sph/commits?author=Crosby98" title="Code">💻</a> <a href="https://github.com/aartiukh/sph/commits?author=Crosby98" title="Documentation">📖</a></td></tr></table>

<!-- ALL-CONTRIBUTORS-LIST:END -->

This project follows the [all-contributors](https://github.com/all-contributors/all-contributors) specification. Contributions of any kind welcome!
