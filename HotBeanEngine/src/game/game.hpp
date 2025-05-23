/**
 * @file game.hpp
 * @author Daniel Parker (DParker13)
 * @brief Header file for the Game class.
 * @version 0.1
 * @date 2025-04-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once

#include "../core/core.hpp"
#include "../systems/default_systems.hpp"
#include "../gameobjects/default_gameobjects.hpp"

using namespace Systems;

namespace Core {
    /**
     * @class Game
     * @brief The main interface for the game application.
     *
     * This class inherits from the Application class and provides additional functionality for game-specific logic.
     */
    namespace Application {
        // Interface for all Application layers ordered in calling order
        class Game : public App {
            public:
                /**
                 * @brief Constructs an instance of Game with the specified title, width, and height.
                 * @param title The title of the application window.
                 * @param width The width of the application window.
                 * @param height The height of the application window.
                 */
                Game(const std::string& config_path);
                Game(const std::string& config_path, ComponentFactory component_factory);
                ~Game() = default;
                Game(const Game&) = delete;
                Game& operator=(const Game&) = delete;

                void SetupSystems() override;

            protected:
                ComponentFactory _component_factory;
        };
    }
}