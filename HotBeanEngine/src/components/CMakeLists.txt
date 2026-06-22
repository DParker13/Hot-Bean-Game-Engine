add_library(HotBeanEngine_Components STATIC
    audio/audio_source.cpp
    input/controller.cpp
    miscellaneous/camera.cpp
    miscellaneous/name.cpp
    miscellaneous/transform_2d.cpp
    physics/collider_2d.cpp
    physics/rigidbody.cpp
    rendering/shape.cpp
    rendering/texture.cpp
    ui/checkbox.cpp
    ui/interactive.cpp
    ui/slider.cpp
    ui/text.cpp
    ui/ui_rect.cpp
)

target_include_directories(HotBeanEngine_Components PUBLIC
    ${box2d_SOURCE_DIR}/include
)

target_link_libraries(HotBeanEngine_Components PUBLIC
    HotBeanEngine_Application
    box2d::box2d
)