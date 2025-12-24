#pragma once

#include <imgui.h>
#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/defaults/systems/rendering/render_system.hpp>
#include <HotBeanEngine/editor_gui/property_nodes/texture_preview.hpp>

#include "property_window.hpp"

namespace HBE::Application::GUI {
    class LayerWindow : public IWindow {
        private:
            IPropertyRenderable* m_selected_layer = nullptr;
            std::shared_ptr<PropertyWindow> m_property_window = nullptr;

        public:
            LayerWindow(std::shared_ptr<PropertyWindow> property_window) : IWindow("Layers"), m_property_window(property_window) {}
            ~LayerWindow();

            virtual void RenderWindow() override;
            void LayerSelected(std::pair<const int, SDL_Texture*> layer);
    };

    class LayerProperty : public IPropertyRenderable {
        private:
            SDL_Texture* m_texture;

        public:
            LayerProperty(SDL_Texture* texture) : m_texture(texture) {}
            ~LayerProperty() = default;

            void RenderProperties(int& id) override {
                PropertyNodes::TexturePreview::RenderProperty(id, "Layer Texture", m_texture);
            }
    };
}