#pragma once

#include <HotBeanEngine/application/application.hpp>

struct TestComponent : public HBE::Core::Component {
    int m_value = 0;

    DEFINE_NAME("TestComponent")
    TestComponent() = default;
};