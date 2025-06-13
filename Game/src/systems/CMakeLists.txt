add_library(systems STATIC
    #tilemap_system.cpp
    #tilemap_system.hpp
    audio_system.cpp
    audio_system.hpp
)

target_link_libraries(systems PUBLIC
    HotBeanEngine
)