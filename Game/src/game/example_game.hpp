/**
 * @file example_game.cpp
 * @author Daniel Parker (DParker13)
 * @brief Game logic implementation.
 * Handles game state updates, user input processing, and rendering ontop of the Application class.
 * @version 0.1
 * @date 2025-04-17
 * 
 * @copyright Copyright (c) 2025
 */
#pragma once

#include "../scenes/example_scene.hpp"

namespace Game {
    using namespace HBE::Application;

    class ExampleGame : public Application {
        public:
            ExampleGame(const std::string& config_path, std::shared_ptr<IComponentFactory> component_factory);
            ~ExampleGame() = default;
            
        protected:
            void OnStart() override;
    };
}