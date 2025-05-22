add_library(test_game STATIC
    test_game.cpp
    test_game.hpp
)

target_link_libraries(test_game PUBLIC
    HotBeanEngine
    test_systems
)