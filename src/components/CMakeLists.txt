add_library(components INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/transform.hpp
    ${CMAKE_CURRENT_LIST_DIR}/rigidbody.hpp
    ${CMAKE_CURRENT_LIST_DIR}/gravity.hpp
)

target_link_libraries(components INTERFACE HotBeanEngine)