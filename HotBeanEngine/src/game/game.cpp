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
            : App(title, width, height) {
            Components::DefaultComponents::RegisterComponents(App::GetInstance().GetECSManager());
        }
    }
}