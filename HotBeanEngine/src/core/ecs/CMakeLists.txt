add_library(ecs INTERFACE
    all_ecs.hpp
    app.hpp
    component.hpp
    entity.hpp
    game_loop.hpp
    logging_type.hpp
    object.hpp
    signature.hpp
    sparse_set.hpp
    system.hpp
    scene.hpp
)

target_link_libraries(ecs INTERFACE
    SDL2
)

set_target_properties(ecs PROPERTIES LINKER_LANGUAGE CXX)