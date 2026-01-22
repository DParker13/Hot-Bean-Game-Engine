add_library(HotBeanEngine_Defaults STATIC
    default_component_factory.cpp
    default_scene_serializer.cpp
    default_scene.cpp
    utilities/scene_graph.cpp
)

add_subdirectory(systems)

target_link_libraries(HotBeanEngine_Defaults PUBLIC
    HotBeanEngine_Systems
)