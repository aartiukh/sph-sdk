set(SPH_LIB_NAME sph)

file(GLOB SPH_SRC_LIST_INCLUDE "src/Particle.h"
                               "src/Collisions.h"
                               "src/Forces.h"
                               "src/Config.h"
                               "src/Integrator.h"
                               "src/SPH.h")

file(GLOB SPH_SRC_LIST_SOURCE  "src/Particle.cpp"
                               "src/Collisions.cpp"
                               "src/Config.cpp"
                               "src/Forces.cpp"
                               "src/Integrator.cpp"
                               "src/SPH.cpp")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

if(BUILD_UNIT_TESTS)
    # TODO: fix unit tests after migration to 3D
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif()

add_library(${SPH_LIB_NAME} ${SPH_SRC_LIST_INCLUDE} ${SPH_SRC_LIST_SOURCE})
target_link_libraries(${SPH_LIB_NAME} algorithms)
