# Create a static library for the application
add_library(application STATIC
    all_application.hpp
    app.cpp
    app.hpp
    macros.hpp
    ../archetypes/default_archetypes.hpp
)

# Link dependencies for the application library
target_link_libraries(application PUBLIC
    SDL3_mixer::SDL3_mixer
    SDL3_image::SDL3_image
    managers
    default_components
)