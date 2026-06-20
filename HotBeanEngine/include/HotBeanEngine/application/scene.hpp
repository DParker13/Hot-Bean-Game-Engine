/**
 * @file scene.hpp
 * @author Daniel Parker (DParker13)
 * @brief Scene implementation with standard setup. Sets up default systems for a basic game scene.
 * @version 0.1
 * @date 2025-10-17
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/core/all_core.hpp>

namespace HBE::Application {
    /**
     * @brief Scene implementation with standard setup
     *
     * Provides basic scene configuration and system initialization.
     * Serves as template for custom scene implementations.
     */
    class Scene : public Core::IScene {
    public:
        Scene(std::string name, std::string path, std::shared_ptr<Core::ISerializer> serializer)
            : IScene(name, path, serializer) {}

        void SetupScene() override;
    };
} // namespace HBE::Application