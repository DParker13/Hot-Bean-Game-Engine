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

#include <filesystem>
#include <memory>

#include <HotBeanEngine/core/iserializable.hpp>

namespace HBE::Core {
    /**
     * @brief Base interface for a scene that handles entities and components.
     * Manages scene-specific setup, serialization, and system configuration.
     * Provides lifecycle hooks for scene initialization.
     */
    struct IScene : public ISerializable {
        std::string m_name;
        std::filesystem::path m_scene_path;

        IScene(std::string name, std::filesystem::path scene_path) : m_name(name), m_scene_path(scene_path) {}
        virtual ~IScene() = default;

        virtual void SetupScene() {};
        virtual void CleanupScene() {};

        // ISerializable interface
        virtual void Serialize(ISerializationWriter &out) const = 0;
        virtual void Deserialize(ISerializationReader &in) = 0;
    };
} // namespace HBE::Core