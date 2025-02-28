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
)

# Specify include directories for the systems library
target_include_directories(systems PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link dependencies for the systems library
target_link_libraries(systems PRIVATE
    SDL2
    SDL2_mixer
    core
)