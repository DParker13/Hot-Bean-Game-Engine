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

target_link_libraries(core INTERFACE
    SDL2::SDL2
    yaml-cpp
)

set_target_properties(core PROPERTIES LINKER_LANGUAGE CXX)