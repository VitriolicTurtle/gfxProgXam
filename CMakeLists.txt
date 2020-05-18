cmake_minimum_required (VERSION 3.14 FATAL_ERROR)
project(springExam2020 VERSION 2.0.0)

# Add dependencies
add_subdirectory(external)

# Create .exe file (essentially)
add_executable(${PROJECT_NAME})

# Add additional source files here
target_sources(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp

    ${CMAKE_CURRENT_LIST_DIR}/include/game.h
    ${CMAKE_CURRENT_LIST_DIR}/src/game.cpp

    ${CMAKE_CURRENT_LIST_DIR}/include/renderer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/renderer.cpp

    ${CMAKE_CURRENT_LIST_DIR}/include/player.h
    ${CMAKE_CURRENT_LIST_DIR}/src/player.cpp

    ${CMAKE_CURRENT_LIST_DIR}/include/maploader.h
    ${CMAKE_CURRENT_LIST_DIR}/src/maploader.cpp

    ${CMAKE_CURRENT_LIST_DIR}/include/wallobj.h
    ${CMAKE_CURRENT_LIST_DIR}/src/wallobj.cpp

    ${CMAKE_CURRENT_LIST_DIR}/include/shader.h
    ${CMAKE_CURRENT_LIST_DIR}/src/shader.cpp

    ${CMAKE_CURRENT_LIST_DIR}/include/texture.h
    ${CMAKE_CURRENT_LIST_DIR}/src/texture.cpp

    ${CMAKE_CURRENT_LIST_DIR}/include/constants.h
    ${CMAKE_CURRENT_LIST_DIR}/src/constants.cpp

    ${CMAKE_CURRENT_LIST_DIR}/include/window.h
    ${CMAKE_CURRENT_LIST_DIR}/src/window.cpp

    ${CMAKE_CURRENT_LIST_DIR}/include/mapobj.h

)

# Set include directories
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# Link with external libraries
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    glad::glad
    gfx::gfx
    glm
    glfw
    stbimage::stbimage
    tinyobj::tinyobj
)

# Enable C++ 17
target_compile_features(
    ${PROJECT_NAME}
    PRIVATE
    cxx_std_17
)

# Copy resources to binary directory
add_custom_target(
    copy_shaders ALL
    ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources
    COMMAND ${CMAKE_COMMAND} -E echo "Copied resource directory to binary directory ${CMAKE_CURRENT_BINARY_DIR}"
)

