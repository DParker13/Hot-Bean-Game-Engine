# Create a static library for the application
add_library(application STATIC
    all_application.hpp
    app.cpp
    app.hpp
    archetype.hpp
    macros.hpp
)

# Link dependencies for the application library
target_link_libraries(application PUBLIC
    SDL2_ttf
    SDL2_mixer
    SDL2_image
    managers
)