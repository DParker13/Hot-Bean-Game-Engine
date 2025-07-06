#include "test_system.hpp"
#include <catch2/catch_all.hpp>

using namespace Core::ECS;
using namespace Core::Managers;

TEST_CASE("SystemManager: Register and Unregister System") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    SystemManager system_manager = SystemManager(logging_manager);
    system_manager.RegisterSystem<TestSystem>();

    SECTION("Register system") {
        TestSystem* test_system_pointer = system_manager.GetSystem<TestSystem>();
        REQUIRE(test_system_pointer != nullptr);
    }

    SECTION("Unregister system") {
        system_manager.UnregisterSystem<TestSystem>();
        TestSystem* test_system_pointer = system_manager.GetSystem<TestSystem>();
        REQUIRE(test_system_pointer == nullptr);
    }
}