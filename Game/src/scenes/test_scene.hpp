#pragma once

#include <HotBeanEngine.hpp>

using namespace Core::ECS;
using namespace Core::Application;

namespace Scenes {
    struct TestScene : Scene {
        TestScene(std::string path)
        : Scene("TestScene", path) {}

        ~TestScene() = default;

        void SetupScene() override;
        void UnloadScene() override;
    };
}