#pragma once

#include <SDL.h>

namespace Components {
    struct Texture : public Object {
        SDL_Texture* texture;

        std::string ToString() const override {
            std::stringstream str;
            str << "    Component: Texture \n";

            return str.str();
        }
    };
}