#include "Controller.h"

Controller::Controller(std::shared_ptr<GameObject> gameObject) {
	this->gameObject.swap(gameObject);
}

void Controller::OnEvent(SDL_Event& event) {
	switch (event.type) {
	case SDL_EVENT_KEY_DOWN:
		if (event.key.keysym.sym == SDLK_w) {
			Position<float> pos = gameObject->GetPosition();
			pos.Y += 1;

			gameObject->GetPosition().SetPosition(pos);
		}
		else if (event.key.keysym.sym == SDLK_a) {
			Position<float> pos = gameObject->GetPosition();
			pos.X -= 1;

			gameObject->GetPosition().SetPosition(pos);
		}
		else if (event.key.keysym.sym == SDLK_s) {
			Position<float> pos = gameObject->GetPosition();
			pos.Y -= 1;

			gameObject->GetPosition().SetPosition(pos);
		}
		else if (event.key.keysym.sym == SDLK_d) {
			Position<float> pos = gameObject->GetPosition();
			pos.X += 1;

			gameObject->GetPosition().SetPosition(pos);
		}
		break;
	}
}