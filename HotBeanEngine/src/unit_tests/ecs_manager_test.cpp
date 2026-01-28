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
#include "test_system.hpp"
#include <HotBeanEngine/application/managers/ecs_manager.hpp>

using namespace HBE::Core;
using namespace HBE::Application::Managers;

TEST_CASE("ECSManager: Create and Destroy Entity") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    ECSManager ecs_manager = ECSManager(logging_manager);

    SECTION("Create entity") {
        ecs_manager.CreateEntity();
        REQUIRE(ecs_manager.EntityCount() == 1);
    }

    SECTION("Create max entities") {
        for (int i = 0; i < MAX_ENTITIES; i++) {
            ecs_manager.CreateEntity();
        }
        REQUIRE(ecs_manager.EntityCount() == MAX_ENTITIES);
    }

    SECTION("Create max entities + 1") {
        for (int i = 0; i < MAX_ENTITIES; i++) {
            ecs_manager.CreateEntity();
        }
        REQUIRE_THROWS_AS(ecs_manager.CreateEntity(), std::overflow_error);
    }

    SECTION("Initialize entity count to 0") { REQUIRE(ecs_manager.EntityCount() == 0); }

    SECTION("Destroy entity") {
        EntityID entity = ecs_manager.CreateEntity();
        ecs_manager.DestroyEntity(entity);
        REQUIRE(ecs_manager.EntityCount() == 0);
    }

    SECTION("Destroy non-existant entity") {
        ecs_manager.DestroyEntity(0);
        REQUIRE(ecs_manager.EntityCount() == 0);
    }
}

TEST_CASE("ECSManager: EntityID has component") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    ECSManager ecs_manager = ECSManager(logging_manager);
    EntityID entity_1 = ecs_manager.CreateEntity();
    EntityID entity_2 = ecs_manager.CreateEntity();
    TestComponent test_component;

    SECTION("Has component: true") {
        ecs_manager.AddComponent<TestComponent>(entity_1, test_component);
        REQUIRE(ecs_manager.HasComponent<TestComponent>(entity_1));
    }

    SECTION("Has component: false") {
        ecs_manager.AddComponent<TestComponent>(entity_2, test_component);
        REQUIRE_FALSE(ecs_manager.HasComponent<TestComponent>(entity_1));
    }
}

TEST_CASE("ECSManager: Component addition and removal") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    ECSManager ecs_manager = ECSManager(logging_manager);
    EntityID entity_1 = ecs_manager.CreateEntity();
    EntityID entity_2 = ecs_manager.CreateEntity();
    TestComponent test_component;

    SECTION("Add component") {
        ecs_manager.AddComponent<TestComponent>(entity_1, test_component);
        REQUIRE(ecs_manager.HasComponent<TestComponent>(entity_1));
    }

    SECTION("Add same component twice") {
        ecs_manager.AddComponent<TestComponent>(entity_1, test_component);
        REQUIRE_THROWS_AS(ecs_manager.AddComponent<TestComponent>(entity_1, test_component), std::runtime_error);
    }

    SECTION("Remove last component associated with an entity") {
        ecs_manager.AddComponent<TestComponent>(entity_1, test_component);
        ecs_manager.RemoveComponent<TestComponent>(entity_1);
        REQUIRE_FALSE(ecs_manager.IsComponentRegistered<TestComponent>());
    }

    SECTION("Remove non-registered component") {
        REQUIRE_THROWS_AS(ecs_manager.RemoveComponent<TestComponent>(entity_1), std::runtime_error);
    }

    SECTION("Remove component") {
        ecs_manager.AddComponent<TestComponent>(entity_1, test_component);
        ecs_manager.AddComponent<TestComponent>(entity_2, test_component);
        ecs_manager.RemoveComponent<TestComponent>(entity_1);
        REQUIRE(ecs_manager.IsComponentRegistered<TestComponent>());
        REQUIRE_FALSE(ecs_manager.HasComponent<TestComponent>(entity_1));
    }

    SECTION("Remove component from same entity twice") {
        ecs_manager.AddComponent<TestComponent>(entity_1, test_component);
        ecs_manager.AddComponent<TestComponent>(entity_2, test_component);
        ecs_manager.RemoveComponent<TestComponent>(entity_1);
        REQUIRE_NOTHROW(ecs_manager.RemoveComponent<TestComponent>(entity_1));
    }
}