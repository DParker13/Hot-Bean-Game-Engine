add_library(core-interface INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/ecs.hpp
    ${CMAKE_CURRENT_LIST_DIR}/entity_manager.hpp
    ${CMAKE_CURRENT_LIST_DIR}/component_manager.hpp
    ${CMAKE_CURRENT_LIST_DIR}/system_manager.hpp
    ${CMAKE_CURRENT_LIST_DIR}/sparse_set.hpp
)

add_library(core OBJECT
    ${CMAKE_CURRENT_LIST_DIR}/entity_manager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/component_manager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/system_manager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core_manager.cpp
)

target_include_directories(HotBeanEngine PUBLIC ${CMAKE_CURRENT_LIST_DIR})