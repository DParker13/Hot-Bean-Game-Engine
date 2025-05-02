/**
 * @file game.cpp
 * @author Daniel Parker (DParker13)
 * @brief Game base class. Registers default components.
 * @version 0.1
 * @date 2025-04-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "game.hpp"

namespace Core {
    namespace Application {
        Game::Game(std::string title, int width, int height)
            : Game(title, width, height, ComponentRegister()) {}

        Game::Game(std::string title, int width, int height, ComponentRegister component_register)
            : App(title, width, height), _component_register(component_register) {
                component_register.RegisterComponents();
        }
    }
}