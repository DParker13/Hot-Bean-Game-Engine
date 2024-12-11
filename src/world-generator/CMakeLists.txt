include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(world-generator STATIC)

target_sources(world-generator PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Cell.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Grid.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Cell.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Grid.h
)