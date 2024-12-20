# Define a static library for the core implementation
add_library(managers STATIC
    ${CMAKE_CURRENT_LIST_DIR}/core_manager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core_manager.hpp
    ${CMAKE_CURRENT_LIST_DIR}/entity_manager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/entity_manager.hpp
    ${CMAKE_CURRENT_LIST_DIR}/component_manager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/component_manager.hpp
    ${CMAKE_CURRENT_LIST_DIR}/system_manager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/system_manager.hpp
)

target_include_directories(managers PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

# Link other dependencies if needed (e.g., core library, SDL2, etc.)
# If managers depend on core, link it here.
target_link_libraries(managers PRIVATE
    core
)