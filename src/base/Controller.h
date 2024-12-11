#pragma once

#include <memory>
#include "Entity.h"

class Controller : public Entity {
private:
    float speed;
    bool isMovingLeft = false;
    bool isMovingRight = false;
    bool isMovingUp = false;
    bool isMovingDown = false;
    std::shared_ptr<Entity> gameObject;

public:
    Controller(float speed, std::shared_ptr<Entity> gameObject);

    //Entity methods
    void OnInitialize() override;

    //EventSystem methods
    void OnEvent(SDL_Event& event) override;
    void OnUpdate(std::shared_ptr<float> deltaTime) override;
};