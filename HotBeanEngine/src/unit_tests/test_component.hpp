#pragma once

#include "../../include/HotBeanEngine.hpp"

struct TestComponent : public Component {
    int m_value = 0;

    TestComponent() = default;

    std::string GetName() const override {
        return "TestComponent";
    }
};