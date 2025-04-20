add_library(src INTERFACE
    game
)

target_link_libraries(src INTERFACE
    game
)

# Add subdirectories for project modules
add_subdirectory(core)
add_subdirectory(components)
add_subdirectory(gameobjects)
add_subdirectory(systems)
add_subdirectory(scenes)
add_subdirectory(game)