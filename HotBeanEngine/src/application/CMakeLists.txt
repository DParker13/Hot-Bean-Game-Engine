add_library(HotBeanEngine_Application STATIC
    application.cpp
    editor_gui.cpp
    editor_gui/components_window.cpp
    editor_gui/components_window.hpp
    editor_gui/components.cpp
    editor_gui/components.hpp
    editor_gui/console_window.cpp
    editor_gui/console_window.hpp
    editor_gui/menu.cpp
    editor_gui/menu.hpp
    editor_gui/systems.cpp
    editor_gui/systems.hpp
    editor_gui/viewport_window.cpp
    editor_gui/viewport_window.hpp
)

add_subdirectory(managers)

target_link_libraries(HotBeanEngine_Application PUBLIC
    imgui
    HotBeanEngine_Managers
)