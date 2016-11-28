#include "Camera.h"

Vector2f Camera::position;
Object * Camera::focus;
float Camera::speed;

void Camera::setFocus(Object * object){
	focus = object;
}

void Camera::setSpeed(float sp){
	speed = sp;
}

void Camera::update(float dt)
{
	Vector2f targetPosition = Vector2f(focus->position.x + focus->scale.x / 2, focus->position.y + focus->scale.y / 2);

	//float currentSpeed = ((targetPosition^position)+1.0f) * speed;
	//Vector2f direction = (targetPosition - position).normalize();

	//position += dt * currentSpeed * direction;

	position = targetPosition;
}

Camera::Camera()
{
}


Camera::~Camera()
{
}
