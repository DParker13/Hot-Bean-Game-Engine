add_library(systems STATIC
    physics_system.cpp
    physics_system.hpp
    render_system.cpp
    render_system.hpp
    input_system.cpp
    input_system.hpp
    player_controller_system.cpp
    player_controller_system.hpp
    ui_system.cpp
    ui_system.hpp
    tilemap_system.hpp
    tilemap_system.cpp
    audio_system.hpp
    audio_system.cpp
    collision_system.cpp
    collision_system.hpp
)

# Link dependencies for the systems library
target_link_libraries(systems PUBLIC
    glm
    core
)