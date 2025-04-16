add_library(scenes STATIC
    test_scene.hpp
)

# Link dependencies for the scenes library
target_link_libraries(scenes PUBLIC
    core
)