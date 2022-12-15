include(ExternalProject)

ExternalProject_Add(glfw-external
      PREFIX ${CMAKE_BINARY_DIR}/thirdparty
      URL ${PROJECT_SOURCE_DIR}/thirdparty/glfw
      CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/install -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
      TEST_COMMAND "")

set(GLFW_INCLUDE_DIR ${CMAKE_BINARY_DIR}/install/include)
set(GLFW_LIBRARY ${CMAKE_BINARY_DIR}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}glfw3${CMAKE_STATIC_LIBRARY_SUFFIX})