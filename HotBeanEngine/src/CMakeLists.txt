add_library(src INTERFACE
    components
    core
    gameobjects
    systems
    scenes
)

target_link_libraries(src INTERFACE
    components
    core
    gameobjects
    systems
    scenes
)

# Add subdirectories for project modules
add_subdirectory(core)
add_subdirectory(components)
add_subdirectory(gameobjects)
add_subdirectory(systems)
add_subdirectory(scenes)