add_library(components STATIC
    component_register.cpp
    component_register.hpp
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
    glm
)

add_subdirectory(enums)