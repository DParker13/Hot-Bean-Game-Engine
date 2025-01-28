#pragma once

#include <SDL.h>

namespace Components {
    struct Tile : public Object {
        Uint8 _type;
        Uint8 _size;
        SDL_Vertex _vertices[4];
        SDL_Color _color;

        int _INDICES[6] = { 0, 1, 2, 1, 3, 2 };

        std::string ToString() const override {
            std::stringstream str;
            str << "    Component: Tile \n";

            return str.str();
        }
    };
}