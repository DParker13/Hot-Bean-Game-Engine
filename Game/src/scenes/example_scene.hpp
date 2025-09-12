#pragma once

#include <HotBeanEngine.hpp>

#include "../systems/audio_system.hpp"

using namespace HBE::Core;
using namespace HBE::Application;
using namespace HBE::Archetypes;
using namespace Systems;

namespace Scenes {
    struct ExampleScene : public BaseScene {
        ExampleScene(std::string path)
        : BaseScene("ExampleScene", path) {}

        ~ExampleScene() = default;

        void SetupSystems() override;
        void SetupScene() override;
    };
}