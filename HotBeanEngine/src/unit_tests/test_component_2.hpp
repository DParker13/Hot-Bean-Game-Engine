#pragma once

#include <HotBeanEngine/application/application.hpp>

struct TestComponent2 : public HBE::Core::IComponent {
    float m_x = 0.0f;
    float m_y = 0.0f;

    DEFINE_NAME("TestComponent2")
    TestComponent2() = default;
    TestComponent2(float x, float y) : m_x(x), m_y(y) {}
};
