#pragma once

#include <HotBeanEngine/application/application.hpp>

struct TestSystem : public HBE::Core::ISystem {
    DEFINE_NAME("TestSystem");
    TestSystem() = default;
    void SetSignature() override {}
};