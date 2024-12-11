add_library(systems OBJECT
    ${CMAKE_CURRENT_LIST_DIR}/physics_system.cpp
    ${CMAKE_CURRENT_LIST_DIR}/render_system.cpp
    ${CMAKE_CURRENT_LIST_DIR}/input_system.cpp
)

add_library(systems-interface INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/physics_system.hpp
    ${CMAKE_CURRENT_LIST_DIR}/render_system.hpp
    ${CMAKE_CURRENT_LIST_DIR}/input_system.hpp
)

target_include_directories(HotBeanEngine PUBLIC ${CMAKE_CURRENT_LIST_DIR})