#include "property_window.hpp"

namespace HBE::Application::GUI {
    void PropertyWindow::RenderWindow() {
        ImGui::Begin(m_name.c_str());

        int id = 0;
        for(auto& property : m_properties) {
            if (ImGui::CollapsingHeader(property.first.data())) {
                property.second->RenderProperties(id);
            }
        }

        ImGui::End();
    }

    void PropertyWindow::SetProperties(std::vector<std::pair<std::string, IPropertyRenderable*>> properties) {
        m_properties = properties;
    }
}