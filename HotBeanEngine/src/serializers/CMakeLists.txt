add_library(HotBeanEngine_Serializers STATIC
    yaml/yaml_scene_serializer.cpp
    yaml/yaml_serialization_reader.cpp
    yaml/yaml_serialization_writer.cpp
)

target_link_libraries(HotBeanEngine_Serializers PUBLIC
    HotBeanEngine_Application
)