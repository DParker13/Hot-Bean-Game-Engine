add_library(core INTERFACE
    core.hpp
)

target_link_libraries(core INTERFACE
    core_components
    core_systems
    core_archetypes
)

add_subdirectory(ecs)
add_subdirectory(components)
add_subdirectory(managers)
add_subdirectory(application)
add_subdirectory(archetypes)
add_subdirectory(systems)