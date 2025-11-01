#pragma once

#include <imgui.h>
#include <functional>

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/editor_gui/iwindow.hpp>
#include <HotBeanEngine/editor_gui/iproperty_renderable.hpp>

namespace HBE::Application::GUI {
    using namespace HBE::Core;
    
    class PropertyWindow : public IWindow {
        public:
            PropertyWindow() : IWindow("Properties") {}
            ~PropertyWindow() = default;

            // Callback function
            Sint64 m_selected_entity = -1;

            void RenderWindow() override;

            // Call this when an entity is selected
            void EntitySelected(EntityID entity);
    };
}