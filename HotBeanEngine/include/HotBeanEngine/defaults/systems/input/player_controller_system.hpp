/**
 * @file player_controller_system.hpp
 * @author Daniel Parker (DParker13)
 * @brief System for player input to control entities.
 * @version 0.1
 * @date 2025-03-02
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/core/isystem.hpp>
#include <HotBeanEngine/defaults/components/input/controller.hpp>
#include <HotBeanEngine/defaults/components/miscellaneous/transform_2d.hpp>

namespace HBE::Default::Systems {
    using HBE::Core::EntityID;
    using HBE::Default::Components::Transform2D;
    using HBE::Default::Components::Controller;
    /**
     * @brief System for player input to control entities.
     */
    class PlayerControllerSystem : public HBE::Core::ISystem {
    public:
        REQUIRES_COMPONENTS(Transform2D, Controller);
        DEFINE_NAME("Player Controller System")

        PlayerControllerSystem() = default;
        ~PlayerControllerSystem() = default;

        void OnUpdate() override;
        void Move(EntityID entity, float speed);
    };
} // namespace HBE::Default::Systems