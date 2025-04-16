#pragma once

#include <core.hpp>

// Include GameObjects
#include "../gameobjects/ui/text.hpp"
#include "../gameobjects/player.hpp"
#include "../gameobjects/tile.hpp"

using namespace Core::ECS;
using namespace Core::Application;
using namespace GameObjects;

namespace Scenes {
    struct TestScene : Scene {
        TestScene()
        : Scene("TestScene") {}

        ~TestScene() = default;

        // Setup entities and components
        std::shared_ptr<UI::Text> fpsText;
        std::shared_ptr<UI::Text> testText;

        void RegisterComponents(App& app) override {
            std::shared_ptr<ECSManager> ecs_manager = app.GetECSManager();
            ecs_manager->RegisterComponentType<Text>();
            ecs_manager->RegisterComponentType<Text>();
            ecs_manager->RegisterComponentType<Transform2D>();
            ecs_manager->RegisterComponentType<Texture>();
            ecs_manager->RegisterComponentType<Controller>();
        }

        void SetupScene(App& app) override {
            std::cout << "Test scene setup" << std::endl;

            fpsText = std::make_shared<UI::Text>(app);
            testText = std::make_shared<UI::Text>(app);
    
            // Setup fps counter
            fpsText->GetComponent<Text>()._size = 5;
            fpsText->GetComponent<Text>().SetText("The quick brown fox jumps over the lazy dog");
            fpsText->GetComponent<Text>()._wrapping_width = 50;
    
            // Setup test text
            testText->GetComponent<Transform2D>()._position = { 500.0f, 50.0f };
            testText->GetComponent<Transform2D>()._layer = 1;
            testText->GetComponent<Texture>()._size = { 500.0f, 100.0f };
            testText->GetComponent<Text>()._size = 50;
            testText->GetComponent<Text>().SetText("Layer 1!");
        }

        void UnloadScene(App& app) override {
            std::cout << "Test scene unloaded" << std::endl;
            
            app.GetECSManager()->DestroyEntity(fpsText->GetEntity());
            app.GetECSManager()->DestroyEntity(fpsText->GetEntity());
        }
    };
}