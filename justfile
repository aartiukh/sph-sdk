set shell := ["powershell.exe", "-c"]

build-mingw:
    rmdir -Recurse build/* -Exclude .gitkeep
    cmake -G "MinGW Makefiles"  -DBUILD_UNIT_TESTS=ON -DCMAKE_BUILD_TYPE=Release -B build -S .
    cmake --build build --config Release -j 8

test:
    ctest -VV --test-dir build
