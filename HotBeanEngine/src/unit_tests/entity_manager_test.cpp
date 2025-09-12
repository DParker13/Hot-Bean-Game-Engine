#include "../../include/HotBeanEngine.hpp"
#include <catch2/catch_all.hpp>

using namespace HBE::Core;
using namespace HBE::Managers;

TEST_CASE("EntityManager: Create and Destroy Entity") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    EntityManager entity_manager = EntityManager(logging_manager);

    SECTION("Create entity") {
        entity_manager.CreateEntity();
        REQUIRE(entity_manager.EntityCount() == 1);
    }

    SECTION("Create max entities") {
        for (int i = 0; i < MAX_ENTITIES; i++) {
            entity_manager.CreateEntity();
        }
        REQUIRE(entity_manager.EntityCount() == MAX_ENTITIES);
    }

    SECTION("Create max entities + 1") {
        for (int i = 0; i < MAX_ENTITIES; i++) {
            entity_manager.CreateEntity();
        }
        REQUIRE_THROWS_AS(entity_manager.CreateEntity(), std::overflow_error);
    }

    SECTION("Initialize entity count to 0") {
        REQUIRE(entity_manager.EntityCount() == 0);
    }

    SECTION("Destroy entity") {
        Entity entity = entity_manager.CreateEntity();
        entity_manager.DestroyEntity(entity);
        REQUIRE(entity_manager.EntityCount() == 0);
    }

    SECTION("Destroy non-existant entity") {
        entity_manager.DestroyEntity(0);
        REQUIRE(entity_manager.EntityCount() == 0);
    }
}