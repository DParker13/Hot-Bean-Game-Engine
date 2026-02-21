/**
 * @file entity_manager_test.cpp
 * @author Daniel Parker (DParker13)
 * @brief Unit tests for the EntityManager class.
 * Tests entity creation, destruction, signature management, and ID recycling.
 * @version 0.1
 * @date 2025-07-06
 *
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/application/managers/entity_manager.hpp>
#include <catch2/catch_all.hpp>

using namespace HBE::Core;
using namespace HBE::Application::Managers;

TEST_CASE("EntityManager: Create and Destroy Entity") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    EntityManager entity_manager = EntityManager(logging_manager);

    SECTION("Initialize entity count to 0") { 
        REQUIRE(entity_manager.EntityCount() == 0); 
    }

    SECTION("Create single entity") {
        EntityID entity = entity_manager.CreateEntity();
        REQUIRE(entity_manager.EntityCount() == 1);
        REQUIRE(entity == 0); // First entity should have ID 0
    }

    SECTION("Create multiple entities") {
        EntityID e1 = entity_manager.CreateEntity();
        EntityID e2 = entity_manager.CreateEntity();
        EntityID e3 = entity_manager.CreateEntity();
        REQUIRE(entity_manager.EntityCount() == 3);
        REQUIRE(e1 == 0);
        REQUIRE(e2 == 1);
        REQUIRE(e3 == 2);
    }

    SECTION("Create max entities") {
        for (int i = 0; i < MAX_ENTITIES; i++) {
            entity_manager.CreateEntity();
        }
        REQUIRE(entity_manager.EntityCount() == MAX_ENTITIES);
    }

    SECTION("Create max entities + 1 returns MAX_ENTITIES") {
        for (int i = 0; i < MAX_ENTITIES; i++) {
            entity_manager.CreateEntity();
        }
        EntityID result = entity_manager.CreateEntity();
        REQUIRE(result == MAX_ENTITIES);
        REQUIRE(entity_manager.EntityCount() == MAX_ENTITIES);
    }

    SECTION("Destroy entity") {
        EntityID entity = entity_manager.CreateEntity();
        entity_manager.DestroyEntity(entity);
        REQUIRE(entity_manager.EntityCount() == 0);
    }

    SECTION("Destroy non-existent entity (ID 0)") {
        entity_manager.DestroyEntity(0);
        REQUIRE(entity_manager.EntityCount() == 0);
    }

    SECTION("Destroy out of range entity (negative)") {
        entity_manager.DestroyEntity(-1);
        REQUIRE(entity_manager.EntityCount() == 0);
    }

    SECTION("Destroy out of range entity (too large)") {
        entity_manager.DestroyEntity(MAX_ENTITIES + 100);
        REQUIRE(entity_manager.EntityCount() == 0);
    }

    SECTION("Destroy entity twice") {
        EntityID entity = entity_manager.CreateEntity();
        entity_manager.DestroyEntity(entity);
        entity_manager.DestroyEntity(entity); // Should not crash
        REQUIRE(entity_manager.EntityCount() == 0);
    }
}

TEST_CASE("EntityManager: Entity ID Recycling") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    EntityManager entity_manager = EntityManager(logging_manager);

    SECTION("Recycle single entity ID after all IDs exhausted") {
        // Create all entities to exhaust the queue
        for (int i = 0; i < MAX_ENTITIES; i++) {
            entity_manager.CreateEntity();
        }
        
        // Destroy entity 0
        entity_manager.DestroyEntity(0);
        
        // Next create should reuse ID 0
        EntityID recycled = entity_manager.CreateEntity();
        REQUIRE(recycled == 0);
    }

    SECTION("FIFO recycling order") {
        // Exhaust all IDs
        for (int i = 0; i < MAX_ENTITIES; i++) {
            entity_manager.CreateEntity();
        }
        
        // Destroy entities 5, 3, 7 in that order
        entity_manager.DestroyEntity(5);
        entity_manager.DestroyEntity(3);
        entity_manager.DestroyEntity(7);
        
        // They should be recycled in FIFO order: 5, 3, 7
        EntityID r1 = entity_manager.CreateEntity();
        EntityID r2 = entity_manager.CreateEntity();
        EntityID r3 = entity_manager.CreateEntity();
        
        REQUIRE(r1 == 5);
        REQUIRE(r2 == 3);
        REQUIRE(r3 == 7);
        REQUIRE(entity_manager.EntityCount() == MAX_ENTITIES);
    }

    SECTION("Recycling with partial queue") {
        // Create only 3 entities (queue has 0,1,2 used, 3+ available)
        EntityID e1 = entity_manager.CreateEntity(); // ID 0
        EntityID e2 = entity_manager.CreateEntity(); // ID 1
        EntityID e3 = entity_manager.CreateEntity(); // ID 2
        
        REQUIRE(e1 == 0);
        REQUIRE(e2 == 1);
        REQUIRE(e3 == 2);
        
        // Destroy middle entity (ID 1) - goes to back of queue
        entity_manager.DestroyEntity(e2);
        
        // Next create uses front of queue (ID 3, not recycled 1)
        EntityID e4 = entity_manager.CreateEntity();
        REQUIRE(e4 == 3);
        REQUIRE(entity_manager.EntityCount() == 3);
    }

    SECTION("Recycled IDs appear after initial queue exhausted") {
        // Use first 5 IDs
        for (int i = 0; i < 5; i++) {
            entity_manager.CreateEntity();
        }
        
        // Destroy IDs 1 and 3 (they go to back of queue)
        entity_manager.DestroyEntity(1);
        entity_manager.DestroyEntity(3);
        
        // Next creates use remaining initial queue: 5, 6, 7, ...
        EntityID e1 = entity_manager.CreateEntity();
        EntityID e2 = entity_manager.CreateEntity();
        REQUIRE(e1 == 5);
        REQUIRE(e2 == 6);
        
        // Entity count should be 5 (0,2,4,5,6 alive)
        REQUIRE(entity_manager.EntityCount() == 5);
    }
}

TEST_CASE("EntityManager: Entity Signature Management") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    EntityManager entity_manager = EntityManager(logging_manager);

    SECTION("Get default signature") {
        EntityID entity = entity_manager.CreateEntity();
        Signature sig = entity_manager.GetSignature(entity);
        REQUIRE(sig.none()); // All bits should be 0
    }

    SECTION("Set and get signature") {
        EntityID entity = entity_manager.CreateEntity();
        ComponentID comp_id = 5;
        
        Signature sig = entity_manager.SetSignature(entity, comp_id);
        REQUIRE(sig.test(comp_id));
        
        Signature retrieved_sig = entity_manager.GetSignature(entity);
        REQUIRE(retrieved_sig.test(comp_id));
    }

    SECTION("Set multiple signature bits") {
        EntityID entity = entity_manager.CreateEntity();
        
        entity_manager.SetSignature(entity, 0);
        entity_manager.SetSignature(entity, 5);
        entity_manager.SetSignature(entity, 10);
        
        Signature sig = entity_manager.GetSignature(entity);
        REQUIRE(sig.test(0));
        REQUIRE(sig.test(5));
        REQUIRE(sig.test(10));
        REQUIRE_FALSE(sig.test(1));
    }

    SECTION("Clear signature") {
        EntityID entity = entity_manager.CreateEntity();
        
        entity_manager.SetSignature(entity, 3);
        entity_manager.SetSignature(entity, 7);
        entity_manager.SetSignature(entity, 3, false); // Clear bit 3
        
        Signature sig = entity_manager.GetSignature(entity);
        REQUIRE_FALSE(sig.test(3));
        REQUIRE(sig.test(7));
    }

    SECTION("Clear all signature bits") {
        EntityID entity = entity_manager.CreateEntity();
        
        entity_manager.SetSignature(entity, 1);
        entity_manager.SetSignature(entity, 2);
        entity_manager.SetSignature(entity, 1, false); // Clear bit 1
        entity_manager.SetSignature(entity, 2, false); // Clear bit 2
        
        Signature sig = entity_manager.GetSignature(entity);
        REQUIRE(sig.none());
    }

    SECTION("Signature persists across other operations") {
        EntityID e1 = entity_manager.CreateEntity();
        EntityID e2 = entity_manager.CreateEntity();
        
        entity_manager.SetSignature(e1, 3);
        entity_manager.SetSignature(e2, 5);
        
        // Signatures should remain independent
        Signature sig1 = entity_manager.GetSignature(e1);
        Signature sig2 = entity_manager.GetSignature(e2);
        
        REQUIRE(sig1.test(3));
        REQUIRE_FALSE(sig1.test(5));
        REQUIRE(sig2.test(5));
        REQUIRE_FALSE(sig2.test(3));
    }
}

TEST_CASE("EntityManager: Destroy All Entities") {
    std::shared_ptr<LoggingManager> logging_manager = std::make_shared<LoggingManager>();
    EntityManager entity_manager = EntityManager(logging_manager);

    SECTION("Destroy all with no entities") {
        entity_manager.DestroyAllEntities();
        REQUIRE(entity_manager.EntityCount() == 0);
    }

    SECTION("Destroy all with some entities") {
        entity_manager.CreateEntity();
        entity_manager.CreateEntity();
        entity_manager.CreateEntity();
        
        entity_manager.DestroyAllEntities();
        REQUIRE(entity_manager.EntityCount() == 0);
    }

    SECTION("Create entities after destroy all") {
        entity_manager.CreateEntity();
        entity_manager.CreateEntity();
        entity_manager.DestroyAllEntities();
        
        EntityID new_entity = entity_manager.CreateEntity();
        REQUIRE(new_entity == 0);
        REQUIRE(entity_manager.EntityCount() == 1);
    }

    SECTION("Signatures cleared after destroy all") {
        EntityID entity = entity_manager.CreateEntity();
        entity_manager.SetSignature(entity, 3);
        
        entity_manager.DestroyAllEntities();
        
        EntityID new_entity = entity_manager.CreateEntity();
        Signature sig = entity_manager.GetSignature(new_entity);
        REQUIRE(sig.none());
    }
}
