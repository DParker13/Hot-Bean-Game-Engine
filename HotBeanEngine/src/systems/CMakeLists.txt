add_library(default_systems STATIC
    all_systems.hpp
    audio/audio_system.hpp
    audio/audio_system.cpp
    input/input_system.cpp
    input/input_system.hpp
    input/player_controller_system.cpp
    input/player_controller_system.hpp
    #physics/collision_system.cpp
    #physics/collision_system.hpp
    physics/physics_system.cpp
    physics/physics_system.hpp
    rendering/camera_system.cpp
    rendering/camera_system.hpp
    rendering/render_system.cpp
    rendering/render_system.hpp
    rendering/shape_system.cpp
    rendering/shape_system.hpp
    rendering/transform_system.cpp
    rendering/transform_system.hpp
    ui/ui_system.cpp
    ui/ui_system.hpp
)

# Link dependencies for the systems library
target_link_libraries(default_systems PUBLIC
    application
)