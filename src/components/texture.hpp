#pragma once

#include <SDL.h>

namespace Components {
    struct Texture : public Object {
        /// @brief A pointer to the SDL texture object. Can be null if the texture has not been loaded.
        SDL_Texture* _texture;
        /// @brief Size of the texture in pixels
        glm::ivec2 _size;

        /**
         * Destructor for the Texture class.
         *
         * This function destroys the SDL_Texture.
         */
        ~Texture() {
            SDL_DestroyTexture(_texture);
        }

        Texture() = default;

        std::string ToString() const override {
            std::stringstream str;
            str << "    Component: Texture \n";

            return str.str();
        }
    };
}