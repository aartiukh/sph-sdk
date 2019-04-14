project(sph-demo)
cmake_minimum_required(VERSION 2.8)

file(GLOB SPH_DEMO_SRC_LIST_SOURCE  "${PROJECT_SOURCE_DIR}/src/main.cpp"
                                    "${PROJECT_SOURCE_DIR}/src/Draw.cpp")

file(GLOB SPH_DEMO_INC_LIST_SOURCE  "${PROJECT_SOURCE_DIR}/src/Draw.h")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${GLUT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SPH_DEMO_SRC_LIST_SOURCE} ${SPH_DEMO_INC_LIST_SOURCE})
target_link_libraries(${PROJECT_NAME} algorithms sph ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})
