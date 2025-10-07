add_library(core INTERFACE
    all_core.hpp
    archetype.hpp
    component.hpp
    entity.hpp
    exceptions.hpp
    game_loop.hpp
    logging_type.hpp
    signature.hpp
    sparse_set.hpp
    system.hpp
    scene.hpp
    yaml_extensions.hpp
)

target_include_directories(core INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(core INTERFACE
    SDL3::SDL3
    glm
    yaml-cpp
)

set_target_properties(core PROPERTIES LINKER_LANGUAGE CXX)