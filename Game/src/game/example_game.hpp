/**
 * @file example_game.cpp
 * @author Daniel Parker (DParker13)
 * @brief Game logic implementation.
 * Handles game state updates, user input processing, and rendering ontop of the Application class.
 * @version 0.1
 * @date 2025-04-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once

#include <HotBeanEngine.hpp>

#include "../scenes/example_scene.hpp"

using namespace Core::Components;
using namespace Core::Systems;

class ExampleGame : public BaseGame {
    public:
        ExampleGame(const std::string& config_path);
        ~ExampleGame() = default;
        
        void OnStart() override;
};