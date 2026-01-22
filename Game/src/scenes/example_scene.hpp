#pragma once

#include <random>

#include "../systems/audio_system.hpp"

namespace Scenes {
    struct ExampleScene : public HBE::Default::DefaultScene {
        ExampleScene(std::string path, std::shared_ptr<HBE::Core::ISerializer> serializer)
        : DefaultScene("ExampleScene", path, serializer) {}

        ~ExampleScene() = default;

        void SetupSystems() override;
        void SetupScene() override;
    };
}