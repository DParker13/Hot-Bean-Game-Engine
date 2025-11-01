#pragma once

#include <random>

#include "../systems/audio_system.hpp"

namespace Scenes {
    using namespace HBE::Core;
    using namespace HBE::Default::Components;
    
    struct ExampleScene : public HBE::Default::DefaultScene {
        ExampleScene(std::string path, std::shared_ptr<ISerializer> serializer)
        : DefaultScene("ExampleScene", path, serializer) {}

        ~ExampleScene() = default;

        void SetupSystems() override;
        void SetupScene() override;
    };
}