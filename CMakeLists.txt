cmake_minimum_required(VERSION 3.11) # FetchContent is new in version 3.11.
project("HotBeanEngine")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the number of threads for parallel building
if(NOT CMAKE_BUILD_PARALLEL_LEVEL)
    set(CMAKE_BUILD_PARALLEL_LEVEL 4)
endif()

# Set build type to Debug by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

message(STATUS "Setting build type to '${CMAKE_BUILD_TYPE}'")

include(FetchContent)
# Turn off FetchContent for offline mode
set(FETCHCONTENT_FULLY_DISCONNECTED OFF)
set(FETCHCONTENT_QUIET FALSE)

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

set(SDL2TTF_VENDORED ON CACHE BOOL "Use vendored third-party libraries" FORCE)
# set(SDL2TTF_HARFBUZZ OFF CACHE BOOL "Use harfbuzz to improve text shaping" FORCE)

FetchContent_MakeAvailable(glm SDL2 SDL2TTF)

# Manually setting SDL2_TTF Source Dir because FetchContent doesn't set it for whatever reason
set(SDL2TTF_SOURCE_DIR ${CMAKE_BINARY_DIR}/_deps/sdl2ttf-src)
set(SDL2TTF_BINARY_DIR ${CMAKE_BINARY_DIR}/_deps/sdl2ttf-build)

add_executable(${PROJECT_NAME} src/main.cpp)

# Include directories for the executable
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/FastNoiseLite
    ${SDL2_SOURCE_DIR}/include
    ${SDL2TTF_SOURCE_DIR}
    ${glm_SOURCE_DIR}/glm
)

# Add subdirectories for project modules
add_subdirectory(src/core)
add_subdirectory(src/managers)
add_subdirectory(src/components)
add_subdirectory(src/systems)
add_subdirectory(src/gameobjects)
add_subdirectory(src/application)

# Link libraries
message(STATUS "Linking Libraries!!!!!!!!!!!!!!!!!!!!!!!")

if (WIN32)
    # If DEBUG is ON, we disable the linker flags
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(STATUS "Debug mode is enabled, no additional linker flags")
        target_link_libraries(${PROJECT_NAME} PRIVATE
            SDL2
            SDL2main
            core
            systems
            application
        )
    else()
        message(STATUS "Debug mode is disabled, applying linker flags")
        target_link_libraries(${PROJECT_NAME} PRIVATE
            SDL2
            SDL2main
            core
            systems
            application
            ${CMAKE_LINKER_FLAGS} -Wl,-subsystem,windows
        )
    endif()
else ()
    target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2
        core
        systems
        application
    )
endif()

# Copy SDL2 DLLs to build directory
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${SDL2_BINARY_DIR}/SDL2.dll
                ${SDL2_BINARY_DIR}/SDL2d.dll
                ${SDL2TTF_BINARY_DIR}/SDL2_ttf.dll
                ${SDL2TTF_BINARY_DIR}/SDL2_ttfd.dll
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
else()
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${SDL2_BINARY_DIR}/SDL2.dll
                ${SDL2TTF_BINARY_DIR}/SDL2_ttf.dll
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()

# Debug include directories (for validation)
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()