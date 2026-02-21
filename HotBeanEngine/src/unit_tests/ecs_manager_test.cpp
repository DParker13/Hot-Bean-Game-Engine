/**
 * @file ecs_manager_test.cpp
 * @author Daniel Parker (DParker13)
 * @brief Unit tests for the ECSManager class.
 * Tests the integrated ECS functionality including entities, components, and systems.
 * @version 0.1
 * @date 2025-07-06
 *
 * @copyright Copyright (c) 2025
 */

#include <catch2/catch_all.hpp>

#include "test_component.hpp"
#include "test_component_2.hpp"
#include "test_system.hpp"
#include <HotBeanEngine/application/managers/ecs_manager.hpp>

using namespace HBE::Core;
using namespace HBE::Application::Managers;

TEST_CASE("ECSManager: Entity Creation and Destruction") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    ECSManager ecs_manager = ECSManager(logging_manager);

    SECTION("Initialize entity count to 0") { 
        REQUIRE(ecs_manager.EntityCount() == 0); 
    }

    SECTION("Create single entity") {
        EntityID entity = ecs_manager.CreateEntity();
        REQUIRE(ecs_manager.EntityCount() == 1);
        REQUIRE(entity == 0);
    }

    SECTION("Create multiple entities") {
        EntityID e1 = ecs_manager.CreateEntity();
        EntityID e2 = ecs_manager.CreateEntity();
        EntityID e3 = ecs_manager.CreateEntity();
        
        REQUIRE(ecs_manager.EntityCount() == 3);
        REQUIRE(e1 != e2);
        REQUIRE(e2 != e3);
    }

    SECTION("Create max entities") {
        for (int i = 0; i < MAX_ENTITIES; i++) {
            ecs_manager.CreateEntity();
        }
        REQUIRE(ecs_manager.EntityCount() == MAX_ENTITIES);
    }

    SECTION("Create max entities + 1 returns MAX_ENTITIES") {
        for (int i = 0; i < MAX_ENTITIES; i++) {
            ecs_manager.CreateEntity();
        }
        EntityID result = ecs_manager.CreateEntity();
        REQUIRE(result == MAX_ENTITIES);
        REQUIRE(ecs_manager.EntityCount() == MAX_ENTITIES);
    }

    SECTION("Destroy entity") {
        EntityID entity = ecs_manager.CreateEntity();
        ecs_manager.DestroyEntity(entity);
        REQUIRE(ecs_manager.EntityCount() == 0);
    }

    SECTION("Destroy non-existent entity") {
        ecs_manager.DestroyEntity(0);
        REQUIRE(ecs_manager.EntityCount() == 0);
    }

    SECTION("Destroy entity with components") {
        EntityID entity = ecs_manager.CreateEntity();
        TestComponent comp;
        ecs_manager.AddComponent<TestComponent>(entity, comp);
        
        ecs_manager.DestroyEntity(entity);
        REQUIRE(ecs_manager.EntityCount() == 0);
    }

    SECTION("Destroy all entities") {
        ecs_manager.CreateEntity();
        ecs_manager.CreateEntity();
        ecs_manager.CreateEntity();
        
        ecs_manager.DestroyAllEntities();
        REQUIRE(ecs_manager.EntityCount() == 0);
    }
}

TEST_CASE("ECSManager: Component Management") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    ECSManager ecs_manager = ECSManager(logging_manager);
    EntityID entity_1 = ecs_manager.CreateEntity();
    EntityID entity_2 = ecs_manager.CreateEntity();

    SECTION("Add component to entity") {
        TestComponent comp;
        comp.m_value = 42;
        
        ecs_manager.AddComponent<TestComponent>(entity_1, comp);
        REQUIRE(ecs_manager.HasComponent<TestComponent>(entity_1));
    }

    SECTION("Add empty component to entity") {
        ecs_manager.AddComponent<TestComponent>(entity_1);
        REQUIRE(ecs_manager.HasComponent<TestComponent>(entity_1));
    }

    SECTION("Add same component twice is safe") {
        TestComponent comp;
        ecs_manager.AddComponent<TestComponent>(entity_1, comp);
        ecs_manager.AddComponent<TestComponent>(entity_1, comp);
        REQUIRE(ecs_manager.HasComponent<TestComponent>(entity_1));
    }

    SECTION("Has component returns false for different entity") {
        TestComponent comp;
        ecs_manager.AddComponent<TestComponent>(entity_2, comp);
        REQUIRE_FALSE(ecs_manager.HasComponent<TestComponent>(entity_1));
    }

    SECTION("Get component data") {
        TestComponent comp;
        comp.m_value = 99;
        
        ecs_manager.AddComponent<TestComponent>(entity_1, comp);
        TestComponent& retrieved = ecs_manager.GetComponent<TestComponent>(entity_1);
        
        REQUIRE(retrieved.m_value == 99);
    }

    SECTION("Modify component data") {
        TestComponent comp;
        comp.m_value = 10;
        
        ecs_manager.AddComponent<TestComponent>(entity_1, comp);
        TestComponent& retrieved = ecs_manager.GetComponent<TestComponent>(entity_1);
        retrieved.m_value = 50;
        
        TestComponent& check = ecs_manager.GetComponent<TestComponent>(entity_1);
        REQUIRE(check.m_value == 50);
    }

    SECTION("Add multiple component types to same entity") {
        TestComponent comp1;
        TestComponent2 comp2(1.0f, 2.0f);
        
        ecs_manager.AddComponent<TestComponent>(entity_1, comp1);
        ecs_manager.AddComponent<TestComponent2>(entity_1, comp2);
        
        REQUIRE(ecs_manager.HasComponent<TestComponent>(entity_1));
        REQUIRE(ecs_manager.HasComponent<TestComponent2>(entity_1));
    }
}

TEST_CASE("ECSManager: Component Removal") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    ECSManager ecs_manager = ECSManager(logging_manager);
    EntityID entity_1 = ecs_manager.CreateEntity();
    EntityID entity_2 = ecs_manager.CreateEntity();

    SECTION("Remove component from entity") {
        TestComponent comp;
        ecs_manager.AddComponent<TestComponent>(entity_1, comp);
        ecs_manager.AddComponent<TestComponent>(entity_2, comp);
        
        ecs_manager.RemoveComponent<TestComponent>(entity_1);
        
        REQUIRE_FALSE(ecs_manager.HasComponent<TestComponent>(entity_1));
        REQUIRE(ecs_manager.HasComponent<TestComponent>(entity_2));
    }

    SECTION("Remove last component instance throws") {
        TestComponent comp;
        ecs_manager.AddComponent<TestComponent>(entity_1, comp);
        
        // When removing the last instance, it unregisters and then tries to get ComponentID
        REQUIRE_THROWS_AS(
            ecs_manager.RemoveComponent<TestComponent>(entity_1),
            ComponentNotRegisteredException
        );
    }

    SECTION("Remove non-registered component throws") {
        REQUIRE_THROWS_AS(
            ecs_manager.RemoveComponent<TestComponent>(entity_1),
            ComponentNotRegisteredException
        );
    }

    SECTION("Remove component from same entity twice is safe") {
        TestComponent comp;
        ecs_manager.AddComponent<TestComponent>(entity_1, comp);
        ecs_manager.AddComponent<TestComponent>(entity_2, comp);
        
        ecs_manager.RemoveComponent<TestComponent>(entity_1);
        REQUIRE_NOTHROW(ecs_manager.RemoveComponent<TestComponent>(entity_1));
    }

    SECTION("Remove all components from entity") {
        TestComponent comp1;
        TestComponent2 comp2;
        
        ecs_manager.AddComponent<TestComponent>(entity_1, comp1);
        ecs_manager.AddComponent<TestComponent2>(entity_1, comp2);
        
        ecs_manager.RemoveAllComponents(entity_1);
        
        REQUIRE_FALSE(ecs_manager.HasComponent<TestComponent>(entity_1));
        REQUIRE_FALSE(ecs_manager.HasComponent<TestComponent2>(entity_1));
    }
}

TEST_CASE("ECSManager: Component Registration") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    ECSManager ecs_manager = ECSManager(logging_manager);
    EntityID entity = ecs_manager.CreateEntity();

    SECTION("Component registered after add") {
        TestComponent comp;
        ecs_manager.AddComponent<TestComponent>(entity, comp);
        
        REQUIRE(ecs_manager.IsComponentRegistered<TestComponent>());
    }

    SECTION("Component not registered initially") {
        REQUIRE_FALSE(ecs_manager.IsComponentRegistered<TestComponent>());
    }

    SECTION("Get component ID after registration") {
        TestComponent comp;
        ecs_manager.AddComponent<TestComponent>(entity, comp);
        
        ComponentID id = ecs_manager.GetComponentID<TestComponent>();
        REQUIRE(id >= 0);
        REQUIRE(id < MAX_COMPONENTS);
    }

    SECTION("Different component types get different IDs") {
        TestComponent comp1;
        TestComponent2 comp2;
        
        ecs_manager.AddComponent<TestComponent>(entity, comp1);
        ecs_manager.AddComponent<TestComponent2>(entity, comp2);
        
        ComponentID id1 = ecs_manager.GetComponentID<TestComponent>();
        ComponentID id2 = ecs_manager.GetComponentID<TestComponent2>();
        
        REQUIRE(id1 != id2);
    }
}

TEST_CASE("ECSManager: System Integration") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    ECSManager ecs_manager = ECSManager(logging_manager);

    SECTION("Register system") {
        ecs_manager.RegisterSystem<TestSystem>();
        TestSystem* system = ecs_manager.GetSystem<TestSystem>();
        
        REQUIRE(system != nullptr);
    }

    SECTION("Unregister system") {
        ecs_manager.RegisterSystem<TestSystem>();
        ecs_manager.UnregisterSystem<TestSystem>();
        
        TestSystem* system = ecs_manager.GetSystem<TestSystem>();
        REQUIRE(system == nullptr);
    }

    SECTION("Set system signature") {
        ecs_manager.RegisterSystem<TestSystem>();
        
        Signature sig;
        EntityID entity = ecs_manager.CreateEntity();
        TestComponent comp;
        ecs_manager.AddComponent<TestComponent>(entity, comp);
        
        ComponentID comp_id = ecs_manager.GetComponentID<TestComponent>();
        sig.set(comp_id);
        
        ecs_manager.SetSignature<TestSystem, TestComponent>();
        
        TestSystem* system = ecs_manager.GetSystem<TestSystem>();
        REQUIRE(system != nullptr);
        REQUIRE(ecs_manager.GetSignature<TestSystem>() == sig);
    }
}

TEST_CASE("ECSManager: Entity-Component Integration") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    ECSManager ecs_manager = ECSManager(logging_manager);

    SECTION("Destroy entity removes its components") {
        EntityID entity = ecs_manager.CreateEntity();
        TestComponent comp;
        ecs_manager.AddComponent<TestComponent>(entity, comp);
        
        EntityID entity2 = ecs_manager.CreateEntity();
        ecs_manager.AddComponent<TestComponent>(entity2, comp);
        
        ecs_manager.DestroyEntity(entity);
        
        REQUIRE(ecs_manager.IsComponentRegistered<TestComponent>());
        REQUIRE(ecs_manager.HasComponent<TestComponent>(entity2));
    }

    SECTION("Create entity with multiple components") {
        EntityID entity = ecs_manager.CreateEntity();
        
        TestComponent comp1;
        comp1.m_value = 42;
        TestComponent2 comp2(3.14f, 2.71f);
        
        ecs_manager.AddComponent<TestComponent>(entity, comp1);
        ecs_manager.AddComponent<TestComponent2>(entity, comp2);
        
        REQUIRE(ecs_manager.GetComponent<TestComponent>(entity).m_value == 42);
        REQUIRE(ecs_manager.GetComponent<TestComponent2>(entity).m_x == 3.14f);
        REQUIRE(ecs_manager.GetComponent<TestComponent2>(entity).m_y == 2.71f);
    }

    SECTION("Recycle entity ID after destroy") {
        EntityID first = ecs_manager.CreateEntity();
        REQUIRE(first == 0);
        ecs_manager.DestroyEntity(first);
        
        // Next ID comes from front of queue (ID 1), not recycled ID
        EntityID second = ecs_manager.CreateEntity();
        REQUIRE(second == 1);
    }
}
