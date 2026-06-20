add_library(HotBeanEngine_Serializers STATIC
    yaml/yaml_scene_serializer.cpp
)

target_link_libraries(HotBeanEngine_Serializers PUBLIC
    HotBeanEngine_Application
)