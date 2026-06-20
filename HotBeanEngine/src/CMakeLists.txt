include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(editor)
add_subdirectory(application)
add_subdirectory(utilities)
add_subdirectory(serializers)
add_subdirectory(components)
add_subdirectory(systems)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC
    HotBeanEngine_Application
)