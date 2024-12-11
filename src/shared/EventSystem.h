#pragma once

#include <SDL.h>

class EventSystem {
public:
    virtual ~EventSystem() = default;

    virtual void OnEvent(SDL_Event& event) {

    }

    virtual void OnUpdate(std::shared_ptr<float> deltaTime) {

    }

    virtual void OnRender(SDL_Surface* surface, SDL_Renderer* renderer) {

    }
};