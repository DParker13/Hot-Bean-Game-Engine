add_library(components INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/transform.hpp
    ${CMAKE_CURRENT_LIST_DIR}/rigidbody.hpp
    ${CMAKE_CURRENT_LIST_DIR}/text.hpp
    ${CMAKE_CURRENT_LIST_DIR}/player.hpp
)

target_include_directories(components INTERFACE ${CMAKE_CURRENT_LIST_DIR})