add_library(core_archetypes INTERFACE
    default_archetypes.hpp
)

target_link_libraries(core_archetypes INTERFACE
    core_components
)