include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/base
    ${CMAKE_CURRENT_SOURCE_DIR}/shared
    ${CMAKE_CURRENT_SOURCE_DIR}/world-generator
)

add_subdirectory(shared)
add_subdirectory(base)
add_subdirectory(world-generator)

add_executable(OceanSim main.cpp Application.cpp)

link_directories(C:/SDL/VisualC/x64/Debug)
target_link_libraries(OceanSim C:/SDL/VisualC/x64/Debug/SDL3.lib)
target_link_libraries(OceanSim base shared world-generator)

add_custom_command(
    TARGET OceanSim
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/SDL3.dll
            $<TARGET_FILE_DIR:OceanSim>
)

add_custom_target(CopySDL3DLL ALL DEPENDS OceanSim)

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "include dir='${dir}'")
endforeach()