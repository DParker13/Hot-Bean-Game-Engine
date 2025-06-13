/**
 * @file texture.hpp
 * @author Daniel Parker (DParker13)
 * @brief Texture component. Used for rendering textures.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "../../ecs/all_ecs.hpp"

namespace Core::Components {
    struct Texture : public Component {
        SDL_Texture* m_texture = nullptr; ///< A pointer to the SDL texture object. Can be null if the texture has not been loaded.
        glm::ivec2 m_size = {0, 0}; ///< Size of the texture in pixels.

        Texture() = default;

        std::string GetName() const override {
            return "Texture";
        }

        /**
         * @brief Destroy the Texture component
         */
        ~Texture() {
            if (m_texture) {
                SDL_DestroyTexture(m_texture);
            }
        }

        void Serialize(YAML::Emitter& out) const override {
            out << YAML::Key << "size" << YAML::Value << m_size;
        }
    };
}