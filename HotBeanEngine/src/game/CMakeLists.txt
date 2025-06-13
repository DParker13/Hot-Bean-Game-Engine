add_library(base_game STATIC
    base_scene.hpp
    base_game.cpp
    base_game.hpp
)

target_link_libraries(base_game PUBLIC
    core
    archetypes
)