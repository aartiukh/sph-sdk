file(GLOB SPH_DEMO_SRC_LIST_SOURCE  "src/main.cpp"
                                    "src/Draw.cpp")

file(GLOB SPH_DEMO_INC_LIST_SOURCE  "src/Draw.h")

find_package(OpenGL REQUIRED)
find_package(BuildGLFW REQUIRED)

include_directories(${GLFW_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SPH_DEMO_SRC_LIST_SOURCE} ${SPH_DEMO_INC_LIST_SOURCE})
target_link_libraries(${PROJECT_NAME} algorithms sph ${GLFW_LIBRARY} ${OPENGL_LIBRARIES})
# if (UNIX) 
#    target_link_libraries(${PROJECT_NAME} X11 Xrandr Xxf86vm Xi)
# endif()

add_dependencies(${PROJECT_NAME} glfw-external)
