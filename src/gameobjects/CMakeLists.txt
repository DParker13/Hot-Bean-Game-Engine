add_library(gameobjects INTERFACE
    player.hpp
    tile.hpp
)

target_link_libraries(gameobjects INTERFACE
    gameobjects-ui
)

add_subdirectory(ui)