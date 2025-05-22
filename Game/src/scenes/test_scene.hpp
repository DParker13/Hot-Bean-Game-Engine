#pragma once

#include <HotBeanEngine.hpp>

#include "../scenes/test_scene.hpp"

using namespace Core::ECS;
using namespace Core::Application;
using namespace GameObjects;

namespace Scenes {
    struct TestScene : Scene {
        TestScene(std::string path)
        : Scene("TestScene", path) {}

        ~TestScene() = default;

        // Setup entities and components
        std::shared_ptr<UI::Text> fpsText;
        std::shared_ptr<UI::Text> testText;

        void SetupScene() override {
            App& app = App::GetInstance();

            fpsText = std::make_shared<UI::Text>();
            testText = std::make_shared<UI::Text>();
    
            // Setup test text 1
            fpsText->GetComponent<Text>()._size = 5;
            fpsText->GetComponent<Text>().SetText("The quick brown fox jumps over the lazy dog");
            fpsText->GetComponent<Text>()._wrapping_width = 50;
    
            // Setup test text 2
            testText->GetComponent<Transform2D>().m_world_position = { 500.0f, 50.0f };
            testText->GetComponent<Transform2D>().m_layer = 1;
            testText->GetComponent<Texture>()._size = { 500.0f, 100.0f };
            testText->GetComponent<Text>()._size = 50;
            testText->GetComponent<Text>().SetText("Layer 1!");
        }

        void UnloadScene() override {
            App& app = App::GetInstance();
            
            app.GetECSManager()->DestroyEntity(fpsText->GetEntity());
            app.GetECSManager()->DestroyEntity(fpsText->GetEntity());
        }
    };
}