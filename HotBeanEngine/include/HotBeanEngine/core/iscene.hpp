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
    struct IScene {
        std::shared_ptr<ISerializer> m_serializer;
        std::string m_name;
        std::filesystem::path m_scene_path;

        IScene(std::string name, std::filesystem::path scene_path) : m_name(name), m_scene_path(scene_path) {}

        IScene(std::string name, std::filesystem::path scene_path, std::shared_ptr<ISerializer> serializer)
            : m_name(name), m_scene_path(scene_path), m_serializer(serializer) {}

        virtual ~IScene() = default;

        virtual void SetupScene() {};
        virtual void CleanupScene() {};
    };
} // namespace HBE::Core