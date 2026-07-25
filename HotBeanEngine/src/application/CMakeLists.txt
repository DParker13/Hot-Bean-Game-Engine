add_library(HotBeanEngine_Application STATIC
    application.cpp
    scene.cpp
    listeners/input_event_listener.cpp
)

target_compile_definitions(HotBeanEngine_Application PRIVATE
    HBE_ENABLE_EDITOR_GUI=$<BOOL:${HBE_ENABLE_EDITOR_GUI}>
)

add_subdirectory(managers)

target_link_libraries(HotBeanEngine_Application PUBLIC
    HotBeanEngine_Managers
    HotBeanEngine_Components
    HotBeanEngine_Editor
)

# TODO: Separate imgui from components to get this working
# if(HBE_ENABLE_EDITOR_GUI)
#     target_link_libraries(HotBeanEngine_Application PUBLIC
#         HotBeanEngine_Editor
#     )
# endif()