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

#include "../core/core.hpp"

namespace Components {
    struct Texture : public Component {
        SDL_Texture* _texture = nullptr; ///< A pointer to the SDL texture object. Can be null if the texture has not been loaded.
        glm::ivec2 _size = {0, 0}; ///< Size of the texture in pixels.

        Texture() {
            Component::_name = "Texture";
        }

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