# Define a static library for the core implementation
add_library(managers STATIC
    core_manager.cpp
    core_manager.hpp
    entity_manager.cpp
    entity_manager.hpp
    component_manager.cpp
    component_manager.hpp
    system_manager.cpp
    system_manager.hpp
)

target_include_directories(managers PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

# Link other dependencies if needed (e.g., core library, SDL2, etc.)
# If managers depend on core, link it here.
target_link_libraries(managers PRIVATE
    core
)