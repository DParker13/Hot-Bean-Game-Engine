cmake_minimum_required(VERSION 3.11) # FetchContent is new in version 3.11.

project(FullHotBeanEngine LANGUAGES CXX)

set(CMAKE_BUILD_PARALLEL_LEVEL 4)

option(HBE_WARNINGS_AS_ERRORS "Treat compiler warnings as errors for project targets" ON)

# Enable testing for CTest
enable_testing()

add_subdirectory(HotBeanEngine)
add_subdirectory(Game)