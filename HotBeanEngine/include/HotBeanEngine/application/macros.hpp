#pragma once

// TODO: Allow setting up systems with components or archetypes
// #define MAKE_SHARED_ARCHETYPE(...) std::make_shared<__VA_ARGS__>().get()

// #define SETUP_SYSTEM_ARCHETYPES(System, ...) \
//     App::GetInstance().GetECSManager()->SetSignature<System>(MAKE_SHARED_ARCHETYPE(__VA_ARGS__));

// #define EXTEND_SYSTEM_ARCHETYPES(OriginalSystem, System, ...)                   \
//     App::GetInstance().GetECSManager()->UnregisterSystem<OriginalSystem>();     \
//     SETUP_SYSTEM_ARCHETYPES(System, __VA_ARGS__)

#define g_app HBE::Application::Application::GetInstance()

#define g_ecs g_app.GetECSManager()

#define LOG(type, message) g_app.Log(type, message, __FILE__, __LINE__, __func__)

#define DEFINE_NAME(Name)                               \
    static std::string_view StaticGetName() {           \
        return Name;                                    \
    }                                                   \
                                                        \
    std::string_view GetName() const {                  \
        return Name;                                    \
    }

/**
 * @brief Macro to define the signature of a system
 */
#define DEFINE_SIGNATURE(System, Name, ...)             \
    DEFINE_NAME(Name)                                   \
                                                        \
    void SetSignature() override {                      \
        g_ecs.SetSignature<System, ##__VA_ARGS__>();    \
    }

#define EXTEND_SYSTEM(OriginalSystem, System, Name, ...)    \
    DEFINE_NAME(Name)                                       \
                                                            \
    void SetSignature() override {                          \
        g_ecs.UnregisterSystem<OriginalSystem>();           \
        g_ecs.SetSignature<System, ##__VA_ARGS__>();        \
    }
    