/**
 * @file default_scene.hpp
 * @author Daniel Parker (DParker13)
 * @brief Default scene implementation. Sets up default systems for a basic game scene.
 * @version 0.1
 * @date 2025-10-17
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/defaults/default_scene_serializer.hpp>
#include <HotBeanEngine/defaults/systems/default_systems.hpp>

namespace HBE::Default {
    using namespace HBE::Application;
    using namespace HBE::Default::Systems;

    /**
     * @brief Default scene implementation with standard setup
     *
     * Provides basic scene configuration and system initialization.
     * Serves as template for custom scene implementations.
     */
    class DefaultScene : public HBE::Core::Scene {
    public:
        DefaultScene(std::string name, std::string path, std::shared_ptr<HBE::Core::ISerializer> serializer)
            : Scene(name, path, serializer) {}

        /**
         * @brief Initializes the default systems needed for basic game functionality.
         * The order each system is initialized is important! That is the order they are then called.
         */
        void SetupSystems();
    };
} // namespace HBE::Default