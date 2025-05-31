/**
 * @file test_game.cpp
 * @author Daniel Parker (DParker13)
 * @brief Game logic implementation.
 * Handles game state updates, user input processing, and rendering ontop of the Application class.
 * @version 0.1
 * @date 2025-02-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "test_game.hpp"

namespace Core {
    namespace Application {
        TestGame::TestGame(const std::string& config_path)
            : Game(config_path) {}

        void TestGame::SetupSystems() {
            Game::SetupSystems();

            RegisterSystem<CustomAudioSystem>();
            //RegisterSystem<TileMapSystem>();
        }

        void TestGame::OnStart() {
            Game::OnStart();

            std::filesystem::path test_scene_path = std::filesystem::current_path().parent_path() / "scenes" / "test.yaml";
            std::shared_ptr<Scenes::TestScene> test_scene = std::make_shared<Scenes::TestScene>(test_scene_path.string());

            m_serialization_manager->RegisterScene(test_scene);
            m_serialization_manager->LoadScene(test_scene);
            m_serialization_manager->UnloadScene();
        }
    }
}