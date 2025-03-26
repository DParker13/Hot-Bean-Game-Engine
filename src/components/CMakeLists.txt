add_library(components INTERFACE
    transform_2d.hpp
    rigidbody.hpp
    text.hpp
    controller.hpp
    texture.hpp
    tile.hpp
    audio_source.hpp
    ui_element.hpp
    collider_2d.hpp
)

target_link_libraries(components INTERFACE
    core
)