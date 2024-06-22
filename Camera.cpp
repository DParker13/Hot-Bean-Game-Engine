#include "Camera.h"

Camera::Camera(Position<float> pos) {
	Position::SetPosition(pos);
}

Camera::Camera() : Camera(Position<float>()) {
}

void Camera::OnUpdate() {

}

void Camera::OnRender(SDL_Surface* surface, SDL_Renderer* renderer) {

}