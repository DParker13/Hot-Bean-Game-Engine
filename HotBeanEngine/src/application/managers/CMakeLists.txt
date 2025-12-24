add_library(HotBeanEngine_Managers STATIC
    component_manager.cpp
    ecs_manager.cpp
    entity_manager.cpp
    game_loop_manager.cpp
    system_manager.cpp
    logging_manager.cpp
    scene_manager.cpp
)

target_include_directories(HotBeanEngine_Managers PUBLIC
    ${CMAKE_SOURCE_DIR}/HotBeanEngine/include
    ${sdl3_SOURCE_DIR}/include
    ${sdl3_mixer_SOURCE_DIR}/include
    ${sdl3_image_SOURCE_DIR}/include
    ${sdl3_ttf_SOURCE_DIR}/include
    ${glm_SOURCE_DIR}
    ${yaml_cpp_SOURCE_DIR}/include
)

target_link_libraries(HotBeanEngine_Managers PUBLIC
    SDL3::SDL3
    SDL3_mixer::SDL3_mixer
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
    yaml-cpp::yaml-cpp
    glm::glm
)