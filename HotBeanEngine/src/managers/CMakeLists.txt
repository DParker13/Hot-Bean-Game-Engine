# Define a static library for the core implementation
add_library(managers STATIC
    all_managers.hpp
    component_manager.cpp
    component_manager.hpp
    ecs_manager.cpp
    ecs_manager.hpp
    entity_manager.cpp
    entity_manager.hpp
    system_manager.cpp
    system_manager.hpp
    logging_manager.cpp
    logging_manager.hpp
    serialization_manager.cpp
    serialization_manager.hpp
)

# Link other dependencies if needed (e.g., core library, SDL2, etc.)
# If managers depend on core, link it here.
target_link_libraries(managers PUBLIC
    core
    glm
)