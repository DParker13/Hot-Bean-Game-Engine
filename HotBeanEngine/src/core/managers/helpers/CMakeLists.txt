add_library(managers_helpers INTERFACE
    component_register.hpp
    serialization_helper.hpp
)

target_link_libraries(managers_helpers INTERFACE
    core
    yaml-cpp
    glm
)