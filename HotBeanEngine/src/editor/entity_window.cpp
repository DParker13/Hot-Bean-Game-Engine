/**
 * @file entity_window.cpp
 * @author Daniel Parker (DParker13)
 * @brief Implementation of the entity window for browsing and selecting entities.
 * Displays entities organized by their systems and allows component property editing.
 * @version 0.1
 * @date 2025-10-30
 *
 * @copyright Copyright (c) 2025
 */

#include "entity_window.hpp"

namespace HBE::Application::GUI {
    void EntityWindow::RenderWindow() {
        ImGui::Begin(m_name.c_str(), &m_open);

        for (auto &system : g_ecs.GetAllSystems()) {
            ImGui::BeginGroup();
            if (ImGui::CollapsingHeader(system->GetName().data(), ImGuiTreeNodeFlags_Framed)) {
                for (auto &entity : system->m_entities) {
                    std::string entity_label = "Entity " + std::to_string(entity);

                    if (ImGui::MenuItem(entity_label.c_str())) {
                        EntitySelected(entity);
                    }
                }
            }
            ImGui::EndGroup();
        }

        ImGui::End();
    }

    void EntityWindow::EntitySelected(EntityID entity) {
        if (m_property_window) {
            std::vector<std::pair<std::string, IPropertyRenderable *>> property_nodes;
            for (IComponent *component : g_ecs.GetAllComponents(entity)) {
                IPropertyRenderable *renderable = dynamic_cast<IPropertyRenderable *>(component);
                IName *nameable = dynamic_cast<IName *>(component);

                if (renderable && nameable) {
                    property_nodes.push_back({std::string(nameable->GetName()), renderable});
                }
            }
            m_property_window->SetProperties(property_nodes);
        } else {
            LOG(LoggingType::ERROR, "Property window was never setup.");
        }
    }
} // namespace HBE::Application::GUI