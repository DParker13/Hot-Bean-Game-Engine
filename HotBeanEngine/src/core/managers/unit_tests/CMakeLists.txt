# Enable testing
enable_testing()

# Add an executable for the test
add_executable(managers_test
    test_component.hpp
    component_manager_test.cpp
)

# Link the test executable to the necessary libraries
target_link_libraries(managers_test PRIVATE
    managers
    Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(managers_test)