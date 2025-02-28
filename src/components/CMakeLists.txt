add_library(components INTERFACE
    transform-2d.hpp
    rigidbody.hpp
    text.hpp
    controller.hpp
    texture.hpp
    tile.hpp
    audio_source.hpp
    ui-element.hpp
)

target_include_directories(components INTERFACE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(components INTERFACE
    SDL2
)