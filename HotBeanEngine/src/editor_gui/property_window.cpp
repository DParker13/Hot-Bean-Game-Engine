#include "property_window.hpp"

namespace HBE::Application::GUI {
    void PropertyWindow::RenderWindow() {
        ImGui::Begin(m_name.c_str());

        if (m_selected_entity != -1) {
            for(const auto& property_renderer : g_ecs.GetAllComponents(static_cast<Entity>(m_selected_entity))) {
                auto* renderable = dynamic_cast<IPropertyRenderable*>(property_renderer);

                if (renderable) {
                    renderable->RenderProperties(m_selected_entity, property_renderer);
                }
            }
        }

        ImGui::End();
    }

    void PropertyWindow::EntitySelected(Entity entity) {
        m_selected_entity = static_cast<Sint64>(entity);
    }
}