add_library(test_systems STATIC
    tilemap_system.cpp
    tilemap_system.hpp
    audio_system.cpp
    audio_system.hpp
)

target_link_libraries(test_systems PUBLIC
    HotBeanEngine
)

include_directories(${HotBeanEngine_SOURCE_DIR}/include)