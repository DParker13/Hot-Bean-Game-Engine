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

#include <core.hpp>

namespace Components {
    struct Texture : public Component {
        /// @brief A pointer to the SDL texture object. Can be null if the texture has not been loaded.
        SDL_Texture* _texture = nullptr;
        /// @brief Size of the texture in pixels
        glm::ivec2 _size = {0, 0};

        Texture() = default;

        /**
         * @brief Destroy the Texture component
         */
        ~Texture() {
            if (_texture) {
                SDL_DestroyTexture(_texture);
            }
        }

        std::string ToString() const override {
            std::stringstream str;
            str << "    Component: Texture \n";

            return str.str();
        }
    };
}