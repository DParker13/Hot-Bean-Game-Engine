include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(base STATIC)

target_sources(base PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Entity.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Player.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Controller.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Text.cpp

    ${CMAKE_CURRENT_LIST_DIR}/Entity.h
    ${CMAKE_CURRENT_LIST_DIR}/Player.h
    ${CMAKE_CURRENT_LIST_DIR}/Controller.h
    ${CMAKE_CURRENT_LIST_DIR}/Text.h
)