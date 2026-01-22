add_library(HotBeanEngine_Systems STATIC
    audio/audio_system.cpp
    input/player_controller_system.cpp
    physics/collision_system.cpp
    physics/physics_system.cpp
    rendering/camera_system.cpp
    rendering/render_system.cpp
    rendering/shape_system.cpp
    rendering/transform_system.cpp
    ui/ui_system.cpp
)

target_include_directories(HotBeanEngine_Systems PUBLIC
    ${box2d_SOURCE_DIR}/include
)

target_link_libraries(HotBeanEngine_Systems PUBLIC
    HotBeanEngine_Application
    box2d::box2d
)