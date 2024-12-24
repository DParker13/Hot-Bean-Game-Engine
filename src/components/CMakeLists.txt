add_library(components INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/transform.hpp
    ${CMAKE_CURRENT_LIST_DIR}/rigidbody.hpp
    ${CMAKE_CURRENT_LIST_DIR}/text.hpp
    ${CMAKE_CURRENT_LIST_DIR}/player.hpp
    ${CMAKE_CURRENT_LIST_DIR}/texture.hpp
)

target_include_directories(components INTERFACE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(components INTERFACE
    SDL2
)