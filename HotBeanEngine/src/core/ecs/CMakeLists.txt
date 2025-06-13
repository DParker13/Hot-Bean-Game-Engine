add_library(ecs INTERFACE
    all_ecs.hpp
    app.hpp
    component.hpp
    entity.hpp
    game_loop.hpp
    logging_type.hpp
    signature.hpp
    sparse_set.hpp
    system.hpp
    scene.hpp
    yaml_extensions.hpp
)

target_link_libraries(ecs INTERFACE
    SDL2::SDL2
    yaml-cpp
)

include_directories(${SDL2_INCLUDE_DIRS})

set_target_properties(ecs PROPERTIES LINKER_LANGUAGE CXX)