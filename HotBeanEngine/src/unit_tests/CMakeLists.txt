add_executable(managers_test
    ecs_manager_test.cpp
    component_manager_test.cpp
    system_manager_test.cpp
    entity_manager_test.cpp
    sparse_set_test.cpp
)

target_link_libraries(managers_test PRIVATE
    base_game
    Catch2::Catch2WithMain
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_options(managers_test PUBLIC
        -mwindows
        -static-libstdc++ -static-libgcc
    )
endif()


list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(managers_test)