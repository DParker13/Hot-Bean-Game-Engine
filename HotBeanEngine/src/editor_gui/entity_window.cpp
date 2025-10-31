#include "entity_window.hpp"

namespace HBE::Application::GUI {
    void EntityWindow::RenderWindow() {
        ImGui::Begin(m_name.c_str(), &m_open);

        for (auto& system : g_ecs.GetAllSystems()) {
            ImGui::BeginGroup();
            if (ImGui::CollapsingHeader(system->GetName().data(), ImGuiTreeNodeFlags_Framed)) {
                for (auto& entity : system->m_entities) {
                    std::string entity_label = "Entity " + std::to_string(entity);

                    if (ImGui::MenuItem(entity_label.c_str())) {
                        if (m_property_window) {
                            m_property_window->EntitySelected(entity);
                        }
                        else {
                            LOG(LoggingType::ERROR, "Property window was never setup.");
                        }
                    }
                }
            }
            ImGui::EndGroup();
        }

        ImGui::End();
    }
}