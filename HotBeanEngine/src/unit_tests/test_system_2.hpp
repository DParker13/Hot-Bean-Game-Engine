#pragma once

#include <HotBeanEngine/application/application.hpp>

struct TestSystem2 : public HBE::Core::GameSystem<> {
    DEFINE_NAME("TestSystem2");
    TestSystem2() = default;

    bool on_start_called = false;
    bool on_update_called = false;

    void OnStart() override { on_start_called = true; }

    void OnUpdate() override { on_update_called = true; }
};
