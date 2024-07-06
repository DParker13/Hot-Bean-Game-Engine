#pragma once

#include <memory>
#include "GameObject.h"

class Controller : public EventSystem {
private:
    std::shared_ptr<GameObject> gameObject;

public:
    Controller(std::shared_ptr<GameObject> gameObject);

    void OnEvent(SDL_Event& event) override;

};