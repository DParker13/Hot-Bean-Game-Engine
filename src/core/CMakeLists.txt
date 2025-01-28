# Define an INTERFACE library for the public headers that other modules will use
add_library(core INTERFACE
    ecs.hpp
    sparse_set.hpp
)

target_include_directories(core INTERFACE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(core INTERFACE
    SDL2
)

add_subdirectory(managers)