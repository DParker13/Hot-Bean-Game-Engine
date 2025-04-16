add_library(core INTERFACE
    core.hpp
)

target_link_libraries(core INTERFACE
    application
)

add_subdirectory(ecs)
add_subdirectory(managers)
add_subdirectory(application)