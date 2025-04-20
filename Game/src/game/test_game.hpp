/**
 * @file test_game.cpp
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

using namespace Systems;

namespace Core {
    namespace Application {
        class TestGame : public Game {
            public:
                TestGame(std::string title, int width, int height);
                ~TestGame() = default;

                void InitSystems() override;
        };
    }
}