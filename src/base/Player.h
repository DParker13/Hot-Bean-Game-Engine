#pragma once

#include <memory>
#include "GameObject.h"
#include "Controller.h"

class Player : public GameObject {
private:
    std::unique_ptr<Controller> controller;

public:
    // Default constructor
    Player();

    // Constructor taking a starting position
    Player(Position<float> startingPos);

    void OnEvent(SDL_Event& event) override;
    void OnUpdate() override;
    void OnRender(SDL_Surface* surface, SDL_Renderer* renderer) override;

};