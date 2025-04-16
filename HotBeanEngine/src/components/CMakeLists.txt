add_library(components STATIC
    default_components.hpp
    audio_source.hpp
    collider_2d.hpp
    controller.hpp
    rigidbody.hpp
    text.hpp
    texture.hpp
    tile.hpp
    transform_2d.hpp
    ui_element.hpp
)

target_link_libraries(components PUBLIC
    core
    enums
)

add_subdirectory(enums)