add_library(systems STATIC
    ${CMAKE_CURRENT_LIST_DIR}/physics_system.cpp
    ${CMAKE_CURRENT_LIST_DIR}/physics_system.hpp
    ${CMAKE_CURRENT_LIST_DIR}/render_system.cpp
    ${CMAKE_CURRENT_LIST_DIR}/render_system.hpp
    ${CMAKE_CURRENT_LIST_DIR}/input_system.cpp
    ${CMAKE_CURRENT_LIST_DIR}/input_system.hpp
    ${CMAKE_CURRENT_LIST_DIR}/player_controller_system.cpp
    ${CMAKE_CURRENT_LIST_DIR}/player_controller_system.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ui_system.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ui_system.hpp
)

# Specify include directories for the systems library
target_include_directories(systems PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link dependencies for the systems library
target_link_libraries(systems PRIVATE
    core
)