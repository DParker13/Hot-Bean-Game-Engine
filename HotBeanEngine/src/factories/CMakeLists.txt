add_library(HotBeanEngine_Factories STATIC
    component_factory.cpp
    scene_factory.cpp
    system_factory.cpp
)

target_link_libraries(HotBeanEngine_Factories PUBLIC
    HotBeanEngine_Application
    HotBeanEngine_Components
    HotBeanEngine_Systems
)