add_library(systems STATIC
    audio_system.hpp
    audio_system.cpp
    camera_system.cpp
    camera_system.hpp
    collision_system.cpp
    collision_system.hpp
    default_systems.hpp
    physics_system.cpp
    physics_system.hpp
    input_system.cpp
    input_system.hpp
    player_controller_system.cpp
    player_controller_system.hpp
    render_system.cpp
    render_system.hpp
    ui_system.cpp
    ui_system.hpp
    transform_system.cpp
    transform_system.hpp
)

# Link dependencies for the systems library
target_link_libraries(systems PUBLIC
    glm
    core
)