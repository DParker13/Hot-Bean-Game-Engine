add_library(game STATIC
    example_game.cpp
    example_game.hpp
)

target_link_libraries(game PUBLIC
    scenes
)