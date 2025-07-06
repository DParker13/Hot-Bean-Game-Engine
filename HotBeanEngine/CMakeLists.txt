# Project settings
project(HotBeanEngine)

# C++ standard and build type
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()
message(STATUS "Setting build type to '${CMAKE_BUILD_TYPE}'")

# Build settings
set(BUILD_SHARED_LIBS OFF)

# FetchContent settings
include(FetchContent)
set(FETCHCONTENT_FULLY_DISCONNECTED TRUE)
set(FETCHCONTENT_QUIET FALSE)
set(CMAKE_VERBOSE_MAKEFILE FALSE)

# Fetch dependencies
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)

FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.x
)

FetchContent_Declare(
    SDL2TTF
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-2.22.0
)

FetchContent_Declare(
    SDL2Mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG release-2.8.x
)

FetchContent_Declare(
    SDL2Image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-2.8.x
)

FetchContent_Declare(
    yaml_cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    GIT_TAG 0.8.0
)

# Testing settings
option(GAME_BUILD_TESTING "${PROJECT_NAME}: Build tests" ON)

if(GAME_BUILD_TESTING)
    FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.8.1
    )
    FetchContent_MakeAvailable(catch2)
    include_directories(${catch2_SOURCE_DIR}/src)
endif()

# Dependency settings
set(SDL_SHARED OFF CACHE BOOL "Build SDL as a shared library" FORCE)
set(SDL_STATIC ON CACHE BOOL "Build a static version of the library" FORCE)
set(YAML_BUILD_SHARED_LIBS OFF CACHE BOOL "Build yaml-cpp shared library" FORCE)

set(SDL2TTF_VENDORED ON CACHE BOOL "Use vendored third-party libraries" FORCE)
set(SDL2MIXER_VENDORED ON CACHE BOOL "Use vendored third-party libraries" FORCE)
# SDL2Image hasn't been implemented yet
# set(SDL2IMAGE_VENDORED ON CACHE BOOL "Use vendored third-party libraries" FORCE)

# Make dependencies available
FetchContent_MakeAvailable(glm SDL2 SDL2TTF SDL2Mixer SDL2Image yaml_cpp)

# Include directories
include_directories(
    ${SDL2_SOURCE_DIR}/include
    ${SDL2_ttf_SOURCE_DIR}
    ${SDL2_mixer_SOURCE_DIR}/include
    ${SDL2_image_SOURCE_DIR}/include
    ${glm_SOURCE_DIR}/glm
)

# Platform-specific settings
if(WIN32)
    set(HAVE_STRINGS_H 0 CACHE INTERNAL "Windows doesn't have strings.h" FORCE)
endif()

# Library settings
add_library(${PROJECT_NAME} SHARED
    src/game
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    base_game
    SDL2::SDL2main
)

# Compiler-specific settings
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_options(${PROJECT_NAME} PUBLIC
        -mwindows
        -static-libstdc++ -static-libgcc
    )
endif()

# Add subdirectories
add_subdirectory(src/core)
add_subdirectory(src/game)

if(GAME_BUILD_TESTING)
    message(STATUS "${PROJECT_NAME}: Building tests")
    # list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

    enable_testing()
    add_subdirectory(src/unit_tests)
endif()