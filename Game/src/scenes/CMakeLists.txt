add_library(scenes STATIC
    example_scene.cpp
    example_scene.hpp
)

# Link dependencies for the scenes library
target_link_libraries(scenes PUBLIC
    systems
)