/**
 * @file scene.hpp
 * @author Daniel Parker (DParker13)
 * @brief Used to setup and control switching between other initialized scenes.
 * @version 0.1
 * @date 2025-03-24
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <memory>

#include <HotBeanEngine/core/serializer.hpp>

namespace HBE::Core {
    /**
     * @brief Base interface for a scene that handles entities and components.
     * Manages scene-specific setup, serialization, and system configuration.
     * Provides lifecycle hooks for scene initialization.
     */
    struct Scene {
        std::shared_ptr<ISerializer> m_serializer;
        std::string m_name;
        std::string m_scene_path;

        Scene(std::string name, std::string scene_path) : m_name(name), m_scene_path(scene_path) {}

        Scene(std::string name, std::string scene_path, std::shared_ptr<ISerializer> serializer)
            : m_name(name), m_scene_path(scene_path), m_serializer(serializer) {}

        ~Scene() = default;

        virtual void SetupScene() = 0;
        /**
         * @brief Initializes the systems needed for this scene in the system manager.
         */
        virtual void SetupSystems() = 0;
    };
} // namespace HBE::Core