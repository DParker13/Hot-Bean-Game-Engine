add_library(gameobjects-interface INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/gameobject.hpp
)

add_library(gameobjects STATIC
    ${CMAKE_CURRENT_LIST_DIR}/text.hpp
    ${CMAKE_CURRENT_LIST_DIR}/text.cpp
    ${CMAKE_CURRENT_LIST_DIR}/player.hpp
    ${CMAKE_CURRENT_LIST_DIR}/player.cpp
)

target_include_directories(gameobjects-interface INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Specify include directories for the systems library
target_include_directories(gameobjects PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(gameobjects PRIVATE
    core
)