project(sph-demo)
cmake_minimum_required(VERSION 3.1)

file(GLOB SPH_DEMO_SRC_LIST_SOURCE  "${PROJECT_SOURCE_DIR}/src/main.cpp"
                                    "${PROJECT_SOURCE_DIR}/src/Draw.cpp")

file(GLOB SPH_DEMO_INC_LIST_SOURCE  "${PROJECT_SOURCE_DIR}/src/Draw.h")

find_package(OpenGL REQUIRED)
find_package(FreeGlutBuild REQUIRED)

include_directories(${GLUT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SPH_DEMO_SRC_LIST_SOURCE} ${SPH_DEMO_INC_LIST_SOURCE})
target_link_libraries(${PROJECT_NAME} algorithms sph ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})
if (UNIX)
    target_link_libraries(${PROJECT_NAME} X11 Xrandr Xxf86vm Xi)
endif()

add_dependencies(${PROJECT_NAME} freeglut-external)
