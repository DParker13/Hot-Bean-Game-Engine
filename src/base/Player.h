#pragma once

#include <memory>
#include "Entity.h"
#include "Controller.h"

class Player : public Entity {
private:
    std::unique_ptr<Controller> controller;

public:
    // Default constructor
    Player();

    // Constructor taking a starting position
    Player(Position<float> startingPos);

    void OnEvent(SDL_Event& event) override;
    void OnUpdate(std::shared_ptr<float> deltaTime) override;
    void OnRender(SDL_Surface* surface, SDL_Renderer* renderer) override;

};