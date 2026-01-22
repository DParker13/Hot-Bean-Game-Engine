cmake_minimum_required(VERSION 3.18)
project(HotBeanEngine LANGUAGES CXX)

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
set(FETCHCONTENT_QUIET TRUE)

# Fetch dependencies
FetchContent_Declare(
    GLM
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG main # A stable release should be used when ver 3.4.0 releases!!!
)

FetchContent_Declare(
    SDL3_TTF
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-3.2.x
)

FetchContent_Declare(
    SDL3_MIXER
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG main
)

FetchContent_Declare(
    SDL3_IMAGE
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-3.2.x
)

FetchContent_Declare(
    YAML_CPP
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    GIT_TAG master # A stable release should be used when one is released
)

FetchContent_Declare(
    BOX2D
    GIT_REPOSITORY https://github.com/erincatto/box2d.git
    GIT_TAG v3.1.1
)

FetchContent_Declare(
    IMGUI
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG docking
)

# Testing settings
option(GAME_BUILD_TESTING "${PROJECT_NAME}: Build tests" ON)

# Dependency settings
set(SDL_SHARED OFF CACHE BOOL "Build SDL as a shared library" FORCE)
set(SDL_STATIC ON CACHE BOOL "Build a static version of the library" FORCE)
set(YAML_BUILD_SHARED_LIBS OFF CACHE BOOL "Build yaml-cpp shared library" FORCE)
add_definitions(-DYAML_CPP_STATIC_DEFINE)
# set(SIZEOF_OFF_T 4 CACHE INTERNAL "Force off_t to be 32 bits" FORCE)

# Vendored settings
set(SDLTTF_VENDORED ON CACHE BOOL "Use vendored third-party libraries" FORCE)
set(SDLMIXER_VENDORED ON CACHE BOOL "Use vendored third-party libraries" FORCE)
set(SDL3IMAGE_VENDORED ON CACHE BOOL "Use vendored third-party libraries" FORCE)
set(SDLIMAGE_AVIF OFF CACHE BOOL "Support loading AVIF images" FORCE)

# Fetch dependencies
FetchContent_MakeAvailable(GLM SDL3 SDL3_TTF SDL3_IMAGE SDL3_MIXER YAML_CPP BOX2D IMGUI)

# Platform-specific settings
if(WIN32)
    set(HAVE_STRINGS_H 0 CACHE INTERNAL "Windows doesn't have strings.h" FORCE)
endif()

# Add subdirectories
add_subdirectory(src/application)
add_subdirectory(src/defaults)
add_subdirectory(src/editor_gui)

# Compiler-specific settings
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(WIN32 AND NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_link_options(HotBeanEngine_Application PUBLIC -mwindows)
    endif()
    target_link_options(HotBeanEngine_Application PUBLIC -static-libstdc++ -static-libgcc)
endif()

if(GAME_BUILD_TESTING)
    message(STATUS "${PROJECT_NAME}: Building tests")
    FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.8.1
    )
    FetchContent_MakeAvailable(catch2)
    
    add_subdirectory(src/unit_tests)
endif()