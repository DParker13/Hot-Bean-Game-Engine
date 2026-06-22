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

#include <HotBeanEngine/HotBeanEngine.hpp>

namespace Scenes {
    /**
     * @class ExampleScene
     * @brief Example scene demonstrating scene setup and configuration.
     *
     * Sets up the initial game scene with cameras, entities, physics components,
     * and rendering systems. Demonstrates best practices for scene initialization
     * and entity/component configuration.
     */
    class ExampleScene : public HBE::Application::Scene {
    private:
        std::vector<HBE::Application::Managers::SubscriptionHandle> m_event_subscription_handles;

    public:
        ExampleScene(std::string path, std::shared_ptr<HBE::Core::ISerializable> serializer)
            : Scene("ExampleScene", path, serializer) {}

        ~ExampleScene() = default;

        void SetupScene() override;
        void CleanupScene() override;

    protected:
        void SetupCustomSystems() override;
    };
} // namespace Scenes