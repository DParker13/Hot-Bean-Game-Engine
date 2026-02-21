/**
 * @file component_manager_test.cpp
 * @author Daniel Parker (DParker13)
 * @brief Unit tests for the ComponentManager class.
 * Tests component addition, removal, retrieval, and validation operations.
 * @version 0.1
 * @date 2025-06-19
 *
 * @copyright Copyright (c) 2025
 */

#include <catch2/catch_all.hpp>

#include "test_component.hpp"
#include "test_component_2.hpp"
#include <HotBeanEngine/application/managers/component_manager.hpp>
#include <HotBeanEngine/application/managers/entity_manager.hpp>

using namespace HBE::Core;
using namespace HBE::Application::Managers;

TEST_CASE("ComponentManager: Component Addition") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    ComponentManager component_manager = ComponentManager(logging_manager);
    EntityManager entity_manager = EntityManager(logging_manager);
    EntityID entity = entity_manager.CreateEntity();

    SECTION("Add component with data") {
        TestComponent test_component;
        test_component.m_value = 42;
        
        component_manager.AddComponent<TestComponent>(entity, test_component);
        REQUIRE(component_manager.HasComponent<TestComponent>(entity));
        REQUIRE(component_manager.IsComponentRegistered<TestComponent>());
    }

    SECTION("Add empty component") {
        component_manager.AddComponent<TestComponent>(entity);
        REQUIRE(component_manager.HasComponent<TestComponent>(entity));
    }

    SECTION("Add same component twice returns same ID") {
        TestComponent comp1;
        comp1.m_value = 10;
        
        ComponentID first_add = component_manager.AddComponent<TestComponent>(entity, comp1);
        ComponentID second_add = component_manager.AddComponent<TestComponent>(entity, comp1);
        
        REQUIRE(first_add == second_add);
        REQUIRE(component_manager.HasComponent<TestComponent>(entity));
    }

    SECTION("Add multiple component types to same entity") {
        TestComponent comp1;
        TestComponent2 comp2(1.0f, 2.0f);
        
        component_manager.AddComponent<TestComponent>(entity, comp1);
        component_manager.AddComponent<TestComponent2>(entity, comp2);
        
        REQUIRE(component_manager.HasComponent<TestComponent>(entity));
        REQUIRE(component_manager.HasComponent<TestComponent2>(entity));
    }

    SECTION("Add same component type to multiple entities") {
        EntityID entity2 = entity_manager.CreateEntity();
        TestComponent comp;
        comp.m_value = 100;
        
        component_manager.AddComponent<TestComponent>(entity, comp);
        component_manager.AddComponent<TestComponent>(entity2, comp);
        
        REQUIRE(component_manager.HasComponent<TestComponent>(entity));
        REQUIRE(component_manager.HasComponent<TestComponent>(entity2));
    }
}

TEST_CASE("ComponentManager: Component Removal") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    ComponentManager component_manager = ComponentManager(logging_manager);
    EntityManager entity_manager = EntityManager(logging_manager);
    EntityID entity_1 = entity_manager.CreateEntity();
    EntityID entity_2 = entity_manager.CreateEntity();
    TestComponent test_component;

    SECTION("Remove component from entity") {
        component_manager.AddComponent<TestComponent>(entity_1, test_component);
        component_manager.AddComponent<TestComponent>(entity_2, test_component);
        
        component_manager.RemoveComponent<TestComponent>(entity_1);
        
        REQUIRE_FALSE(component_manager.HasComponent<TestComponent>(entity_1));
        REQUIRE(component_manager.HasComponent<TestComponent>(entity_2));
        REQUIRE(component_manager.IsComponentRegistered<TestComponent>());
    }

    SECTION("Remove last component unregisters type") {
        component_manager.AddComponent<TestComponent>(entity_1, test_component);
        component_manager.RemoveComponent<TestComponent>(entity_1);
        
        REQUIRE_FALSE(component_manager.IsComponentRegistered<TestComponent>());
        REQUIRE_FALSE(component_manager.HasComponent<TestComponent>(entity_1));
    }

    SECTION("Remove component from same entity twice is safe") {
        component_manager.AddComponent<TestComponent>(entity_1, test_component);
        component_manager.AddComponent<TestComponent>(entity_2, test_component);
        
        component_manager.RemoveComponent<TestComponent>(entity_1);
        component_manager.RemoveComponent<TestComponent>(entity_1); // Should not crash
        
        REQUIRE(component_manager.IsComponentRegistered<TestComponent>());
        REQUIRE(component_manager.HasComponent<TestComponent>(entity_2));
    }

    SECTION("Remove non-registered component throws") {
        REQUIRE_THROWS_AS(
            component_manager.RemoveComponent<TestComponent>(entity_1), 
            ComponentNotRegisteredException
        );
    }

    SECTION("Remove component from entity without it is safe") {
        component_manager.AddComponent<TestComponent>(entity_1, test_component);
        
        REQUIRE_NOTHROW(component_manager.RemoveComponent<TestComponent>(entity_2));
    }
}

TEST_CASE("ComponentManager: Component Retrieval") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    ComponentManager component_manager = ComponentManager(logging_manager);
    EntityManager entity_manager = EntityManager(logging_manager);
    EntityID entity = entity_manager.CreateEntity();

    SECTION("Get component data by reference") {
        TestComponent test_component;
        test_component.m_value = 99;
        
        component_manager.AddComponent<TestComponent>(entity, test_component);
        TestComponent& retrieved = component_manager.GetComponentData<TestComponent>(entity);
        
        REQUIRE(retrieved.m_value == 99);
    }

    SECTION("Modify component data through reference") {
        TestComponent test_component;
        test_component.m_value = 10;
        
        component_manager.AddComponent<TestComponent>(entity, test_component);
        TestComponent& retrieved = component_manager.GetComponentData<TestComponent>(entity);
        retrieved.m_value = 50;
        
        TestComponent& check = component_manager.GetComponentData<TestComponent>(entity);
        REQUIRE(check.m_value == 50);
    }

    SECTION("Get component by ComponentID") {
        TestComponent test_component;
        test_component.m_value = 123;
        
        ComponentID comp_id = component_manager.AddComponent<TestComponent>(entity, test_component);
        IComponent* comp_ptr = component_manager.GetComponent(entity, comp_id);
        
        REQUIRE(comp_ptr != nullptr);
        TestComponent* typed_ptr = dynamic_cast<TestComponent*>(comp_ptr);
        REQUIRE(typed_ptr != nullptr);
        REQUIRE(typed_ptr->m_value == 123);
    }
}

TEST_CASE("ComponentManager: Component Type Queries") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    ComponentManager component_manager = ComponentManager(logging_manager);
    EntityManager entity_manager = EntityManager(logging_manager);
    EntityID entity_1 = entity_manager.CreateEntity();
    EntityID entity_2 = entity_manager.CreateEntity();

    SECTION("Has component returns true") {
        TestComponent comp;
        component_manager.AddComponent<TestComponent>(entity_1, comp);
        
        REQUIRE(component_manager.HasComponent<TestComponent>(entity_1));
    }

    SECTION("Has component returns false for different entity") {
        TestComponent comp;
        component_manager.AddComponent<TestComponent>(entity_2, comp);
        
        REQUIRE_FALSE(component_manager.HasComponent<TestComponent>(entity_1));
    }

    SECTION("Is component registered after add") {
        TestComponent comp;
        component_manager.AddComponent<TestComponent>(entity_1, comp);
        
        REQUIRE(component_manager.IsComponentRegistered<TestComponent>());
    }

    SECTION("Is component not registered initially") {
        REQUIRE_FALSE(component_manager.IsComponentRegistered<TestComponent>());
    }

    SECTION("Get component ID after registration") {
        TestComponent comp;
        ComponentID id = component_manager.AddComponent<TestComponent>(entity_1, comp);
        ComponentID retrieved_id = component_manager.GetComponentID<TestComponent>();
        
        REQUIRE(id == retrieved_id);
    }

    SECTION("Get component ID throws if not registered") {
        REQUIRE_THROWS_AS(
            component_manager.GetComponentID<TestComponent>(),
            ComponentNotRegisteredException
        );
    }
}

TEST_CASE("ComponentManager: Multiple Component Types") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    ComponentManager component_manager = ComponentManager(logging_manager);
    EntityManager entity_manager = EntityManager(logging_manager);
    EntityID entity = entity_manager.CreateEntity();

    SECTION("Track multiple registered component types") {
        TestComponent comp1;
        TestComponent2 comp2(5.0f, 10.0f);
        
        component_manager.AddComponent<TestComponent>(entity, comp1);
        component_manager.AddComponent<TestComponent2>(entity, comp2);
        
        REQUIRE(component_manager.IsComponentRegistered<TestComponent>());
        REQUIRE(component_manager.IsComponentRegistered<TestComponent2>());
    }

    SECTION("Get different component IDs for different types") {
        TestComponent comp1;
        TestComponent2 comp2;
        
        ComponentID id1 = component_manager.AddComponent<TestComponent>(entity, comp1);
        ComponentID id2 = component_manager.AddComponent<TestComponent2>(entity, comp2);
        
        REQUIRE(id1 != id2);
    }

    SECTION("Remove one type doesn't affect other") {
        EntityID entity2 = entity_manager.CreateEntity();
        TestComponent comp1;
        TestComponent2 comp2;
        
        component_manager.AddComponent<TestComponent>(entity, comp1);
        component_manager.AddComponent<TestComponent2>(entity, comp2);
        component_manager.RemoveComponent<TestComponent>(entity);
        
        REQUIRE_FALSE(component_manager.HasComponent<TestComponent>(entity));
        REQUIRE(component_manager.HasComponent<TestComponent2>(entity));
        REQUIRE(component_manager.IsComponentRegistered<TestComponent2>());
    }
}
