add_library(HotBeanEngine_Utilities STATIC
    scene_graph.cpp
)

target_link_libraries(HotBeanEngine_Utilities PUBLIC
    HotBeanEngine_Application
)