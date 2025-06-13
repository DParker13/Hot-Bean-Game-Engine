/**
 * @file example_game.cpp
 * @author Daniel Parker (DParker13)
 * @brief Game logic implementation.
 * Handles game state updates, user input processing, and rendering ontop of the Application class.
 * @version 0.1
 * @date 2025-02-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "example_game.hpp"

ExampleGame::ExampleGame(const std::string& config_path)
    : BaseGame(config_path) {}

void ExampleGame::OnStart() {
    std::filesystem::path test_scene_path = std::filesystem::current_path() / "scenes" / "example_scene.yaml";
    std::shared_ptr<Scenes::ExampleScene> test_scene = std::make_shared<Scenes::ExampleScene>(test_scene_path.string());

    m_serialization_manager->RegisterScene(test_scene);
    m_serialization_manager->LoadScene(test_scene);
}