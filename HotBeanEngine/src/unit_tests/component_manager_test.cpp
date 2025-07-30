#include "../../include/HotBeanEngine.hpp"
#include "test_component.hpp"
#include <catch2/catch_all.hpp>

using namespace Core::ECS;
using namespace Core::Managers;

TEST_CASE("ComponentManager: Entity has component") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    ComponentManager component_manager = ComponentManager(logging_manager);
    EntityManager entity_manager = EntityManager(logging_manager);
    Entity entity_1 = entity_manager.CreateEntity();
    Entity entity_2 = entity_manager.CreateEntity();
    TestComponent test_component;

    SECTION("Has component: true") {
        component_manager.AddComponent<TestComponent>(entity_1, test_component);
        REQUIRE(component_manager.HasComponent<TestComponent>(entity_1));
    }

    SECTION("Has component: false") {
        component_manager.AddComponent<TestComponent>(entity_2, test_component);
        REQUIRE_FALSE(component_manager.HasComponent<TestComponent>(entity_1));
    }
}

TEST_CASE("ComponentManager: Component addition and removal") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    ComponentManager component_manager = ComponentManager(logging_manager);
    EntityManager entity_manager = EntityManager(logging_manager);
    Entity entity_1 = entity_manager.CreateEntity();
    Entity entity_2 = entity_manager.CreateEntity();
    TestComponent test_component;

    SECTION("Add component") {
        component_manager.AddComponent<TestComponent>(entity_1, test_component);
        REQUIRE(component_manager.HasComponent<TestComponent>(entity_1));
    }

    SECTION("Add same component twice") {
        component_manager.AddComponent<TestComponent>(entity_1, test_component);
        REQUIRE_THROWS_AS(component_manager.AddComponent<TestComponent>(entity_1, test_component), std::runtime_error);
    }

    SECTION("Remove last component associated with an entity") {
        component_manager.AddComponent<TestComponent>(entity_1, test_component);
        component_manager.RemoveComponent<TestComponent>(entity_1);
        REQUIRE_FALSE(component_manager.IsComponentRegistered<TestComponent>());
    }

    SECTION("Remove non-registered component") {
        REQUIRE_THROWS_AS(component_manager.RemoveComponent<TestComponent>(entity_1), std::runtime_error);
    }

    SECTION("Remove component") {
        component_manager.AddComponent<TestComponent>(entity_1, test_component);
        component_manager.AddComponent<TestComponent>(entity_2, test_component);
        component_manager.RemoveComponent<TestComponent>(entity_1);
        REQUIRE(component_manager.IsComponentRegistered<TestComponent>());
        REQUIRE_FALSE(component_manager.HasComponent<TestComponent>(entity_1));
    }

    SECTION("Remove component from same entity twice") {
        component_manager.AddComponent<TestComponent>(entity_1, test_component);
        component_manager.AddComponent<TestComponent>(entity_2, test_component);
        component_manager.RemoveComponent<TestComponent>(entity_1);
        REQUIRE_NOTHROW(component_manager.RemoveComponent<TestComponent>(entity_1));
    }
}