/**
 * @file example_scene.hpp
 * @author Daniel Parker (DParker13)
 * @brief Example scene demonstrating scene setup and configuration.
 * @version 0.1
 * @date 2025-06-12
 *
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <HotBeanEngine/HotBeanEngine_Defaults.hpp>

namespace Scenes {
    /**
     * @class ExampleScene
     * @brief Example scene demonstrating scene setup and configuration.
     *
     * Sets up the initial game scene with cameras, entities, physics components,
     * and rendering systems. Demonstrates best practices for scene initialization
     * and entity/component configuration.
     */
    struct ExampleScene : public HBE::Default::DefaultScene {
        ExampleScene(std::string path, std::shared_ptr<HBE::Core::ISerializer> serializer)
            : DefaultScene("ExampleScene", path, serializer) {}

        ~ExampleScene() = default;

        void SetupSystems() override;
        void SetupScene() override;
    };
} // namespace Scenes