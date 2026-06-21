# Setup ImGUI
add_library(imgui STATIC
	${imgui_SOURCE_DIR}/imconfig.h
	${imgui_SOURCE_DIR}/imgui.h

	${imgui_SOURCE_DIR}/imgui.cpp
	${imgui_SOURCE_DIR}/imgui_draw.cpp
	${imgui_SOURCE_DIR}/imgui_demo.cpp
	${imgui_SOURCE_DIR}/imgui_tables.cpp
	${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp

	${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)

target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
)

target_link_libraries(imgui PUBLIC
    SDL3::SDL3
)

add_library(HotBeanEngine_Editor STATIC
    control_bar.cpp
    control_bar.hpp
    editor_gui.cpp
    editor_utils.hpp
    menu.cpp
    menu.hpp
    project_manager.cpp
    project_manager.hpp
    windows/config_window.cpp
    windows/config_window.hpp
    windows/console_window.cpp
    windows/console_window.hpp
    windows/entity_window.cpp
    windows/entity_window.hpp
    windows/layer_window.cpp
    windows/layer_window.hpp
    windows/new_project_window.cpp
    windows/new_project_window.hpp
    windows/project_window.cpp
    windows/project_window.hpp
    windows/property_window.cpp
    windows/property_window.hpp
    windows/scene_window.cpp
    windows/scene_window.hpp
)

target_link_libraries(HotBeanEngine_Editor PUBLIC
    imgui
    HotBeanEngine_Systems
    HotBeanEngine_Components
    HotBeanEngine_Serializers
)