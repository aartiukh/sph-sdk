project(sph)
cmake_minimum_required(VERSION 3.1)

file(GLOB SPH_SRC_LIST_INCLUDE "${PROJECT_SOURCE_DIR}/src/Particle.h"
                               "${PROJECT_SOURCE_DIR}/src/Collisions.h"
                               "${PROJECT_SOURCE_DIR}/src/Forces.h"
                               "${PROJECT_SOURCE_DIR}/src/Config.h"
                               "${PROJECT_SOURCE_DIR}/src/Integrator.h"
                               "${PROJECT_SOURCE_DIR}/src/SPH.h")

file(GLOB SPH_SRC_LIST_SOURCE  "${PROJECT_SOURCE_DIR}/src/Particle.cpp"
                               "${PROJECT_SOURCE_DIR}/src/Collisions.cpp"
                               "${PROJECT_SOURCE_DIR}/src/Config.cpp"
                               "${PROJECT_SOURCE_DIR}/src/Forces.cpp"
                               "${PROJECT_SOURCE_DIR}/src/Integrator.cpp"
                               "${PROJECT_SOURCE_DIR}/src/SPH.cpp")

include_directories(${PROJECT_SOURCE_DIR}/src)

if(BUILD_UNIT_TESTS)
    # TODO: fix unit tests after migration to 3D
    add_subdirectory(${PROJECT_SOURCE_DIR}/test)
endif()

add_library(${PROJECT_NAME} ${SPH_SRC_LIST_INCLUDE} ${SPH_SRC_LIST_SOURCE})
target_link_libraries(${PROJECT_NAME} algorithms)
