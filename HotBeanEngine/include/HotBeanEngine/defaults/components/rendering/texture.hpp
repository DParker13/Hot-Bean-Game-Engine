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

namespace HBE::Default::Components {
    using namespace HBE::Core;
    
    /**
     * @brief Texture rendering component
     * 
     * Stores texture data and rendering properties.
     * Supports sprite rendering with source rectangles.
     */
    struct Texture : public IComponent, public HBE::Application::GUI::IPropertyRenderable {
        SDL_Texture* m_texture = nullptr; ///< A pointer to the SDL texture object. Can be null if the texture has not been loaded.
        glm::vec2 m_size = {0, 0}; ///< Size of the texture in pixels.
        bool m_dirty = true;

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

        void RenderProperties(EntityID entity, IComponent* component) override {
            auto* texture = dynamic_cast<Texture*>(component);

            if (!texture) {
                return;
            }

            HBE::Application::GUI::RenderProperties<Texture>(entity, texture, [](EntityID entity, auto* tex) {
                HBE::Application::GUI::PropertyNodes::Bool::RenderProperty(entity, "Dirty", tex->m_dirty);
                HBE::Application::GUI::PropertyNodes::Vec2::RenderProperty(entity, "Size", tex->m_size);
            });
        }
    };
}