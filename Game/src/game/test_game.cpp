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
        TestGame::TestGame(std::string title, int width, int height)
            : Game(title, width, height) {}
    
        /**
         * @brief Initializes all systems in the game. This function creates an 
         * instance of each system that is used in the game.
         * 
         * @note The System Manager is responsible for cleaning up these
         * systems when they're no longer needed.
         */
        void TestGame::SetupSystems() {
            std::filesystem::path font_path = std::filesystem::current_path().parent_path() / "assets" / "fonts" / "LT_Superior_Mono" / "LTSuperiorMono-Regular.ttf";

            new PhysicsSystem();
            new RenderSystem();
            new InputSystem();
            new PlayerControllerSystem();
            new UISystem(font_path.string());
            //new TileMapSystem();
            new AudioSystem();
        }

        void TestGame::OnStart() {
            Game::OnStart();

            std::filesystem::path test_scene_path = std::filesystem::current_path().parent_path() / "scenes" / "test.yaml";
            std::shared_ptr<Scenes::TestScene> test_scene = std::make_shared<Scenes::TestScene>(test_scene_path.string());

            _serialization_manager->RegisterScene(test_scene);
            _serialization_manager->LoadScene(test_scene);

            Entity text = CreateEntity();
            AddComponent<Transform2D>(text, Transform2D());
            AddComponent<Texture>(text, Texture());
            AddComponent<Text>(text, Text());

            Text& textComponent = GetComponent<Text>(text);
            textComponent.SetText("Loaded from code!");
            textComponent._type = UIElement::UIType::Text;
        }
    }
}