cmake_minimum_required(VERSION 3.11)
project("HotBeanEngine")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type to Debug by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()
message(STATUS "Setting build type to '${CMAKE_BUILD_TYPE}'")

include(FetchContent)
# Turn off FetchContent for offline mode
set(FETCHCONTENT_FULLY_DISCONNECTED TRUE)
set(FETCHCONTENT_QUIET FALSE)
set(CMAKE_VERBOSE_MAKEFILE FALSE)

# Fetch glm
FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e #refs/tags/1.0.1
)
# Fetch SDL2
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.x
)

# Fetch SDL_ttf
FetchContent_Declare(
    SDL2TTF
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-2.22.0
)

# Fetch SDL_mixer
FetchContent_Declare(
    SDL2Mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG release-2.8.x
)

# Fetch SDL_Image
FetchContent_Declare(
    SDL2Image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-2.8.x
)

# Fetch yaml-cpp
FetchContent_Declare(
    yaml_cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    GIT_TAG yaml-cpp-0.7.0
)

set(SDL2TTF_VENDORED ON CACHE BOOL "Use vendored third-party libraries" FORCE)
set(SDL2MIXER_VENDORED ON CACHE BOOL "Use vendored third-party libraries" FORCE)
# set(SDL2TTF_HARFBUZZ OFF CACHE BOOL "Use harfbuzz to improve text shaping" FORCE)

FetchContent_MakeAvailable(glm SDL2 SDL2TTF SDL2Mixer SDL2Image yaml_cpp)

# Include directories
include_directories(
    ${SDL2_SOURCE_DIR}/include
    ${SDL2_ttf_SOURCE_DIR}
    ${SDL2_mixer_SOURCE_DIR}/include
    ${SDL2_image_SOURCE_DIR}/include
    ${glm_SOURCE_DIR}/glm
    src/core
)

message(STATUS "YAML: ${yaml_cpp_BINARY_DIR}")


add_library(${PROJECT_NAME} STATIC
    src
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    src
)

# Add source directories
add_subdirectory(src)