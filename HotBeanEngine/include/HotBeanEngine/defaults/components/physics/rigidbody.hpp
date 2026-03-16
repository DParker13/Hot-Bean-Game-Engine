/**
 * @file rigidbody.hpp
 * @author Daniel Parker (DParker13)
 * @brief Rigidbody component. Used for 2D physics calculations.
 * @version 0.1
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <box2d/box2d.h>

#include <HotBeanEngine/core/all_core.hpp>
#include <HotBeanEngine/editor/iproperty_renderable.hpp>

namespace HBE::Default::Components {

    /**
     * @brief Physics body component for 2D dynamics
     *
     * Integrates with Box2D physics engine.
     * Handles mass, velocity, and collision response.
     */
    class RigidBody : public Core::IComponent, public Application::GUI::IPropertyRenderable {
    public:
        float m_mass = 1.0f;
        b2BodyType m_type = b2BodyType::b2_kinematicBody;
        b2BodyId m_body_id = b2BodyId(); // ID of the body in the Box2D physics engine

        DEFINE_NAME("RigidBody");
        RigidBody() = default;

        void Serialize(YAML::Emitter &out) const override;
        void Deserialize(YAML::Node &node) override;
        void RenderProperties(int &id);
    };
} // namespace HBE::Default::Components
