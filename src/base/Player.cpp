#include "Player.h"
#include "Controller.h"

Player::Player() : Player(Position<float>()) {
}

Player::Player(Position<float> startingPos)
	: GameObject(startingPos) {
	//controller = std::make_unique<Controller>(std::make_shared<GameObject>(this));
}

void Player::OnEvent(SDL_Event& event) {
	//Calls controller OnEvent to handle any event calls
	controller->OnEvent(event);
}

void Player::OnUpdate() {

}

void Player::OnRender(SDL_Surface* surface, SDL_Renderer* renderer) {

}