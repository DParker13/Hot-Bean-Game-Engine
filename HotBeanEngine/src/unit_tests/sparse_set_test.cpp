#include <catch2/catch_all.hpp>

#include <HotBeanEngine/core/sparse_set.hpp>
#include "test_system.hpp"

using namespace HBE::Core;

TEST_CASE("SparseSet") {
    #define MAX_ITEMS 10
    SparseSet<int, MAX_ITEMS> sparse_set;

    SECTION("Add") {
        sparse_set.Add(1);
        REQUIRE(sparse_set.Size() == 1);
    }

    SECTION("Remove") {
        sparse_set.Add(1);
        sparse_set.Remove(0);
        REQUIRE(sparse_set.Size() == 0);
    }

    SECTION("GetElementAsRef") {
        sparse_set.Add(100);
        REQUIRE(sparse_set.GetElementAsRef(0) == 100);
    }

    SECTION("Insert") {
        sparse_set.Insert(0, 1);
        REQUIRE(sparse_set.Size() == 1);
        REQUIRE(sparse_set.HasElement(0));
        REQUIRE(sparse_set[0] == 1);
    }

    SECTION("Insert out of range") {
        REQUIRE_THROWS_AS(sparse_set.Insert(-1, 100), std::out_of_range);
        REQUIRE_THROWS_AS(sparse_set.Insert(MAX_ITEMS + 1, 100), std::out_of_range);
    }

    SECTION("Add max items") {
        for (int i = 0; i < MAX_ITEMS - 1; i++) {
            sparse_set.Add(100);
        }
        REQUIRE_NOTHROW(sparse_set.Add(100));
    }

    SECTION("Add max items + 1") {
        for (int i = 0; i < MAX_ITEMS; i++) {
            sparse_set.Add(100);
        }

        REQUIRE_THROWS_AS(sparse_set.Add(100), std::overflow_error);
    }
}

TEST_CASE("ISparseSet") {
    #define MAX_ITEMS 10
    SparseSet<int, MAX_ITEMS> sparse_set;
    sparse_set.Insert(0, 100);

    SECTION("GetElementPtrAsAny") {
        REQUIRE(sparse_set.Size() == 1);
        REQUIRE(sparse_set.HasElement(0));
        REQUIRE(*std::any_cast<int*>(sparse_set.GetElementPtrAsAny(0)) == 100);
    }

    SECTION("GetElementPtrAsAny Bad Cast") {
        REQUIRE(sparse_set.Size() == 1);
        REQUIRE(sparse_set.HasElement(0));
        REQUIRE_THROWS_AS(std::any_cast<int>(sparse_set.GetElementPtrAsAny(0)), std::bad_any_cast);
    }
}

// TODO: Create test cases double check memory is being managed correctly