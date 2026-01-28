/**
 * @file system_manager_test.cpp
 * @author Daniel Parker (DParker13)
 * @brief Unit tests for the SystemManager class.
 * Tests system registration, lifecycle events, and entity signature matching.
 * @version 0.1
 * @date 2025-07-06
 *
 * @copyright Copyright (c) 2025
 */

#include <catch2/catch_all.hpp>

#include "test_system.hpp"
#include <HotBeanEngine/application/managers/system_manager.hpp>

using namespace HBE::Core;
using namespace HBE::Application::Managers;

TEST_CASE("SystemManager: Register and Unregister System") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    SystemManager system_manager = SystemManager(logging_manager);
    system_manager.RegisterSystem<TestSystem>();

    SECTION("Register system") {
        TestSystem *test_system_pointer = system_manager.GetSystem<TestSystem>();
        REQUIRE(test_system_pointer != nullptr);
    }

    SECTION("Unregister system") {
        system_manager.UnregisterSystem<TestSystem>();
        TestSystem *test_system_pointer = system_manager.GetSystem<TestSystem>();
        REQUIRE(test_system_pointer == nullptr);
    }
}