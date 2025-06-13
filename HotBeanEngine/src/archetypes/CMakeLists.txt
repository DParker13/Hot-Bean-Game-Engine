add_library(archetypes INTERFACE
    default_archetypes.hpp
)

target_link_libraries(archetypes INTERFACE
    core
)