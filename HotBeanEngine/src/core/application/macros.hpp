#pragma once

// TODO: Allow setting up systems with components or archetypes
// #define MAKE_SHARED_ARCHETYPE(...) std::make_shared<__VA_ARGS__>().get()

// #define SETUP_SYSTEM_ARCHETYPES(System, ...) \
//     App::GetInstance().GetECSManager()->SetSignature<System>(MAKE_SHARED_ARCHETYPE(__VA_ARGS__));

// #define EXTEND_SYSTEM_ARCHETYPES(OriginalSystem, System, ...)                   \
//     App::GetInstance().GetECSManager()->UnregisterSystem<OriginalSystem>();     \
//     SETUP_SYSTEM_ARCHETYPES(System, __VA_ARGS__)

#define SETUP_SYSTEM(System, ...) \
    App::GetInstance().GetECSManager()->SetSignature<System, ##__VA_ARGS__>();

#define EXTEND_SYSTEM(OriginalSystem, System, ...)                              \
    App::GetInstance().GetECSManager()->UnregisterSystem<OriginalSystem>();     \
    SETUP_SYSTEM(System, ##__VA_ARGS__)
    