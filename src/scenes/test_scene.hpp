#pragma once

#include <core.hpp>

// Include GameObjects
#include "../gameobjects/ui/text.hpp"
#include "../gameobjects/player.hpp"
#include "../gameobjects/tile.hpp"

using namespace Core::ECS;
using namespace GameObjects;

namespace Scenes {
    struct TestScene : Scene {
        TestScene()
        : Scene("TestScene") {}

        ~TestScene() = default;

        void SetupScene(Core::Application::App& app) override {
            std::cout << "Test scene setup" << std::endl;

            // Setup entities and components
            auto fpsText = UI::Text(app);
            auto testText = UI::Text(app);
    
            // Setup fps counter
            fpsText.GetComponent<Text>()._size = 5;
            fpsText.GetComponent<Text>().SetText("The quick brown fox jumps over the lazy dog");
            fpsText.GetComponent<Text>()._wrapping_width = 50;
            fpsText.AddComponent<Controller>();
    
            // Setup test text
            testText.GetComponent<Transform2D>()._position = { 500.0f, 50.0f };
            testText.GetComponent<Transform2D>()._layer = 1;
            testText.GetComponent<Texture>()._size = { 500.0f, 100.0f };
            testText.GetComponent<Text>()._size = 50;
            testText.GetComponent<Text>().SetText("Layer 1!");
        }

        void UnloadScene() override {
            std::cout << "Test scene unloaded" << std::endl;

            // Unload entities and components
        }
    };
}