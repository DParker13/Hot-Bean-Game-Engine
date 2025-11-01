add_library(systems STATIC
    audio_system.cpp
    audio_system.hpp
)

target_include_directories(systems PUBLIC
    ${HotBeanEngine_SOURCE_DIR}/include
)

target_link_libraries(systems PUBLIC
    HotBeanEngine_Application
    HotBeanEngine_Defaults
)