#pragma once

#include <HotBeanEngine/core/system.hpp>

struct TestSystem : public HBE::Core::System {
    TestSystem() = default;
    void SetSignature() override {}
};