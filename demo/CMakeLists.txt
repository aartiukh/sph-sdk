file(GLOB SPH_DEMO_SRC_LIST_SOURCE  "src/main.cpp"
                                    "src/Draw.cpp")

file(GLOB SPH_DEMO_INC_LIST_SOURCE  "src/Draw.h")

find_package(OpenGL REQUIRED)
find_package(BuildGLFW REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(${GLFW_INCLUDE_DIR} ${GLFW_DEPS_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SPH_DEMO_SRC_LIST_SOURCE} ${SPH_DEMO_INC_LIST_SOURCE})
target_link_libraries(${PROJECT_NAME} algorithms sph ${GLFW_LIBRARY} ${OPENGL_LIBRARIES})

if (APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IO_KIT_LIBRARY IOKit)
    target_link_libraries(${PROJECT_NAME} ${COCOA_LIBRARY} ${IO_KIT_LIBRARY})
elseif (UNIX) 
    target_link_libraries(${PROJECT_NAME} X11 Xrandr Xxf86vm Xi Threads::Threads ${CMAKE_DL_LIBS})
endif()

add_dependencies(${PROJECT_NAME} glfw-external)
