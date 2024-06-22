#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include <SDL3/SDL.h>

class EventSystem {
public:
    virtual ~EventSystem() = default;

    virtual void OnEvent(SDL_Event& event) {

    }

    virtual void OnUpdate() {

    }

    virtual void OnRender(SDL_Surface* surface, SDL_Renderer* renderer) {

    }
};

#endif // EVENT_SYSTEM_H
