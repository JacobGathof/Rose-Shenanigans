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
	/*
	Vector2f targetPosition = focus->centerOfMass;

	float currentSpeed = ((targetPosition^position)+1.0f) * speed;
	Vector2f direction = (targetPosition - position).normalize();

	position += dt * currentSpeed * direction;
	*/

	position = focus->centerOfMass;

}

Camera::Camera()
{
}


Camera::~Camera()
{
}
