add_library(scenes STATIC
    test_scene.cpp
    test_scene.hpp
)

# Link dependencies for the scenes library
target_link_libraries(scenes PUBLIC
    HotBeanEngine
)