project("HotBeanEngine")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type to Debug by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()
message(STATUS "Setting build type to '${CMAKE_BUILD_TYPE}'")

set(BUILD_SHARED_LIBS OFF)

include(FetchContent)
# Turn off FetchContent for offline mode
set(FETCHCONTENT_FULLY_DISCONNECTED TRUE)
set(FETCHCONTENT_QUIET FALSE)
set(CMAKE_VERBOSE_MAKEFILE FALSE)

# Fetch glm
FetchContent_Declare(
	glm
	GIT_REPOSITORY https://github.com/g-truc/glm.git
	GIT_TAG 1.0.1
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
    GIT_TAG 0.8.0
)

# Fetch Catch2
FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.8.1
)

# Set all third-party libraries to static
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(YAML_BUILD_SHARED_LIBS OFF)

set(SDL2TTF_VENDORED ON CACHE BOOL "Use vendored third-party libraries" FORCE)
# set(SDL2TTF_HARFBUZZ OFF CACHE BOOL "Use harfbuzz to improve text shaping" FORCE)
set(SDL2MIXER_VENDORED ON CACHE BOOL "Use vendored third-party libraries" FORCE)

# SDL2Image hasn't been implemented yet
# set(SDL2IMAGE_VENDORED ON CACHE BOOL "Use vendored third-party libraries" FORCE)

FetchContent_MakeAvailable(glm SDL2 SDL2TTF SDL2Mixer SDL2Image yaml_cpp catch2)

# Find catch2 tests and add them to the build
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

# Include directories
include_directories(
    ${SDL2_SOURCE_DIR}/include
    ${SDL2_ttf_SOURCE_DIR}
    ${SDL2_mixer_SOURCE_DIR}/include
    ${SDL2_image_SOURCE_DIR}/include
    ${glm_SOURCE_DIR}/glm
    ${catch2_SOURCE_DIR}/src
)

add_library(${PROJECT_NAME} SHARED
    src/game
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    base_game
    SDL2::SDL2main
)

# Only add these if using GCC/MinGW
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_options(${PROJECT_NAME} PUBLIC
        -mwindows
        -static-libstdc++ -static-libgcc
    )
endif()

# Add subdirectories for project modules
add_subdirectory(src/core)
add_subdirectory(src/archetypes)
add_subdirectory(src/game)