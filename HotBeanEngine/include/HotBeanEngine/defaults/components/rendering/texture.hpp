/**
 * @file texture.hpp
 * @author Daniel Parker (DParker13)
 * @brief Texture component. Used for rendering textures.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/editor_gui/iproperty_renderable.hpp>

#include <HotBeanEngine/editor_gui/property_nodes/bool.hpp>
#include <HotBeanEngine/editor_gui/property_nodes/vec2.hpp>
#include <HotBeanEngine/editor_gui/property_nodes/texture_preview.hpp>

namespace HBE::Default::Components {
    using namespace HBE::Core;
    using namespace HBE::Application::GUI;
    
    /**
     * @brief Texture rendering component
     * 
     * Stores texture data and rendering properties.
     * Supports sprite rendering with source rectangles.
     */
    struct Texture : public IComponent, public IMemberChanged, public IPropertyRenderable {
        SDL_Texture* m_texture = nullptr; ///< A pointer to the SDL texture object. Can be null if the texture has not been loaded.
        glm::vec2 m_size = {0, 0}; ///< Size of the texture in pixels.

        DEFINE_NAME("Texture");
        Texture() = default;

        ~Texture() {
            if (m_texture) {
                SDL_DestroyTexture(m_texture);
            }
        }

        void Serialize(YAML::Emitter& out) const override {
            out << YAML::Key << "size" << YAML::Value << m_size;
        }

        void RenderProperties(int& id) override {
            if (PropertyNodes::Vec2::RenderProperty(id, "Size", m_size, {0.0f, 0.0f})) {
                MarkDirty();
            }

            PropertyNodes::TexturePreview::RenderProperty(id, "Texture Preview", m_texture);
        }
    };
}