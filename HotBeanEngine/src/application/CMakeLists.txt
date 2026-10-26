add_library(HotBeanEngine_Application STATIC
    application.cpp
    scene.cpp
    listeners/input_event_listener.cpp
)

target_compile_definitions(HotBeanEngine_Application PRIVATE
    GAME_RELEASE_BUILD=$<BOOL:${GAME_RELEASE_BUILD}>
)

add_subdirectory(managers)

target_link_libraries(HotBeanEngine_Application PUBLIC
    HotBeanEngine_Managers
    HotBeanEngine_Components
    HotBeanEngine_Editor
)

# TODO: Separate imgui from components to get this working
# if(GAME_RELEASE_BUILD)
#     target_link_libraries(HotBeanEngine_Application PUBLIC
#         HotBeanEngine_Editor
#     )
# endif()