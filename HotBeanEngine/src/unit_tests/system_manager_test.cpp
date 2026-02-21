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

#include "test_component.hpp"
#include "test_system.hpp"
#include "test_system_2.hpp"
#include <HotBeanEngine/application/managers/system_manager.hpp>

using namespace HBE::Core;
using namespace HBE::Application::Managers;

TEST_CASE("SystemManager: System Registration") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    std::shared_ptr<ComponentManager> component_manager = std::make_shared<ComponentManager>(logging_manager);
    SystemManager system_manager = SystemManager(component_manager, logging_manager);

    SECTION("Register system") {
        system_manager.RegisterSystem<TestSystem>();
        TestSystem* test_system_pointer = system_manager.GetSystem<TestSystem>();
        
        REQUIRE(test_system_pointer != nullptr);
    }

    SECTION("Get unregistered system returns null") {
        TestSystem* test_system_pointer = system_manager.GetSystem<TestSystem>();
        REQUIRE(test_system_pointer == nullptr);
    }

    SECTION("Register multiple systems") {
        system_manager.RegisterSystem<TestSystem>();
        system_manager.RegisterSystem<TestSystem2>();
        
        TestSystem* sys1 = system_manager.GetSystem<TestSystem>();
        TestSystem2* sys2 = system_manager.GetSystem<TestSystem2>();
        
        REQUIRE(sys1 != nullptr);
        REQUIRE(sys2 != nullptr);
    }

    SECTION("Register same system twice") {
        system_manager.RegisterSystem<TestSystem>();
        TestSystem* first = system_manager.GetSystem<TestSystem>();
        
        system_manager.RegisterSystem<TestSystem>();
        TestSystem* second = system_manager.GetSystem<TestSystem>();
        
        REQUIRE(first == second); // Should return same instance
    }
}

TEST_CASE("SystemManager: System Unregistration") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    std::shared_ptr<ComponentManager> component_manager = std::make_shared<ComponentManager>(logging_manager);
    SystemManager system_manager = SystemManager(component_manager, logging_manager);

    SECTION("Unregister system") {
        system_manager.RegisterSystem<TestSystem>();
        system_manager.UnregisterSystem<TestSystem>();
        
        TestSystem* test_system_pointer = system_manager.GetSystem<TestSystem>();
        REQUIRE(test_system_pointer == nullptr);
    }

    SECTION("Unregister unregistered system is safe") {
        REQUIRE_NOTHROW(system_manager.UnregisterSystem<TestSystem>());
    }

    SECTION("Unregister one system doesn't affect others") {
        system_manager.RegisterSystem<TestSystem>();
        system_manager.RegisterSystem<TestSystem2>();
        
        system_manager.UnregisterSystem<TestSystem>();
        
        REQUIRE(system_manager.GetSystem<TestSystem>() == nullptr);
        REQUIRE(system_manager.GetSystem<TestSystem2>() != nullptr);
    }

    SECTION("Can re-register after unregister") {
        system_manager.RegisterSystem<TestSystem>();
        system_manager.UnregisterSystem<TestSystem>();
        system_manager.RegisterSystem<TestSystem>();
        
        TestSystem* sys = system_manager.GetSystem<TestSystem>();
        REQUIRE(sys != nullptr);
    }
}

TEST_CASE("SystemManager: System Signatures") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    std::shared_ptr<ComponentManager> component_manager = std::make_shared<ComponentManager>(logging_manager);
    SystemManager system_manager = SystemManager(component_manager, logging_manager);

    SECTION("Set system signature") {
        system_manager.RegisterSystem<TestSystem>();
        
        Signature sig;
        sig.set(0);
        sig.set(5);
        
        system_manager.SetSignature<TestSystem>(sig);
        
        // If no exception and system is still accessible, it worked
        TestSystem* sys = system_manager.GetSystem<TestSystem>();
        REQUIRE(sys != nullptr);
    }

    SECTION("Set signature for unregistered system is safe") {
        Signature sig;
        sig.set(0);
        
        REQUIRE_NOTHROW(system_manager.SetSignature<TestSystem>(sig));
    }

    SECTION("Different systems can have different signatures") {
        system_manager.RegisterSystem<TestSystem>();
        system_manager.RegisterSystem<TestSystem2>();
        
        Signature sig1;
        sig1.set(0);
        
        Signature sig2;
        sig2.set(1);
        sig2.set(2);
        
        system_manager.SetSignature<TestSystem>(sig1);
        system_manager.SetSignature<TestSystem2>(sig2);
        
        // Both systems should still be accessible
        REQUIRE(system_manager.GetSystem<TestSystem>() != nullptr);
        REQUIRE(system_manager.GetSystem<TestSystem2>() != nullptr);
    }
}

TEST_CASE("SystemManager: Entity Signature Changes") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    std::shared_ptr<ComponentManager> component_manager = std::make_shared<ComponentManager>(logging_manager);
    SystemManager system_manager = SystemManager(component_manager, logging_manager);

    SECTION("Entity signature changed notifies systems") {
        system_manager.RegisterSystem<TestSystem>();
        
        Signature system_sig;
        system_sig.set(0);
        system_manager.SetSignature<TestSystem>(system_sig);
        
        EntityID entity = 0;
        Signature entity_sig;
        entity_sig.set(0);
        
        REQUIRE_NOTHROW(system_manager.EntitySignatureChanged(entity, entity_sig));
    }

    SECTION("Entity signature changed with no matching systems") {
        EntityID entity = 0;
        Signature entity_sig;
        entity_sig.set(0);
        
        REQUIRE_NOTHROW(system_manager.EntitySignatureChanged(entity, entity_sig));
    }

    SECTION("Entity destroyed notification") {
        system_manager.RegisterSystem<TestSystem>();
        EntityID entity = 0;
        
        REQUIRE_NOTHROW(system_manager.EntityDestroyed(entity));
    }

    SECTION("Entity destroyed with no systems") {
        EntityID entity = 0;
        REQUIRE_NOTHROW(system_manager.EntityDestroyed(entity));
    }
}

TEST_CASE("SystemManager: System Lifecycle") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    std::shared_ptr<ComponentManager> component_manager = std::make_shared<ComponentManager>(logging_manager);
    SystemManager system_manager = SystemManager(component_manager, logging_manager);

    SECTION("Dispatch OnStart") {
        system_manager.RegisterSystem<TestSystem2>();
        TestSystem2* sys = system_manager.GetSystem<TestSystem2>();
        
        REQUIRE_FALSE(sys->on_start_called);
        
        system_manager.IterateSystems(GameLoopState::OnStart);
        
        REQUIRE(sys->on_start_called);
    }

    SECTION("Dispatch OnUpdate") {
        system_manager.RegisterSystem<TestSystem2>();
        TestSystem2* sys = system_manager.GetSystem<TestSystem2>();
        
        REQUIRE_FALSE(sys->on_update_called);
        
        system_manager.IterateSystems(GameLoopState::OnUpdate);
        
        REQUIRE(sys->on_update_called);
    }

    SECTION("Dispatch with no systems registered") {
        REQUIRE_NOTHROW(system_manager.IterateSystems(GameLoopState::OnStart));
        REQUIRE_NOTHROW(system_manager.IterateSystems(GameLoopState::OnUpdate));
        REQUIRE_NOTHROW(system_manager.IterateSystems(GameLoopState::OnEvent));
        REQUIRE_NOTHROW(system_manager.IterateSystems(GameLoopState::OnRender));
    }

    SECTION("Multiple systems receive lifecycle events") {
        system_manager.RegisterSystem<TestSystem2>();
        
        // Register a second instance under different name for testing
        system_manager.RegisterSystem<TestSystem>();
        
        system_manager.IterateSystems(GameLoopState::OnStart);
        
        TestSystem2* sys2 = system_manager.GetSystem<TestSystem2>();
        REQUIRE(sys2->on_start_called);
    }
}

TEST_CASE("SystemManager: System Ordering") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    std::shared_ptr<ComponentManager> component_manager = std::make_shared<ComponentManager>(logging_manager);
    SystemManager system_manager = SystemManager(component_manager, logging_manager);

    SECTION("Systems are tracked in registration order") {
        system_manager.RegisterSystem<TestSystem>();
        system_manager.RegisterSystem<TestSystem2>();
        
        // Both should be accessible
        REQUIRE(system_manager.GetSystem<TestSystem>() != nullptr);
        REQUIRE(system_manager.GetSystem<TestSystem2>() != nullptr);
    }

    SECTION("Unregister and re-register maintains order") {
        system_manager.RegisterSystem<TestSystem>();
        system_manager.RegisterSystem<TestSystem2>();
        system_manager.UnregisterSystem<TestSystem>();
        system_manager.RegisterSystem<TestSystem>();
        
        REQUIRE(system_manager.GetSystem<TestSystem>() != nullptr);
        REQUIRE(system_manager.GetSystem<TestSystem2>() != nullptr);
    }
}
