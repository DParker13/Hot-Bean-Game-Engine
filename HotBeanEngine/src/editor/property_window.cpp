/**
 * @file property_window.cpp
 * @author Daniel Parker (DParker13)
 * @brief Implementation of the property window for editing entity properties.
 * Displays and manages component properties with collapsible sections.
 * @version 0.1
 * @date 2025-10-30
 *
 * @copyright Copyright (c) 2025
 */

#include "property_window.hpp"

namespace HBE::Application::GUI {
    void PropertyWindow::RenderWindow() {
        ImGui::Begin(m_name.c_str());

        int id = 0;
        for (auto &property : m_properties) {
            if (ImGui::CollapsingHeader(property.first.data())) {
                property.second->RenderProperties(id);
            }
        }

        ImGui::End();
    }

    void PropertyWindow::SetProperties(std::vector<std::pair<std::string, IPropertyRenderable *>> properties) {
        m_properties = properties;
    }
} // namespace HBE::Application::GUI