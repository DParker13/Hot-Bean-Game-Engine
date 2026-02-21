/**
 * @file sparse_set_test.cpp
 * @author Daniel Parker (DParker13)
 * @brief Unit tests for the sparse set data structure.
 * Tests insertion, deletion, lookup, and iteration operations.
 * @version 0.1
 * @date 2025-07-06
 *
 * @copyright Copyright (c) 2025
 */

#include <catch2/catch_all.hpp>

#include "test_component.hpp"
#include <HotBeanEngine/core/isparse_set.hpp>

using namespace HBE::Core;

constexpr size_t TEST_MAX_ITEMS = 10;

TEST_CASE("SparseSet: Initialization") {
    SparseSet<TestComponent, TEST_MAX_ITEMS> sparse_set;

    SECTION("Initial size is zero") {
        REQUIRE(sparse_set.Size() == 0);
    }

    SECTION("No elements present initially") {
        for (size_t i = 0; i < TEST_MAX_ITEMS; i++) {
            REQUIRE_FALSE(sparse_set.HasElement(i));
        }
    }
}

TEST_CASE("SparseSet: Insertion") {
    SparseSet<TestComponent, TEST_MAX_ITEMS> sparse_set;

    SECTION("Insert single element") {
        TestComponent comp;
        comp.m_value = 42;
        
        bool result = sparse_set.Insert(0, comp);
        REQUIRE(result);
        REQUIRE(sparse_set.Size() == 1);
        REQUIRE(sparse_set.HasElement(0));
    }

    SECTION("Insert multiple elements") {
        TestComponent comp;
        
        sparse_set.Insert(0, comp);
        sparse_set.Insert(3, comp);
        sparse_set.Insert(7, comp);
        
        REQUIRE(sparse_set.Size() == 3);
        REQUIRE(sparse_set.HasElement(0));
        REQUIRE(sparse_set.HasElement(3));
        REQUIRE(sparse_set.HasElement(7));
        REQUIRE_FALSE(sparse_set.HasElement(1));
    }

    SECTION("Insert empty element") {
        bool result = sparse_set.InsertEmpty(5);
        REQUIRE(result);
        REQUIRE(sparse_set.Size() == 1);
        REQUIRE(sparse_set.HasElement(5));
    }

    SECTION("Insert at same index twice fails") {
        TestComponent comp;
        sparse_set.Insert(2, comp);
        
        bool result = sparse_set.Insert(2, comp);
        REQUIRE_FALSE(result);
        REQUIRE(sparse_set.Size() == 1);
    }

    SECTION("Insert out of range fails") {
        TestComponent comp;
        bool result = sparse_set.Insert(TEST_MAX_ITEMS + 1, comp);
        REQUIRE_FALSE(result);
    }

    SECTION("Insert max items") {
        TestComponent comp;
        for (size_t i = 0; i < TEST_MAX_ITEMS; i++) {
            bool result = sparse_set.Insert(i, comp);
            REQUIRE(result);
        }
        REQUIRE(sparse_set.Size() == TEST_MAX_ITEMS);
    }

    SECTION("Insert beyond max items fails") {
        TestComponent comp;
        for (size_t i = 0; i < TEST_MAX_ITEMS; i++) {
            sparse_set.Insert(i, comp);
        }
        
        // Can't insert using InsertEmpty when full
        bool result = sparse_set.InsertEmpty(TEST_MAX_ITEMS);
        REQUIRE_FALSE(result);
    }
}

TEST_CASE("SparseSet: Element Access") {
    SparseSet<TestComponent, TEST_MAX_ITEMS> sparse_set;

    SECTION("Get element by reference") {
        TestComponent comp;
        comp.m_value = 99;
        sparse_set.Insert(3, comp);
        
        TestComponent& retrieved = sparse_set.GetElementAsRef(3);
        REQUIRE(retrieved.m_value == 99);
    }

    SECTION("Modify element through reference") {
        TestComponent comp;
        comp.m_value = 10;
        sparse_set.Insert(1, comp);
        
        TestComponent& retrieved = sparse_set.GetElementAsRef(1);
        retrieved.m_value = 50;
        
        REQUIRE(sparse_set.GetElementAsRef(1).m_value == 50);
    }

    SECTION("Get element by pointer") {
        TestComponent comp;
        comp.m_value = 123;
        sparse_set.Insert(5, comp);
        
        TestComponent* ptr = sparse_set.GetElement(5);
        REQUIRE(ptr != nullptr);
        REQUIRE(ptr->m_value == 123);
    }

    SECTION("Get non-existent element returns nullptr") {
        TestComponent* ptr = sparse_set.GetElement(7);
        REQUIRE(ptr == nullptr);
    }

    SECTION("Array subscript operator") {
        TestComponent comp;
        comp.m_value = 777;
        sparse_set.Insert(2, comp);
        
        REQUIRE(sparse_set[2].m_value == 777);
    }

    SECTION("Modify through subscript operator") {
        TestComponent comp;
        sparse_set.Insert(4, comp);
        
        sparse_set[4].m_value = 888;
        REQUIRE(sparse_set[4].m_value == 888);
    }
}

TEST_CASE("SparseSet: Element Removal") {
    SparseSet<TestComponent, TEST_MAX_ITEMS> sparse_set;

    SECTION("Remove single element") {
        TestComponent comp;
        sparse_set.Insert(3, comp);
        
        bool result = sparse_set.Remove(3);
        REQUIRE(result);
        REQUIRE(sparse_set.Size() == 0);
        REQUIRE_FALSE(sparse_set.HasElement(3));
    }

    SECTION("Remove element from middle") {
        TestComponent comp;
        sparse_set.Insert(0, comp);
        sparse_set.Insert(5, comp);
        sparse_set.Insert(9, comp);
        
        sparse_set.Remove(5);
        
        REQUIRE(sparse_set.Size() == 2);
        REQUIRE(sparse_set.HasElement(0));
        REQUIRE_FALSE(sparse_set.HasElement(5));
        REQUIRE(sparse_set.HasElement(9));
    }

    SECTION("Remove non-existent element fails") {
        bool result = sparse_set.Remove(7);
        REQUIRE_FALSE(result);
    }

    SECTION("Remove same element twice fails second time") {
        TestComponent comp;
        sparse_set.Insert(1, comp);
        
        sparse_set.Remove(1);
        bool result = sparse_set.Remove(1);
        
        REQUIRE_FALSE(result);
    }

    SECTION("Remove out of range fails") {
        bool result = sparse_set.Remove(TEST_MAX_ITEMS + 5);
        REQUIRE_FALSE(result);
    }

    SECTION("Remove all elements") {
        TestComponent comp;
        for (size_t i = 0; i < 5; i++) {
            sparse_set.Insert(i, comp);
        }
        
        for (size_t i = 0; i < 5; i++) {
            sparse_set.Remove(i);
        }
        
        REQUIRE(sparse_set.Size() == 0);
        for (size_t i = 0; i < 5; i++) {
            REQUIRE_FALSE(sparse_set.HasElement(i));
        }
    }

    SECTION("Insert after removal") {
        TestComponent comp;
        comp.m_value = 100;
        sparse_set.Insert(3, comp);
        sparse_set.Remove(3);
        
        comp.m_value = 200;
        sparse_set.Insert(3, comp);
        
        REQUIRE(sparse_set.HasElement(3));
        REQUIRE(sparse_set.GetElementAsRef(3).m_value == 200);
    }
}

TEST_CASE("SparseSet: Iteration") {
    SparseSet<TestComponent, TEST_MAX_ITEMS> sparse_set;

    SECTION("Iterate over empty set") {
        int count = 0;
        for (const auto& comp : sparse_set) {
            count++;
        }
        REQUIRE(count == 0);
    }

    SECTION("Iterate over elements") {
        TestComponent comp;
        sparse_set.Insert(1, comp);
        sparse_set.Insert(3, comp);
        sparse_set.Insert(7, comp);
        
        int count = 0;
        for (const auto& elem : sparse_set) {
            count++;
        }
        REQUIRE(count == 3);
    }

    SECTION("Modify elements during iteration") {
        TestComponent comp;
        comp.m_value = 0;
        
        sparse_set.Insert(0, comp);
        sparse_set.Insert(1, comp);
        sparse_set.Insert(2, comp);
        
        for (auto& elem : sparse_set) {
            elem.m_value = 100;
        }
        
        for (const auto& elem : sparse_set) {
            REQUIRE(elem.m_value == 100);
        }
    }

    SECTION("Const iteration") {
        TestComponent comp;
        comp.m_value = 42;
        sparse_set.Insert(5, comp);
        
        const auto& const_set = sparse_set;
        int count = 0;
        for (const auto& elem : const_set) {
            REQUIRE(elem.m_value == 42);
            count++;
        }
        REQUIRE(count == 1);
    }

    SECTION("Iterator begin and end") {
        TestComponent comp;
        sparse_set.Insert(0, comp);
        sparse_set.Insert(5, comp);
        
        auto it = sparse_set.begin();
        auto end = sparse_set.end();
        
        int count = 0;
        while (it != end) {
            ++it;
            count++;
        }
        REQUIRE(count == 2);
    }
}

TEST_CASE("SparseSet: Copy and Move") {
    SparseSet<TestComponent, TEST_MAX_ITEMS> sparse_set;

    SECTION("Copy constructor") {
        TestComponent comp;
        comp.m_value = 555;
        sparse_set.Insert(2, comp);
        sparse_set.Insert(4, comp);
        
        SparseSet<TestComponent, TEST_MAX_ITEMS> copy(sparse_set);
        
        REQUIRE(copy.Size() == 2);
        REQUIRE(copy.HasElement(2));
        REQUIRE(copy.HasElement(4));
        REQUIRE(copy.GetElementAsRef(2).m_value == 555);
    }

    SECTION("Move constructor") {
        TestComponent comp;
        comp.m_value = 666;
        sparse_set.Insert(1, comp);
        sparse_set.Insert(6, comp);
        
        SparseSet<TestComponent, TEST_MAX_ITEMS> moved(std::move(sparse_set));
        
        REQUIRE(moved.Size() == 2);
        REQUIRE(moved.HasElement(1));
        REQUIRE(moved.HasElement(6));
        REQUIRE(moved.GetElementAsRef(1).m_value == 666);
    }
}

TEST_CASE("SparseSet: ISparseSet Interface") {
    SparseSet<TestComponent, TEST_MAX_ITEMS> sparse_set;

    SECTION("GetElementPtrAsAny") {
        TestComponent comp;
        comp.m_value = 999;
        sparse_set.Insert(0, comp);
        
        std::any result = sparse_set.GetElementPtrAsAny(0);
        REQUIRE_FALSE(result.has_value() == false);
        
        IComponent* comp_ptr = std::any_cast<IComponent*>(result);
        REQUIRE(comp_ptr != nullptr);
        
        TestComponent* typed_ptr = dynamic_cast<TestComponent*>(comp_ptr);
        REQUIRE(typed_ptr != nullptr);
        REQUIRE(typed_ptr->m_value == 999);
    }

    SECTION("GetElementPtrAsAny for non-existent element") {
        std::any result = sparse_set.GetElementPtrAsAny(5);
        REQUIRE_FALSE(result.has_value());
    }

    SECTION("Insert via std::any") {
        TestComponent comp;
        comp.m_value = 111;
        std::any any_comp = comp;
        
        bool result = sparse_set.Insert(3, any_comp);
        REQUIRE(result);
        REQUIRE(sparse_set.HasElement(3));
        REQUIRE(sparse_set.GetElementAsRef(3).m_value == 111);
    }
}

TEST_CASE("SparseSet: Edge Cases") {
    SparseSet<TestComponent, TEST_MAX_ITEMS> sparse_set;

    SECTION("Sparse indices with gaps") {
        TestComponent comp;
        
        sparse_set.Insert(0, comp);
        sparse_set.Insert(9, comp);
        
        REQUIRE(sparse_set.Size() == 2);
        REQUIRE(sparse_set.HasElement(0));
        REQUIRE(sparse_set.HasElement(9));
        
        // Check gaps
        for (size_t i = 1; i < 9; i++) {
            REQUIRE_FALSE(sparse_set.HasElement(i));
        }
    }

    SECTION("Remove and reuse sparse indices") {
        TestComponent comp1, comp2;
        comp1.m_value = 100;
        comp2.m_value = 200;
        
        sparse_set.Insert(5, comp1);
        REQUIRE(sparse_set.GetElementAsRef(5).m_value == 100);
        
        sparse_set.Remove(5);
        sparse_set.Insert(5, comp2);
        
        REQUIRE(sparse_set.GetElementAsRef(5).m_value == 200);
    }

    SECTION("Fill and empty repeatedly") {
        TestComponent comp;
        
        for (int iteration = 0; iteration < 3; iteration++) {
            // Fill
            for (size_t i = 0; i < TEST_MAX_ITEMS; i++) {
                sparse_set.Insert(i, comp);
            }
            REQUIRE(sparse_set.Size() == TEST_MAX_ITEMS);
            
            // Empty
            for (size_t i = 0; i < TEST_MAX_ITEMS; i++) {
                sparse_set.Remove(i);
            }
            REQUIRE(sparse_set.Size() == 0);
        }
    }

    SECTION("Remove elements in reverse order") {
        TestComponent comp;
        for (size_t i = 0; i < 5; i++) {
            sparse_set.Insert(i, comp);
        }
        
        for (int i = 4; i >= 0; i--) {
            sparse_set.Remove(i);
        }
        
        REQUIRE(sparse_set.Size() == 0);
    }
}
