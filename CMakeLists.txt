cmake_minimum_required(VERSION 3.10)
project("OceanSim")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(C:/SDL/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set build type to Debug by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

message(STATUS "Setting build type to '${CMAKE_BUILD_TYPE}'")

add_subdirectory(src)