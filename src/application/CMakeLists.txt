# Create a static library for the application
add_library(application STATIC
    application.cpp
    application.hpp
    game.cpp
    game.hpp
)

# Link dependencies for the application library
target_link_libraries(application PRIVATE
    SDL2_ttf
    SDL2_mixer
    SDL2_image
    core
    managers
    gameobjects
    systems
)