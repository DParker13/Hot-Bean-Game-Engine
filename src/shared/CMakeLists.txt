include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(shared STATIC)

target_sources(shared PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Matrix.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Position.cpp

    ${CMAKE_CURRENT_LIST_DIR}/EventSystem.h
    ${CMAKE_CURRENT_LIST_DIR}/Matrix.h
    ${CMAKE_CURRENT_LIST_DIR}/Position.h
)