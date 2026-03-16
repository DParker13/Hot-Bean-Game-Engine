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

#include <HotBeanEngine/core/all_core.hpp>
#include <HotBeanEngine/editor/iproperty_renderable.hpp>

namespace HBE::Default::Components {

    /**
     * @brief Texture rendering component
     *
     * Stores texture data and rendering properties.
     * Supports sprite rendering with source rectangles.
     */
    struct Texture : public Core::IComponent, public Core::DirtyFlag, public Application::GUI::IPropertyRenderable {
        SDL_Texture *m_texture =
            nullptr; ///< A pointer to the SDL texture object. Can be null if the texture has not been loaded.
        glm::vec2 m_size = {0, 0}; ///< Size of the texture in pixels.

        DEFINE_NAME("Texture");
        Texture() = default;
        ~Texture();

        void Serialize(YAML::Emitter &out) const override;
        void RenderProperties(int &id);
    };
} // namespace HBE::Default::Components