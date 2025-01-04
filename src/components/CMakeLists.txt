add_library(components INTERFACE
    transform.hpp
    rigidbody.hpp
    text.hpp
    player.hpp
    texture.hpp
    tile.hpp
    audio_source.hpp
)

target_include_directories(components INTERFACE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(components INTERFACE
    SDL2
)