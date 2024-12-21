# Create a static library for the application
add_library(application STATIC
    application.cpp
    application.hpp
)

# Link dependencies for the application library
target_link_libraries(application PRIVATE
    SDL2_ttf
    core
    managers
    gameobjects
    systems
)