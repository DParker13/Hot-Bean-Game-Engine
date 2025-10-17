#include "components_window.hpp"

namespace HBE::Application::GUI {
    ComponentsWindow::ComponentsWindow() : IWindow("Components") {}

    void ComponentsWindow::Render() {
        ImGui::Begin(m_name.c_str(), &m_open);

        size_t index = 0;
        for (auto& system : g_ecs.GetAllSystems()) {
            std::string system_id = "System " + std::to_string(index++);
            if (ImGui::BeginListBox(system_id.c_str())) {
                for (auto& entity : system->m_entities) {
                    std::string entity_label = "Entity " + std::to_string(entity);
                    ImGui::MenuItem(entity_label.c_str());
                }

                ImGui::EndListBox();
            }
        }

        ImGui::End();
    }
}