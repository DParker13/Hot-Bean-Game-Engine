enable_testing()

add_executable(HotBeanEngine_Managers_Test
    ecs_manager_test.cpp
    component_manager_test.cpp
    system_manager_test.cpp
    entity_manager_test.cpp
    sparse_set_test.cpp
)

target_include_directories(HotBeanEngine_Managers_Test PRIVATE
    ${catch2_SOURCE_DIR}/src
)

target_link_libraries(HotBeanEngine_Managers_Test PRIVATE
    HotBeanEngine_Application
    Catch2::Catch2WithMain
)

if (WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_options(HotBeanEngine_Managers_Test PRIVATE
        -mwindows
        -static-libstdc++ -static-libgcc
    )
endif()


list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(HotBeanEngine_Managers_Test)