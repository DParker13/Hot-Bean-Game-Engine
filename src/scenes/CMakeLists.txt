add_library(scenes STATIC
    test.hpp
)

# Link dependencies for the scenes library
target_link_libraries(scenes STATIC
    core
)