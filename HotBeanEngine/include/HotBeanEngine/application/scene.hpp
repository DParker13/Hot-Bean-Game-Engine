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

        /**
         * @brief Initializes systems for the scene.
         *
         * Registers engine default systems first, then allows the game scene
         * to append additional systems through SetupCustomSystems().
         */
        void SetupSystems() override;
        void SetupScene() override;

    protected:
        /**
         * @brief Controls whether engine default systems should be registered.
         */
        virtual bool IncludeDefaultSystems() const { return true; }

        /**
         * @brief Hook for game scenes to register scene-specific systems.
         */
        virtual void SetupCustomSystems() {}

    private:
        /**
         * @brief Registers engine-provided default systems.
         *
         * The order each system is initialized is important because this is
         * the order they are called during iteration.
         */
        void SetupDefaultSystems();
    };
} // namespace HBE::Application