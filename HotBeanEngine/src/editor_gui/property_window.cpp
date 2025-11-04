#include "property_window.hpp"

namespace HBE::Application::GUI {
    void PropertyWindow::RenderWindow() {
        ImGui::Begin(m_name.c_str());

        if (m_selected_entity != -1) {
            int id = 0;
            EntityID entity = static_cast<EntityID>(m_selected_entity);
            for(IComponent* property_renderer : g_ecs.GetAllComponents(entity)) {
                IPropertyRenderable* renderable = dynamic_cast<IPropertyRenderable*>(property_renderer);
                IName* name = dynamic_cast<IName*>(property_renderer);

                if (renderable && name) {
                    if (ImGui::CollapsingHeader((std::string(name->GetName()) + " Component").c_str())) {
                        renderable->RenderProperties(id, entity);
                    }
                }
            }
        }

        ImGui::End();
    }

    void PropertyWindow::EntitySelected(EntityID entity) {
        m_selected_entity = static_cast<Sint64>(entity);
    }
}