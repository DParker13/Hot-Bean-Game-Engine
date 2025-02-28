add_library(gameobjects-ui STATIC
    ui-element.hpp
    ui-element.cpp
    text.hpp
    text.cpp
    textbox.hpp
    textbox.cpp
)

target_include_directories(gameobjects-ui PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(gameobjects-ui PRIVATE
    core
)