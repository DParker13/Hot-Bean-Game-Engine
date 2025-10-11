#pragma once

#include <HotBeanEngine/core/component.hpp>

struct TestComponent : public HBE::Core::Component {
    int m_value = 0;

    TestComponent() = default;

    std::string GetName() const override {
        return "TestComponent";
    }
};