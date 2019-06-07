include(ExternalProject)

if (UNIX)
    ExternalProject_Add(freeglut-external
      PREFIX ${CMAKE_BINARY_DIR}/thirdparty
      URL ${PROJECT_SOURCE_DIR}/../thirdparty/freeglut
      CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/install -DFREEGLUT_BUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
      TEST_COMMAND ""
    )

    set(GLUT_LIBRARIES ${CMAKE_BINARY_DIR}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}glut${CMAKE_STATIC_LIBRARY_SUFFIX})
    set(GLUT_INCLUDE_DIR ${CMAKE_BINARY_DIR}/install/include)

elseif (WIN32)
    # https://www.transmissionzero.co.uk/files/software/development/GLUT/freeglut-MSVC.zip
    ExternalProject_Add(freeglut-external
      URL ${PROJECT_SOURCE_DIR}/../thirdparty/freeglut-MSVC-3.0.0-2.mp.zip
      CONFIGURE_COMMAND ""
      BUILD_COMMAND ""
      INSTALL_COMMAND ""
    )

    set(GLUT_LIBRARIES ${CMAKE_BINARY_DIR}/demo/freeglut-external-prefix/src/freeglut-external/lib/x64/${CMAKE_STATIC_LIBRARY_PREFIX}freeglut${CMAKE_STATIC_LIBRARY_SUFFIX})
    set(GLUT_INCLUDE_DIR ${CMAKE_BINARY_DIR}/demo/freeglut-external-prefix/src/freeglut-external/include)
    
    add_custom_command(
        TARGET freeglut-external POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_BINARY_DIR}/demo/freeglut-external-prefix/src/freeglut-external/bin/x64/freeglut.dll
                ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})

endif()
