#pragma once

#include <HotBeanEngine/application/application.hpp>

struct TestSystem : public HBE::Core::GameSystem<> {
    DEFINE_NAME("TestSystem");
    TestSystem() = default;
};