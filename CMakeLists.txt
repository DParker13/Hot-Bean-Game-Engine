cmake_minimum_required(VERSION 3.11) # FetchContent is new in version 3.11.
project("HotBeanEngine")

# SDL2_ttf 2.22.0
# include header file copied to SDL2 include directory
set(SDL_TTF_DIR C:/SDL/SDL2_ttf)
set(SDL_TTF_LIBRARY_DIR ${SDL_TTF_DIR}/lib/x64)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the number of threads for parallel building
set(CMAKE_BUILD_PARALLEL_LEVEL 4)

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
# FetchContent_Declare(
#     SDL_ttf
#     GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
#     GIT_TAG release-2.22.0
# )

# Set up SDL_ttf deps
#set(SDL_ttf_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin/_deps/sdl_ttf-src)
#add_subdirectory(${SDL_ttf_SOURCE_DIR}/external/freetype)
#set(FREETYPE_LIBRARY ${SDL_ttf_SOURCE_DIR}/external/freetype/libfreetype.a)
#set(FREETYPE_INCLUDE_DIRS ${SDL_ttf_SOURCE_DIR}/external/freetype/include)

FetchContent_MakeAvailable(glm SDL2)

add_executable(HotBeanEngine src/main.cpp src/Application.cpp)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_custom_command(
        TARGET HotBeanEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${SDL2_BINARY_DIR}/SDL2.dll
                ${SDL2_BINARY_DIR}/SDL2d.dll
                ${SDL_TTF_LIBRARY_DIR}/SDL2_ttf.dll
                $<TARGET_FILE_DIR:HotBeanEngine>
    )
else()
    add_custom_command(
        TARGET HotBeanEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${SDL2_BINARY_DIR}/SDL2.dll
                ${SDL_TTF_LIBRARY_DIR}/SDL2_ttf.dll
                $<TARGET_FILE_DIR:HotBeanEngine>
    )
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SDL2_SOURCE_DIR}/include
    # ${SDL_ttf_SOURCE_DIR}
    ${SDL_TTF_DIR}/include
    ${glm_SOURCE_DIR}/glm
)

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()

add_subdirectory(src/core)
add_subdirectory(src/components)
add_subdirectory(src/systems)

target_link_libraries(HotBeanEngine
  SDL2main
  SDL2
  # SDL_ttf
  ${SDL_TTF_LIBRARY_DIR}/SDL2_ttf.lib
  glm
  core
  components
  systems
)