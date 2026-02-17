/**
 * @file layer_window.cpp
 * @author Daniel Parker (DParker13)
 * @brief Implementation of the layer window for managing render layers.
 * Displays available layers and properties of selected layers.
 * @version 0.1
 * @date 2025-12-24
 *
 * @copyright Copyright (c) 2025
 */

#include "layer_window.hpp"
#include <HotBeanEngine/application/managers/render_manager.hpp>

namespace HBE::Application::GUI {
    LayerWindow::~LayerWindow() {
        if (m_selected_layer) {
            delete m_selected_layer;
            m_selected_layer = nullptr;
        }
    }

    void LayerWindow::RenderWindow() {
        ImGui::Begin(m_name.c_str(), &m_open);

        int id = 0;
        for (auto &layer : g_app.GetRenderManager().GetAllLayers()) {
            glm::vec2 layer_size;
            SDL_GetTextureSize(layer.second, &layer_size.x, &layer_size.y);
            ImGui::BeginGroup();
            if (ImGui::MenuItem(std::to_string(layer.first).data())) {
                LayerSelected(layer);
            }
            ImGui::EndGroup();
        }

        ImGui::End();
    }

    void LayerWindow::LayerSelected(std::pair<const int, SDL_Texture *> layer) {
        if (m_property_window) {
            std::vector<std::pair<std::string, IPropertyRenderable *>> property_nodes;
            if (m_selected_layer) {
                delete m_selected_layer;
                m_selected_layer = nullptr;
            }
            m_selected_layer = new LayerProperty(layer.second);
            std::string layer_name = "Layer " + std::to_string(layer.first);
            property_nodes.push_back({layer_name, m_selected_layer});
            m_property_window->SetProperties(property_nodes);
        }
        else {
            LOG(LoggingType::ERROR, "Property window was never setup.");
        }
    }
} // namespace HBE::Application::GUI