#pragma once

#include "../../ecs/component.hpp"

struct TestComponent : public Core::ECS::Component {
    int m_value = 0;

    TestComponent() = default;

    std::string GetName() const override {
        return "TestComponent";
    }
};