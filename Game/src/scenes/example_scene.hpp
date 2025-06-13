#pragma once

#include <HotBeanEngine.hpp>

#include "../systems/audio_system.hpp"

using namespace Core::ECS;
using namespace Core::Application;
using namespace Systems;

namespace Scenes {
    struct ExampleScene : public BaseScene {
        ExampleScene(std::string path)
        : BaseScene("ExampleScene", path) {}

        ~ExampleScene() = default;

        void SetupPreSystems() override;
        void SetupScene() override;
    };
}