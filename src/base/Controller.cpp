#include "Controller.h"

Controller::Controller(float speed, std::shared_ptr<Entity> gameObject)
	:speed(speed) {
	this->gameObject.swap(gameObject);
}

void Controller::OnEvent(SDL_Event& event) {
    switch (event.type) {
        case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					isMovingLeft = true;
					break;
				case SDLK_RIGHT:
					isMovingRight = true;
					break;
				case SDLK_UP:
					isMovingUp = true;
					break;
				case SDLK_DOWN:
					isMovingDown = true;
					break;
			}
            break;
        case SDL_KEYUP:
			switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					isMovingLeft = false;
					break;
				case SDLK_RIGHT:
					isMovingRight = false;
					break;
				case SDLK_UP:
					isMovingUp = false;
					break;
				case SDLK_DOWN:
					isMovingDown = false;
					break;
			}
            break;
    }
}

void Controller::OnUpdate(std::shared_ptr<float> deltaTime) {
	//Calls base OnUpdate
	Entity::OnUpdate(deltaTime);

	Position<float> pos = GetPosition();
	float distance = speed * *deltaTime;

	if (isMovingLeft) {
        pos.X -= distance;
    }
	
	if (isMovingRight) {
        pos.X += distance;
    }
	
	if (isMovingUp) {
        pos.Y -= distance;
    }
	
	if (isMovingDown) {
        pos.Y += distance;
    }
	
	SetPosition(pos);
}

void Controller::OnInitialize() {
	AddChild(gameObject);

	Entity::OnInitialize();
}