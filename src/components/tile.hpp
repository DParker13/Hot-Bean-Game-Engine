/**
 * @file tile.hpp
 * @author Daniel Parker (DParker13)
 * @brief Tile component. Used for rendering tiles (simple rectangles).
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include <SDL.h>

namespace Components {
    struct Tile : public Component {
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