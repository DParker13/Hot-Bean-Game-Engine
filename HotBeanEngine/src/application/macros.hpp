#pragma once

// TODO: Allow setting up systems with components or archetypes
// #define MAKE_SHARED_ARCHETYPE(...) std::make_shared<__VA_ARGS__>().get()

// #define SETUP_SYSTEM_ARCHETYPES(System, ...) \
//     App::GetInstance().GetECSManager()->SetSignature<System>(MAKE_SHARED_ARCHETYPE(__VA_ARGS__));

// #define EXTEND_SYSTEM_ARCHETYPES(OriginalSystem, System, ...)                   \
//     App::GetInstance().GetECSManager()->UnregisterSystem<OriginalSystem>();     \
//     SETUP_SYSTEM_ARCHETYPES(System, __VA_ARGS__)

/**
 * @brief Macro to define the signature of a system
 * 
 */
#define DEFINE_SIGNATURE(System, ...)                \
    void SetSignature() override {                   \
        g_ecs.SetSignature<System, ##__VA_ARGS__>(); \
    }

#define EXTEND_SYSTEM(OriginalSystem, System, ...)   \
    void SetSignature() override {                   \
        g_ecs.UnregisterSystem<OriginalSystem>();    \
        g_ecs.SetSignature<System, ##__VA_ARGS__>(); \
    }
    