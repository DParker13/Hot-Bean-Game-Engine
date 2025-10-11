#pragma once

#include <random>

#include "../systems/audio_system.hpp"

using namespace HBE::Default::Components;

namespace Scenes {
    struct ExampleScene : public HBE::Default::DefaultScene {
        ExampleScene(std::string path, std::shared_ptr<ISerializer> serializer)
        : DefaultScene("ExampleScene", path, serializer) {}

        ~ExampleScene() = default;

        void SetupSystems() override;
        void SetupScene() override;
    };
}