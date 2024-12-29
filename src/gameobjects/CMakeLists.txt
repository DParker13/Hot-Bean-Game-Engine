add_library(gameobjects STATIC
    gameobject.hpp
    gameobject.cpp
    text.hpp
    text.cpp
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
)