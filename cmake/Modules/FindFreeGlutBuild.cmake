include(ExternalProject)

ExternalProject_Add(freeglut-external
  PREFIX ${CMAKE_BINARY_DIR}/thirdparty
  URL ${PROJECT_SOURCE_DIR}/../thirdparty/freeglut
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/install
  TEST_COMMAND ""
)

# Export
set(GLUT_LIBRARIES ${CMAKE_BINARY_DIR}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}glut${CMAKE_STATIC_LIBRARY_SUFFIX})
set(GLUT_INCLUDE_DIR ${CMAKE_BINARY_DIR}/install/include)
