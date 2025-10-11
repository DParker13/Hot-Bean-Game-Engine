#pragma once

#include <HotBeanEngine/defaults/systems/input/input_system.hpp>
#include <HotBeanEngine/defaults/components/default_components.hpp>

using namespace HBE::Default::Components;
using namespace HBE::Application;
using namespace HBE::Core;

namespace HBE::Default::Systems {
    class PhysicsSystem : public System {
    private:
        InputSystem& m_input_system;
        glm::vec2 m_gravity = {0.0f, 9.8f};
        b2WorldId m_world_id = b2WorldId();

    public:
        DEFINE_SIGNATURE(PhysicsSystem, Transform2D, RigidBody);
            
        PhysicsSystem(InputSystem& input_system, glm::vec2 gravity)
            : m_input_system(input_system), m_gravity(gravity) {}

        PhysicsSystem(InputSystem& input_system)
            : PhysicsSystem(input_system, glm::vec2(0.0f, 9.8f)) {}

        void OnStart() override;
        void OnFixedUpdate() override;
        void OnEntityAdded(Entity entity) override;
        void OnEntityRemoved(Entity entity) override;

    private:
        float DegreesToRadians(float degrees) {
            return degrees * (B2_PI / 180.0f);
        }

        float RadiansToDegrees(float radians) {
            return radians * (180.0f / B2_PI);
        }
    };
}