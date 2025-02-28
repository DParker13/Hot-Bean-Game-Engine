add_library(gameobjects STATIC
    gameobject.hpp
    gameobject.cpp
    player.hpp
    player.cpp
    tile.hpp
    tile.cpp
)

target_include_directories(gameobjects PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(gameobjects PRIVATE
    core
    gameobjects-ui
)

add_subdirectory(ui)