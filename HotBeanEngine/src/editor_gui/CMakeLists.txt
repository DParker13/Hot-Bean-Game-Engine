# Setup ImGUI
add_library(imgui STATIC
	${imgui_SOURCE_DIR}/imconfig.h
	${imgui_SOURCE_DIR}/imgui.h

	${imgui_SOURCE_DIR}/imgui.cpp
	${imgui_SOURCE_DIR}/imgui_draw.cpp
	${imgui_SOURCE_DIR}/imgui_demo.cpp
	${imgui_SOURCE_DIR}/imgui_tables.cpp
	${imgui_SOURCE_DIR}/imgui_widgets.cpp

	${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)

target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
)

target_link_libraries(imgui PUBLIC
    HotBeanEngine_Defaults
)

add_library(HotBeanEngine_EditorGui STATIC
    console_window.cpp
    console_window.hpp
    control_bar.cpp
    control_bar.hpp
    editor_camera.cpp
    editor_gui.cpp
    entity_window.cpp
    entity_window.hpp
    layer_window.cpp
    layer_window.hpp
    menu.cpp
    menu.hpp
    property_window.cpp
    property_window.hpp
    viewport_window.cpp
    viewport_window.hpp
)

target_link_libraries(HotBeanEngine_EditorGui PUBLIC
    imgui
)