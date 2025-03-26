/**
 * @file game.hpp
 * @author Daniel Parker (DParker13)
 * @brief Header file for the Game class.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once

#include <core.hpp>

// Include Systems
#include "../systems/physics_system.hpp"
#include "../systems/render_system.hpp"
#include "../systems/input_system.hpp"
#include "../systems/player_controller_system.hpp"
#include "../systems/ui_system.hpp"
#include "../systems/tilemap_system.hpp"
#include "../systems/audio_system.hpp"

#include "../scenes/test_scene.hpp"

using namespace Components;
using namespace GameObjects;
using namespace Systems;
using namespace Scenes;

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
                Game(std::string title, int width, int height);
                ~Game();

            private:
                /**
                 * @brief Initializes the game systems.
                 */
                void InitSystems() override;

                /**
                 * @brief Called once at the start of the game.
                 */
                void OnInit() override;

                /**
                 * @brief Called before handling events.
                 */
                void OnPreEvent() override {};

                /**
                 * @brief Handles events, such as keyboard and mouse input.
                 *
                 * @param event The event to handle.
                 */
                void OnEvent(SDL_Event& event) override;

                /**
                 * @brief Updates the game state, such as updating the game logic and physics.
                 */
                void OnUpdate() override;

                /**
                 * @brief Renders the game graphics, such as rendering the game world and entities.
                 */
                void OnRender() override;

                /**
                 * @brief Called after rendering.
                 */
                void OnPostRender() override;
        };
    }
}