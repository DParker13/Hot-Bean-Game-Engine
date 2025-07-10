add_library(core INTERFACE
    core.hpp
)

target_link_libraries(core INTERFACE
    core_components
    core_systems
)

add_subdirectory(ecs)
add_subdirectory(components)
add_subdirectory(managers)
add_subdirectory(application)
add_subdirectory(systems)
add_subdirectory(scenes)