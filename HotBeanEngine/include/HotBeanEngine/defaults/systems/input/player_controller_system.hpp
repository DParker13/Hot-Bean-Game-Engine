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

#include <HotBeanEngine/defaults/systems/input/input_system.hpp>
#include <HotBeanEngine/defaults/components/default_components.hpp>

namespace HBE::Default::Systems {
    using namespace HBE::Core;
    using namespace HBE::Default::Components;
    
    /**
     * @brief System for player input to control entities.
     */
    class PlayerControllerSystem : public ISystem {
        private:
            InputSystem& m_input_system;

        public:
            DEFINE_SIGNATURE(PlayerControllerSystem, "Player Controller System", Transform2D, Controller);
            PlayerControllerSystem(InputSystem& input_system)
                : m_input_system(input_system) {}
            ~PlayerControllerSystem() = default;

            void OnUpdate() override;

            void Move(EntityID entity, float speed);
    };
}