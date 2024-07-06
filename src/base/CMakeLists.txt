add_library(base STATIC)

target_sources(base PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/GameObject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Player.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Controller.cpp

    ${CMAKE_CURRENT_LIST_DIR}/GameObject.h
    ${CMAKE_CURRENT_LIST_DIR}/Player.h
    ${CMAKE_CURRENT_LIST_DIR}/Controller.h
)