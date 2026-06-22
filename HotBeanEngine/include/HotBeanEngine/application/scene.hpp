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

#include <HotBeanEngine/core/iscene.hpp>

namespace HBE::Application {
    /**
     * @brief Scene implementation with standard setup
     *
     * Provides basic scene configuration and system initialization.
     * Serves as template for custom scene implementations.
     */
    class Scene : public Core::IScene {
    public:
        Scene(std::string name, std::string path) : IScene(name, path) {}
        virtual ~Scene() = default;

        virtual void SetupScene() override;

        // ISerializable interface
        virtual void Serialize(Core::ISerializationWriter &out) const override;
        virtual void Deserialize(Core::ISerializationReader &in) override;
    };
} // namespace HBE::Application