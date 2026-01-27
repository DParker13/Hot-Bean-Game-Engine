#pragma once

#include <imgui.h>
#include <HotBeanEngine/application/application.hpp>

#include "property_window.hpp"

namespace HBE::Application::GUI {
    class EntityWindow : public IWindow {
        private:
            std::shared_ptr<PropertyWindow> m_property_window = nullptr;

        public:
            EntityWindow(std::shared_ptr<PropertyWindow> property_window) : IWindow("Entities"), m_property_window(property_window) {}
            ~EntityWindow() = default;

            virtual void RenderWindow() override;
            void EntitySelected(EntityID entity);
    };
}