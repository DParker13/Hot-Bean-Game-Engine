add_library(core_components STATIC
    component_factory.cpp
    component_factory.hpp
    audio/audio_source.hpp
    input/controller.hpp
    miscellaneous/camera.hpp
    miscellaneous/transform_2d.hpp
    physics/collider_2d.hpp
    physics/rigidbody.hpp
    rendering/shape.hpp
    rendering/texture.hpp
    ui/text.hpp
    ui/ui_element.hpp
)

target_link_libraries(core_components PUBLIC
    glm
    yaml-cpp
)