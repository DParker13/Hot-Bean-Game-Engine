add_library(gameobjects-ui INTERFACE
    text.hpp
    textbox.hpp
    fps-counter.hpp
)

target_link_libraries(gameobjects-ui INTERFACE
    core
)