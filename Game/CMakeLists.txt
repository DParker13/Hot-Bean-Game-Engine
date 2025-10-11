project("Game")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type to Debug by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()
message(STATUS "Setting build type to '${CMAKE_BUILD_TYPE}'")

add_executable(${PROJECT_NAME} src/main.cpp)

# Add subdirectories for project modules
add_subdirectory(src/systems)
add_subdirectory(src/scenes)
add_subdirectory(src/game)

# Link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
    game
)

# Not sure why this gets set to nothing but other binary dirs don't
set(yaml_cpp_BINARY_DIR ${CMAKE_BINARY_DIR}/_deps/yaml_cpp-build)


# Gather all .yaml files in the scenes directory
file(GLOB_RECURSE SCENE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/*.yaml")

# Ensure target folders exist
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/assets")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/scenes")

# Add a post-build command to copy assets and resources
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD

    # Copy the entire assets directory
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
            "${CMAKE_CURRENT_BINARY_DIR}/assets"

    # Copy config.yaml
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/src/config.yaml"
            "${CMAKE_CURRENT_BINARY_DIR}/config.yaml"

    # Copy the HotBeanEngine DLL
    # COMMAND ${CMAKE_COMMAND} -E copy
    #         "${HotBeanEngine_BINARY_DIR}/libHotBeanEngine.dll"
    #         "${CMAKE_CURRENT_BINARY_DIR}/libHotBeanEngine.dll"

    COMMENT "Copying assets, config file, DLL, and scenes to binary directory"
)

# Loop to copy each .yaml file in scenes individually
foreach(scene_file ${SCENE_FILES})
    get_filename_component(scene_name "${scene_file}" NAME)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${scene_file}"
                "${CMAKE_CURRENT_BINARY_DIR}/scenes/${scene_name}"
    )
endforeach()