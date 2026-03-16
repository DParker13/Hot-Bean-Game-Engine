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

namespace HBE::Default {
    /**
     * @brief Default scene implementation with standard setup
     *
     * Provides basic scene configuration and system initialization.
     * Serves as template for custom scene implementations.
     */
    class DefaultScene : public Core::Scene {
    public:
        DefaultScene(std::string name, std::string path, std::shared_ptr<Core::ISerializer> serializer)
            : Scene(name, path, serializer) {}

        /**
         * @brief Initializes systems for the scene.
         *
         * Registers engine default systems first, then allows the game scene
         * to append additional systems through SetupCustomSystems().
         */
        void SetupSystems() override;

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
} // namespace HBE::Default