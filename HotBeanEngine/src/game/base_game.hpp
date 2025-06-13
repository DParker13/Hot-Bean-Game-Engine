/**
 * @file game.hpp
 * @author Daniel Parker (DParker13)
 * @brief Header file for the BaseGame class.
 * @version 0.1
 * @date 2025-04-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once

#include "../core/core.hpp"

namespace Core {
    /**
     * @class Game
     * @brief The main interface for the game application.
     *
     * This class inherits from the Application class and provides additional functionality for game-specific logic.
     */
    namespace Application {
        // Interface for all Application layers ordered in calling order
        class BaseGame : public App {
            public:
                BaseGame(const std::string& config_path);
                BaseGame(const std::string& config_path, ComponentFactory component_factory);
                ~BaseGame() = default;
                BaseGame(const BaseGame&) = delete;
                BaseGame& operator=(const BaseGame&) = delete;

            protected:
                ComponentFactory _component_factory;
        };
    }
}