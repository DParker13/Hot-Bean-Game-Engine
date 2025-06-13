#include "../all_managers.hpp"
#include "test_component.hpp"
#include <catch2/catch_all.hpp>

TEST_CASE("ComponentManager: Component addition and removal") {
    Core::Managers::ComponentManager component_manager;
    Core::Managers::EntityManager entity_manager;
    Entity test_entity = entity_manager.CreateEntity();
    TestComponent test_component;

    // SECTION("Has component") {
    //     bool has_component = component_manager.HasComponent<TestComponent>(test_entity);
    //     component_manager.GetComponentData<TestComponent>(test_entity);
    //     REQUIRE(component_manager.HasComponent<TestComponent>(test_entity));
    // }

    SECTION("Add component") {
        component_manager.AddComponent<TestComponent>(test_entity, test_component);
        REQUIRE(component_manager.HasComponent<TestComponent>(test_entity));
    }

    SECTION("Remove component") {
        component_manager.AddComponent<TestComponent>(test_entity, test_component);
        component_manager.RemoveComponent<TestComponent>(test_entity);
        REQUIRE(component_manager.HasComponent<TestComponent>(test_entity));
    }
}