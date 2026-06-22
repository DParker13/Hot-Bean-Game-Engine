include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(application)
add_subdirectory(components)
add_subdirectory(editor)
add_subdirectory(factories)
add_subdirectory(serializers)
add_subdirectory(systems)
add_subdirectory(utilities)

add_executable(${PROJECT_NAME} main.cpp)

# Copy Example Project to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Example Project"
        "${CMAKE_BINARY_DIR}/Example Project"
)

# Copy assets to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/HotBeanEngine/assets"
        "${CMAKE_BINARY_DIR}/HotBeanEngine/assets"
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    HotBeanEngine_Application
    HotBeanEngine_Factories
)