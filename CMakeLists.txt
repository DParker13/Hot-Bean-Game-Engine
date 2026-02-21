cmake_minimum_required(VERSION 3.11) # FetchContent is new in version 3.11.

project(FullHotBeanEngine LANGUAGES CXX)

set(CMAKE_BUILD_PARALLEL_LEVEL 4)

# Enable testing for CTest
enable_testing()

add_subdirectory(HotBeanEngine)
add_subdirectory(Game)