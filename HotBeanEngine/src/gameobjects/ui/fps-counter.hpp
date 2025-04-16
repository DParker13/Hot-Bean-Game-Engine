#pragma once

#include "text.hpp"

namespace GameObjects {
    namespace UI {
        struct FPSCounter : public Text {
            Uint32 _framesCounter = 0;
            Uint32 _lastTickCount = 0;
            Uint32 _fps = 0;

            FPSCounter(App& app)
                : Text(app) {};

            // void OnUpdate(Entity entity) override {
            //     GameObject::OnUpdate(entity);

            //     _framesCounter++;

            //     if (SDL_GetTicks() - _lastTickCount >= 1000) {
            //         _fps = _framesCounter;
            //         GetComponent<Components::Text>()._text = "FPS: " + std::to_string(_fps);
            //         _framesCounter = 0;
            //     }
            // };
        };
    }
}