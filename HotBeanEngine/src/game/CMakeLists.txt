add_library(base_game STATIC
    base_scene.cpp
    base_scene.hpp
)

target_link_libraries(base_game PUBLIC
    core
)