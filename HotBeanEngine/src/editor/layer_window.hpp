/**
 * @file layer_window.hpp
 * @author Daniel Parker (DParker13)
 * @brief Window for managing and displaying render layers.
 * @version 0.1
 * @date 2025-12-24
 *
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/defaults/systems/rendering/render_system.hpp>
#include <HotBeanEngine/editor/property_nodes/texture_preview.hpp>
#include <imgui.h>

#include "property_window.hpp"

namespace HBE::Application::GUI {
    /**
     * @class LayerWindow
     * @brief Window for managing and displaying render layers.
     * 
     * Shows available render layers and displays properties of selected layers.
     * Allows users to inspect texture preview and layer properties.
     */
    class LayerWindow : public IWindow {
    private:
        IPropertyRenderable *m_selected_layer = nullptr;
        std::shared_ptr<PropertyWindow> m_property_window = nullptr;

    public:
        LayerWindow(std::shared_ptr<PropertyWindow> property_window)
            : IWindow("Layers"), m_property_window(property_window) {}
        ~LayerWindow();

        virtual void RenderWindow() override;
        void LayerSelected(std::pair<const int, SDL_Texture *> layer);
    };

    class LayerProperty : public IPropertyRenderable {
    private:
        SDL_Texture *m_texture;

    public:
        LayerProperty(SDL_Texture *texture) : m_texture(texture) {}
        ~LayerProperty() = default;

        void RenderProperties(int &id) override {
            PropertyNodes::TexturePreview::RenderProperty(id, "Layer Texture", m_texture);
        }
    };
} // namespace HBE::Application::GUI