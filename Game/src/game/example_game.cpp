/**
 * @file example_game.cpp
 * @author Daniel Parker (DParker13)
 * @brief Game logic implementation.
 * Handles game state updates, user input processing, and rendering ontop of the Application class.
 * @version 0.1
 * @date 2025-02-18
 *
 * @copyright Copyright (c) 2025
 */

#include "example_game.hpp"
#include "../scenes/example_scene.hpp"

namespace Game {
    ExampleGame::ExampleGame(std::shared_ptr<HBE::Application::IComponentFactory> component_factory)
        : Application(component_factory) {}

    void ExampleGame::OnStart() {}
} // namespace Game