cmake_minimum_required(VERSION 3.11) # FetchContent is new in version 3.11.
project("Game")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type to Debug by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()
message(STATUS "Setting build type to '${CMAKE_BUILD_TYPE}'")

add_executable(${PROJECT_NAME} src/main.cpp)

include_directories(
    ${SDL2_SOURCE_DIR}/include
    ${HotBeanEngine_SOURCE_DIR}/include
)

add_subdirectory(src)

# Link libraries
if (WIN32)
    # If DEBUG is ON, we disable the linker flags
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(STATUS "Debug mode is enabled, no additional linker flags")
        target_link_libraries(${PROJECT_NAME} PRIVATE
            SDL2main
            test_game
        )
    else()
        message(STATUS "Debug mode is disabled, applying linker flags")
        target_link_libraries(${PROJECT_NAME} PRIVATE
            SDL2main
            test_game
            ${CMAKE_LINKER_FLAGS} -Wl,-subsystem,windows
        )
    endif()
else ()
    # I have never tried this. I have only tested building on Windows
    target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2
        test_game
    )
endif()

# Not sure why this gets set to nothing but other binary dirs don't
set(yaml_cpp_BINARY_DIR ${CMAKE_BINARY_DIR}/_deps/yaml_cpp-build)

# Copy SDL2 DLLs to build directory
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${SDL2_BINARY_DIR}/SDL2.dll
                ${SDL2_BINARY_DIR}/SDL2d.dll
                ${SDL2_ttf_BINARY_DIR}/SDL2_ttf.dll
                ${SDL2_ttf_BINARY_DIR}/SDL2_ttfd.dll
                ${SDL2_image_BINARY_DIR}/SDL2_image.dll
                ${SDL2_image_BINARY_DIR}/SDL2_imaged.dll
                ${SDL2_mixer_BINARY_DIR}/SDL2_mixer.dll
                ${SDL2_mixer_BINARY_DIR}/SDL2_mixerd.dll
                ${yaml_cpp_BINARY_DIR}/libyaml-cpp.dll
                ${yaml_cpp_BINARY_DIR}/libyaml-cppd.dll
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
else()
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${SDL2_BINARY_DIR}/SDL2.dll
                ${SDL2_ttf_BINARY_DIR}/SDL2_ttf.dll
                ${SDL2_image_BINARY_DIR}/SDL2_image.dll
                ${SDL2_mixer_BINARY_DIR}/SDL2_mixer.dll
                ${yaml_cpp_BINARY_DIR}/libyaml-cpp.dll
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()