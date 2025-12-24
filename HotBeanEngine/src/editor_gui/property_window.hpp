#pragma once

#include <imgui.h>
#include <functional>

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/editor_gui/iwindow.hpp>
#include <HotBeanEngine/editor_gui/iproperty_renderable.hpp>

namespace HBE::Application::GUI {
    using namespace HBE::Core;
    
    class PropertyWindow : public IWindow {
        private:
            std::vector<std::pair<std::string, IPropertyRenderable*>> m_properties;

        public:
            PropertyWindow() : IWindow("Properties") {}
            ~PropertyWindow() = default;

            void RenderWindow() override;
            void SetProperties(std::vector<std::pair<std::string, IPropertyRenderable*>> properties);
    };
}