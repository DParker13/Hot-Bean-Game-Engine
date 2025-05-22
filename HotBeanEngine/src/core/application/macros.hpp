#pragma once

#define SETUP_SYSTEM(System, ...) \
    App::GetInstance().GetECSManager()->SetSignature<System, ##__VA_ARGS__>();

#define EXTEND_SYSTEM(OriginalSystem, System, ...)                              \
    App::GetInstance().GetECSManager()->UnregisterSystem<OriginalSystem>();     \
    App::GetInstance().GetECSManager()->SetSignature<System, ##__VA_ARGS__>();
    