/**
 * @file transform_system.hpp
 * @author Daniel Parker (DParker13)
 * @brief System for 2D transform management.
 * @version 0.1
 * @date 2025-03-02
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/core/isystem.hpp>
#include <HotBeanEngine/defaults/components/miscellaneous/transform_2d.hpp>

namespace HBE::Default::Systems {
    using HBE::Core::EntityID;
    using HBE::Default::Components::Transform2D;

    /**
     * @brief Updates entity transforms and hierarchy
     *
     * Computes world-space transforms from local transforms.
     * Handles parent-child transformation propagation.
     */
    class TransformSystem : public HBE::Core::ISystem {
    public:
        REQUIRES_COMPONENTS(Transform2D);
        DEFINE_NAME("Transform System")

    public:
        TransformSystem() = default;
        ~TransformSystem() = default;

        void OnEntityAdded(EntityID entity) override;
        void OnEntityRemoved(EntityID entity) override;
    };
} // namespace HBE::Default::Systems