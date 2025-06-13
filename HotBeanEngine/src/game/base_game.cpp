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

#include "base_game.hpp"

namespace Core {
    namespace Application {
        BaseGame::BaseGame(const std::string& config_path)
            : BaseGame(config_path, ComponentFactory()) {}

        BaseGame::BaseGame(const std::string& config_path, ComponentFactory component_factory)
            : App(config_path) {
            component_factory.RegisterComponents(*m_ecs_manager);
        }
    }
}