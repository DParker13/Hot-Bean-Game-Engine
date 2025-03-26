# Define a static library for the core implementation
add_library(managers STATIC
    all_managers.hpp
    core_manager.cpp
    core_manager.hpp
    entity_manager.cpp
    entity_manager.hpp
    component_manager.cpp
    component_manager.hpp
    system_manager.cpp
    system_manager.hpp
    scene_manager.cpp
    scene_manager.hpp
)

# Link other dependencies if needed (e.g., core library, SDL2, etc.)
# If managers depend on core, link it here.
target_link_libraries(managers PUBLIC
    ecs
)